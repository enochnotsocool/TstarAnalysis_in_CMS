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

void ChannelMgr::MakeLimitRequirements( const SampleName& massPoint )
{
   makeProcessList( massPoint );
   makeNuissanceList();

   makeShapeFile( massPoint );
   
   makeCard_Header(massPoint);
   makeCard_ShapeMarker(massPoint);
   makeCard_ChannelYield(massPoint);
   makeCard_ProcessYield(massPoint);
   makeCard_NuissanceTable(massPoint);

   clearList();
}

//------------------------------------------------------------------------------ 
//   Process generation private member functions
//------------------------------------------------------------------------------
void ChannelMgr::makeProcessList( const SampleName& massPoint )
{

   if( _MCsignalMap.find(massPoint) == _MCsignalMap.end() ){
      cerr << "Error, mass point " << Stringify(massPoint) << "not found" << endl;
      return ;
   }
   // Making signal process
   HC_Process* signal = new HC_Process( _name , massPoint );
   makeSignalProcess( signal );

   // Making Background process 
   HC_Process* ttjets  = new HC_Process( _name, TTJets );
   HC_Process* singlet = new HC_Process( _name, SINGLE_T );
   HC_Process* bosons  = new HC_Process( _name, BOSONS );
   HC_Process* ttBoson = new HC_Process( _name, TT_PLUS_BOSON );

   makeBGLimitProcess( ttjets, TTJets, TTJets);
   makeBGLimitProcess( singlet, SingleT_S, SingleTbar_TW );
   makeBGLimitProcess( bosons , WJets, ZZ );  
   makeBGLimitProcess( ttBoson, TTW_Lepton, TTZ_Quark ); 
 
   // Inserting into List
   _processList.push_back( signal );
   _processList.push_back( ttjets );
   _processList.push_back( singlet );
   _processList.push_back( bosons );
   _processList.push_back( ttBoson );
}

void ChannelMgr::makeBGLimitProcess( HC_Process* const proc, const SampleName& first, const SampleName& last)
{
   const PlotDef& def = availiablePlots[ChiSquareTstarMass];
   const string  name = Stringify(proc->GetChannel()) +"_" + Stringify(proc->GetProcess()) ;
   TH1F* temp = NULL;
   Parameter totalbg(0,0,0);
   double scale = 0.0;

   proc->SetShape( new TH1F( name.c_str(), name.c_str() , def.BinCount() , def.XMin() , def.XMax() ) );
   
   for( auto it= _MCbackgroundMap.find( first ); it!=_MCbackgroundMap.end() && it->first <= last ; ++it ){
      temp = it->second->Hist( ChiSquareTstarMass );
      if( temp->Integral() != 0 ){
         scale = getHistScale( it->second );
         proc->GetShape()->Add( temp, scale );
         totalbg+= it->second->getExpectedYield( _totalLumi );
         cout << name << " " << totalbg << endl; 
      }
   }
   proc->SetRate( totalbg.CentralValue() );
   normalizeProcessShape( proc );
   
   //----- Adding Nuisance parameter  ---------------------------------------------
   NuisancePar norm( (name+"_Norm").c_str() , "lnN" );
   proc->AddNuisance( norm , 1 + totalbg.RelativeAvgError() );
   
   NuisancePar lumi( "lumi" , "lnN" );
   proc->AddNuisance( lumi , 1.05 );
}

void ChannelMgr::makeSignalProcess( HC_Process* const proc )
{
   const SampleMgr* const sample = _MCsignalMap.at( proc->GetProcess() );
   proc->SetShape( (TH1F*)sample->Hist( ChiSquareTstarMass )->Clone() );
   proc->SetRate( sample->getExpectedYield(_totalLumi).CentralValue() );
   normalizeProcessShape( proc );
   NuisancePar lumi( "lumi" , "lnN" );
   proc->AddNuisance( lumi , 1.05 );
}

void ChannelMgr::normalizeProcessShape( HC_Process* const proc )
{
   proc->GetShape()->Scale( proc->GetRate() / proc->GetShape()->Integral() );
}

//------------------------------------------------------------------------------ 
//   Nuisance list generation
//------------------------------------------------------------------------------
void ChannelMgr::makeNuissanceList()
{
   for( const auto process : _processList ){
      for( const auto npair : process->GetNuisance() ){
         _uncertaintlyList[npair.first][process] = npair.second;
      } 
   }
}

//------------------------------------------------------------------------------ 
//   File making member functions
//------------------------------------------------------------------------------
string ChannelMgr::shapeFileName( const SampleName& massPoint ) const
{
   string name = "./data/shapes/Shape_";
   name += Stringify( _name );
   name += Stringify( massPoint );
   name += ".root";
   return name;
}

string ChannelMgr::cardFileName( const SampleName& massPoint ) const 
{
   string name = "./data/cards/datacard_";
   name += Stringify( _name );
   name += Stringify( massPoint );
   name += ".txt";
   return name;
}

void ChannelMgr::makeShapeFile( const SampleName& massPoint ) const
{
   string filename = shapeFileName(massPoint);
   TFile* shapeFile = new TFile( filename.c_str() , "RECREATE" );
   for( const auto& process : _processList ){
      string shapename = process->ObjName();
      TH1F* hist = (TH1F*)process->GetShape()->Clone( shapename.c_str() );
      hist->Write();
   }
   TH1F* hist = (TH1F*)sample( Data )->Hist( ChiSquareTstarMass )->Clone("data_obs");
   hist->Write();
   shapeFile->Close();
   delete shapeFile;
}


void ChannelMgr::makeCard_Header(const SampleName& massPoint ) const
{
   FILE* datacard = fopen( cardFileName(massPoint).c_str() , "w" );
   fprintf( datacard , "imax 1\n" );
   fprintf( datacard , "jmax *\n" );
   fprintf( datacard , "kmax *\n" );
   fprintf( datacard , "-------------------------------\n" );
   fclose( datacard );
}

void ChannelMgr::makeCard_ShapeMarker(const SampleName& massPoint) const 
{
   FILE* datacard = fopen( cardFileName(massPoint).c_str() , "a" );
   const string channel   = Stringify(_name);
   const string shapefile = shapeFileName(massPoint) ;

   fprintf( datacard, "shapes %15s %15s %25s %30s\n",
         "data_obs", channel.c_str(), shapefile.c_str(),  "data_obs");
   for( const auto& process : _processList ){
      fprintf( datacard , "shapes %15s %15s %25s %30s\n",
            Stringify(process->GetProcess()).c_str(),
            Stringify(process->GetChannel()).c_str(),
            shapefile.c_str(),
            (process->ObjName()).c_str() );
   }
   fprintf( datacard , "-------------------------------\n" );
   fclose( datacard );
}

void ChannelMgr::makeCard_ChannelYield(const SampleName& massPoint ) const 
{
   FILE* datacard = fopen( cardFileName(massPoint).c_str() , "a" );
   fprintf( datacard , "%-15s %15s\n" , 
         "bin" , Stringify(_name).c_str());
   fprintf( datacard , "%-15s %15lf\n", 
         "observation",  sample(Data)->getRawEventCount() );
   fprintf( datacard , "-------------------------------\n" );
   fclose(datacard);
}

void ChannelMgr::makeCard_ProcessYield(const SampleName& massPoint) const 
{
   FILE* datacard = fopen( cardFileName(massPoint).c_str() , "a" );
   fprintf( datacard, "%-45s", "bin" );
   for( const auto& process : _processList ){
      fprintf( datacard, "%20s", Stringify(process->GetChannel()).c_str() );
   } fprintf( datacard, "\n" );

   fprintf( datacard, "%-45s", "process" );
   for( const auto& process : _processList ){
      fprintf( datacard, "%20s", Stringify(process->GetProcess()).c_str() );
   } fprintf( datacard, "\n" );
   
   fprintf( datacard, "%-45s", "process" );
   for( const auto& process : _processList ){
      fprintf( datacard, "%20d", process->GetProcess() );
   } fprintf( datacard, "\n" );
   
   fprintf( datacard, "%-45s", "rate" );
   for( const auto& process : _processList ){
      fprintf( datacard, "%20lf", process->GetRate() );
   } fprintf( datacard, "\n" );
   fprintf( datacard , "-------------------------------\n" );
   fclose(datacard);
}


void ChannelMgr::makeCard_NuissanceTable(const SampleName& massPoint ) const 
{
   FILE* datacard = fopen( cardFileName(massPoint).c_str() , "a" );
   for( const auto& np_pair : _uncertaintlyList ){
      const auto& np  = np_pair.first;
      const auto& map = np_pair.second;
      fprintf( datacard, "%-30s %14s", np.Name().c_str() , np.Type().c_str() );
      for( const auto& process : _processList ){
         if( map.find( process ) == map.end() ){
            fprintf( datacard , "%20s", "-" );
         } else {
            fprintf( datacard, "%20lf" , map.at(process) );
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
   _uncertaintlyList.clear();
}
