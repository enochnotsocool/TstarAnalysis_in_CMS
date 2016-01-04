/*******************************************************************************
 *
 *  Filename    : Combine_MakeCombine.cc
 *  Description : Functions for generating the requirements of HiggCombine Package
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"

void CombineMgr::MakeCombine()
{
   for( auto& channelpair : _channelList ){
      channelpair.second->MakeLimitProcesses( _processList );
   }
   for( const auto process : _processList ){
      for( const auto npair : process->GetNuisance() ){
         _uncertaintlyList[npair.first][process] = npair.second;
      } 
   }
   
   makeShapeFile(); 
   //----- Making datacard  -------------------------------------------------------
   FILE*  datacard = fopen( "datacard.txt" , "w" );
   makeHeader( datacard );
   fprintf( datacard , "----------------------------------\n" );
   makeShapeMarker(datacard);
   fprintf( datacard , "----------------------------------\n" );
   makeChannelYield(datacard);
   fprintf( datacard , "----------------------------------\n" );
   makeProcessYield(datacard);
   fprintf( datacard , "----------------------------------\n" );
   makeNuissanceTable(datacard);
   
   fclose( datacard );
}

//------------------------------------------------------------------------------ 
//   Helper private functions
//------------------------------------------------------------------------------
void CombineMgr::makeShapeFile()
{
   TFile* shapeFile = new TFile( "Shapes.root" , "RECREATE" );
   for( const auto& process : _processList ){
      TH1F* hist = (TH1F*)process->GetShape()->Clone( (process->ObjName()).c_str() );
      hist->Write();
   }
   TH1F* hist = (TH1F*)_channelList[ggMuon]->sample( Data )->Hist( ChiSquareTstarMass )->Clone("data_obs");
   hist->Write();
   shapeFile->Close();
   delete shapeFile;
}

void CombineMgr::makeHeader(FILE* datacard)
{
   fprintf( datacard , "imax %lu\n", _channelList.size() );
   fprintf( datacard , "jmax *\n" );
   fprintf( datacard , "kmax *\n" );
}

void CombineMgr::makeShapeMarker(FILE* datacard)
{
   fprintf( datacard, "shapes %15s %15s Shapes.root %30s\n",
         "data_obs", "ggMuon", "data_obs");
   for( const auto& process : _processList ){
      fprintf( datacard , "shapes %15s %15s Shapes.root %30s\n",
            Stringify(process->GetProcess()).c_str(),
            Stringify(process->GetChannel()).c_str(),
            (process->ObjName()).c_str() );
   }
}

void CombineMgr::makeChannelYield(FILE* datacard)
{
   fprintf( datacard , "%-15s" , "bin" );
   for( auto& channelpair : _channelList ){
      fprintf( datacard, "%15s" , Stringify(channelpair.second->Name()).c_str());
   } 
   fprintf(datacard, "\n" );
   fprintf( datacard , "%-15s", "observation" );
   for( auto& channelpair : _channelList ){
      fprintf( datacard, " %15lf" , channelpair.second->sample(Data)->getRawEventCount() );
   }
   fprintf(datacard, "\n" );

}

void CombineMgr::makeProcessYield(FILE* datacard)
{
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
}


void CombineMgr::makeNuissanceTable(FILE* datacard)
{
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
}
