/*******************************************************************************
 *
 *  Filename    : CombineMgr_MakeHiggsCombineFiles.cc
 *  Description : Implementation for making the Higgs combine files
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include "TstarAnalysis/CombineAnalysis/interface/NuisancePar.h"
#include "TFile.h"
#include "TH1F.h"
#include <string>

using namespace std;

//------------------------------------------------------------------------------ 
//   Helper static variables 
//------------------------------------------------------------------------------
const string    limit_base = "ChiSquareTstarMass";
const HistMgr&  FormatRef() { return availablePlots[limit_base]; }

//------------------------------------------------------------------------------ 
//   ChannelMgr member functions
//------------------------------------------------------------------------------
void ChannelMgr::MakeLimitRequirement( const string& massPoint )
{
   if( !HasSample( "Signal", massPoint ) ){
      cerr << "Error! Mass Point (" << massPoint << ") not found!" << endl;
      _MCSampleTable.Print();
      return;      
   }

   _processList.push_back( MakeSignalProcess(massPoint) );
   for( const auto& list : _MCSampleTable ){
      if( list.Name()=="Signal" ) { continue; }
      _processList.push_back( MakeBGProcess( list ) );
   }
   MakeNuissanceMap();

   MakeShapeFile( massPoint );
   MakeCardFile( massPoint );

   clearList();
}

//------------------------------------------------------------------------------ 
//   Process generation private member functions
//------------------------------------------------------------------------------
const HC_Process* ChannelMgr::MakeSignalProcess( const string& massPoint ) const
{
   cout << "Making signal process of (" << massPoint << ")" << endl;
   HC_Process* proc = new HC_Process( _name , massPoint );
   const SampleMgr& sig = Sample(massPoint);

   proc->SetShape( (TH1F*)sig.Hist( limit_base )->Clone() );
   proc->SetRate( sig.ExpectedYield(_totalLumi).CentralValue() );
   proc->Noramlize();

   return proc;
}

const HC_Process* ChannelMgr::MakeBGProcess( const SampleList& list ) const 
{
   HC_Process* proc = new HC_Process( _name , list.Name() );
   const string name = proc->ObjName() ;
   unsigned bin = FormatRef().BinCount();
   double  xmin = FormatRef().XMin();
   double  xmax = FormatRef().XMax();
   double scale = 0.0;
   const TH1F* temp = NULL;
   Parameter totalbg(0,0,0);

   proc->SetShape( new TH1F( name.c_str(), name.c_str() , bin , xmin , xmax ) );

   for( const auto& sample : list ){
      temp = sample.Hist( limit_base );
      if( temp->Integral() != 0 ){
         scale = sample.GetHistogramScale( _totalLumi );
         proc->GetShape()->Add( temp, scale );
         totalbg += sample.ExpectedYield( _totalLumi );
      }
   }
   proc->SetRate( totalbg.CentralValue() );
   proc->Noramlize();

   return proc;
}

void ChannelMgr::MakeNuissanceMap()
{
   //----- Make Normalization Part  -----------------------------------------------  
   for( const auto& process : _processList ){
      const string newname = process->ObjName() + "_Norm" ;
      const NuisancePar norm( newname, "lnN" );
      const string procname = process->GetProcess();
      Parameter nu;
      if( HasSample("Signal",procname) ){
         nu = Sample(procname).ExpectedYield(_totalLumi);
      } else {
         nu = _MCSampleTable[procname].ExpectedYield(_totalLumi);
      }
      _nuissanceMap[norm][process] = nu;
   }

   //----- Making Luminocity Part  ------------------------------------------------
   const NuisancePar lumi( "Lumi" , "lnN" );
   const Parameter nu_lumi( _totalLumi , _totalLumi*0.05 , _totalLumi*0.05 );
   for( const auto& process : _processList ){
      _nuissanceMap[lumi][process] = nu_lumi;
   }
}


void ChannelMgr::MakeShapeFile( const string& massPoint ) const
{
   string filename = ShapeFilePath(massPoint);
   TFile* shapeFile = new TFile( filename.c_str() , "RECREATE" );
   for( const auto& process : _processList ){
      string shapename = process->ObjName();
      TH1F* hist = (TH1F*)process->GetShape()->Clone( shapename.c_str() );
      hist->Write();
   }
   TH1F* hist = (TH1F*)Sample("Data").Hist(limit_base)->Clone("data_obs");
   hist->Write();
   shapeFile->Close();
   delete shapeFile;
}


void ChannelMgr::MakeCardFile(const string& massPoint ) const
{
   FILE* datacard = fopen( CardeFilePath(massPoint).c_str() , "w" );
   const string channel   = _name;
   const string shapefile = ShapeFilePath(massPoint) ;

   //----- Header Part  -----------------------------------------------------------
   fprintf( datacard , "imax 1\n" );
   fprintf( datacard , "jmax *\n" );
   fprintf( datacard , "kmax *\n" );
   fprintf( datacard , "-------------------------------\n" );

   //----- Shape File Part  -------------------------------------------------------
   fprintf( datacard, "shapes %15s %15s %25s %30s\n",
         "data_obs", channel.c_str(), shapefile.c_str(),  "data_obs");
   for( const auto& process : _processList ){
      fprintf( datacard , "shapes %15s %15s %25s %30s\n",
            process->GetProcess().c_str(),
            process->GetChannel().c_str(),
            shapefile.c_str(),
            (process->ObjName()).c_str() );
   }
   fprintf( datacard , "-------------------------------\n" );
  
   //----- Normalization Part  ----------------------------------------------------
   fprintf( datacard , "%-15s %15s\n" , "bin" , channel.c_str());
   fprintf( datacard , "%-15s %15lf\n", "observation",  Sample("Data").GetRawEventCount() );
   fprintf( datacard , "-------------------------------\n" );
   
   fprintf( datacard, "%-45s", "bin" );
   for( const auto& process : _processList ){
      fprintf( datacard, "%20s", process->GetChannel().c_str() );
   } fprintf( datacard, "\n" );

   fprintf( datacard, "%-45s", "process" );
   for( const auto& process : _processList ){
      fprintf( datacard, "%20s", process->GetProcess().c_str() );
   } fprintf( datacard, "\n" );

   int id = 1;
   fprintf( datacard, "%-45s", "process" );
   for( const auto& process : _processList ){
      if( HasSample( "Signal" , process->GetProcess() ) ){
         fprintf( datacard, "%20d", -id );
      } else {
         fprintf( datacard, "%20d", +id ); 
      }++id;
   } fprintf( datacard, "\n" );

   fprintf( datacard, "%-45s", "rate" );
   for( const auto& process : _processList ){
      fprintf( datacard, "%20lf", process->GetRate() );
   } fprintf( datacard, "\n" );
   fprintf( datacard , "-------------------------------\n" );
   
   //----- Nuisance Parameter Part  -----------------------------------------------
   for( const auto& np_pair : _nuissanceMap ){
      const auto& np  = np_pair.first;
      const auto& map = np_pair.second;
      fprintf( datacard, "%-30s %14s", np.Name().c_str() , np.Type().c_str() );
      for( const auto& process : _processList ){
         if( map.find( process ) == map.end() ){
            fprintf( datacard , "%20s", "-" );
         } else {
            fprintf( datacard, "%20s" , map.at(process).MakeCardFormat().c_str() );
         }
      }
      fprintf( datacard , "\n" );
   }
   fprintf( datacard , "-------------------------------\n" );
   fclose( datacard );
}


//------------------------------------------------------------------------------ 
//   Tidy up member functions
//------------------------------------------------------------------------------
void ChannelMgr::clearList()
{
   for( auto process: _processList ){
      delete process;
   }
   _processList.clear();
   _nuissanceMap.clear();
}
