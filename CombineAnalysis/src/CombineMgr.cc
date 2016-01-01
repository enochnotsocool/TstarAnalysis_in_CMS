/*******************************************************************************
 *
 *  Filename    : CombineMgr.cc
 *  Description : Implementation for CombineMgr class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TstarAnalysis/Utils/interface/Utils.h"
#include <fstream>

using namespace std;

//------------------------------------------------------------------------------ 
//   Declaring Global variables
//------------------------------------------------------------------------------
CombineMgr*  cmbMgr = NULL;

//------------------------------------------------------------------------------ 
//   Constructor
//------------------------------------------------------------------------------
CombineMgr::CombineMgr()
{
   _channelList.insert( ChannelPair(ggMuon, new ChannelMgr(ggMuon)) );
}

CombineMgr::~CombineMgr()
{
   for( auto& process : _processList ){
      delete process;
   }
   for( auto& channelpair : _channelList ){
      delete channelpair.second;
   }
}

//------------------------------------------------------------------------------ 
//   File Parser
//------------------------------------------------------------------------------
void CombineMgr::ParseCMDFile( const string& filename )
{
   ifstream input( filename );
   string cmd;
   string line;
   vector<string> tokens;

   while( getline( input, line ) ){
      if( !BreakLineToWords( line, tokens ) ) { continue; }
      
      cmd = tokens[0];
      if( cmd == "SetChannel" && tokens.size() == 3 ){
         SetChannel( tokens[1], tokens[2] ); 
      } 
      else {
         cerr << "Error! Unrecognised command \"" << cmd << "\"" << endl;
         continue;
      }
   }
}

//------------------------------------------------------------------------------ 
//   Access Members
//------------------------------------------------------------------------------
ChannelMgr* CombineMgr::Channel( const ChannelName& x ){
   return _channelList[x];
} 

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
   //----- Making input file for system  ------------------------------------------
   TFile* shapeFile = new TFile( "Shapes.root" , "RECREATE" );
   for( const auto& process : _processList ){
      TH1F* hist = (TH1F*)process->GetShape()->Clone( (process->ObjName()).c_str() );
      hist->Write();
   }
   TH1F* hist = (TH1F*)_channelList[ggMuon]->sample( Data )->Hist( ChiSquareTstarMass )->Clone();
   hist->Write();
   shapeFile->Close();
   delete shapeFile;
   
   //----- Making datacard  -------------------------------------------------------
   FILE*  datacard = fopen( "datacard.txt" , "w" );
   fprintf( datacard , "imax %lu\n", _channelList.size() );
   fprintf( datacard , "jmax *\n" );
   fprintf( datacard , "kmax *\n" );
   fprintf( datacard , "----------------------------------\n" );

   for( const auto& process : _processList ){
      fprintf( datacard , "shape %s %s Shapes.root %s\n",
            Stringify(process->GetProcess()).c_str(),
            Stringify(process->GetChannel()).c_str(),
            (process->ObjName()).c_str() );
   }
   fprintf( datacard , "----------------------------------\n" );

   fprintf( datacard , "bin  " );
   for( auto& channelpair : _channelList ){
      printf( "  %s" , Stringify(channelpair.second->Name()).c_str());
   } 
   fprintf(datacard, "\n" );
   fprintf( datacard , "observation  " );
   for( auto& channelpair : _channelList ){
      printf( " %lf" , channelpair.second->sample(Data)->getRawEventCount() );
   }
   fprintf(datacard, "\n" );
   fprintf( datacard , "----------------------------------\n" );
}

//------------------------------------------------------------------------------ 
//   Helper private functions
//------------------------------------------------------------------------------
void CombineMgr::SetChannel( const string& x , const string& filename )
{
   const ChannelName name = ChannelFromString( x );
   if( name == CHANNEL_END ) { 
      cerr << "Error! Unrecognized channel " << x << endl;
      return; 
   }
   _channelList[name]->ParseCMDFile( filename );
}

