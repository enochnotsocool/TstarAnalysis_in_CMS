/*******************************************************************************
 *
 *  Filename    : plotCmd.cc
 *  Description : Implementation of commands
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include <iostream>
#include "util.h"
#include "AnaCmd.h"
#include "AnalysisMgr.h"
#include "TColor.h"
using namespace std;

bool initPlotCmd()
{
   cout << "Hello" << endl;
   if (!(cmdMgr->regCmd("InitBase"    , 4 , new SetFileBase ) &&
         cmdMgr->regCmd("SetLumi"     , 5 , new SetLumi     ) &&
         cmdMgr->regCmd("Print"       , 4 , new Print       ) &&
         cmdMgr->regCmd("AddFile"     , 4 , new AddFile     ) &&
         cmdMgr->regCmd("SetXSection" , 4 , new SetXSection ) &&
         cmdMgr->regCmd("SetEff"      , 4 , new SetEff      ) &&
         cmdMgr->regCmd("SetSignal"   , 4 , new SetSignal   ) &&
         cmdMgr->regCmd("MakeBasic"   , 5 , new MakeBasic   ) &&
         cmdMgr->regCmd("MakeCombine" , 5 , new MakeCombine ) &&
         cmdMgr->regCmd("MakeSignalPlot"  , 5 , new MakeSignalPlot  ) &&
         cmdMgr->regCmd("ClearPlot"   , 5 , new ClearPlot   ) ) ) {
      cerr << "Registering \"plot\" commands fails... exiting" << endl;
      return false;
   }
   return true;
}

enum PlotMgrState {
   PLOTNONE = 0 ,
   PLOTINIT = 1 ,
   PLOTBASIC = 2 , 

   PLOT_STATE_TOT = 3
};

//------------------------------------------------------------------------------ 
//   Global variables
//------------------------------------------------------------------------------
extern AnalysisMgr* pltMgr;
static PlotMgrState currentState = PLOTNONE;
static std::vector<std::string> options;
static std::string  singleOption;

#define CHECKMGR   \
   if( !pltMgr ) { std::cerr << "Error! Program not yet initialized!" << std::endl; \
      return CMD_EXEC_ERROR; }

//------------------------------------------------------------------------------ 
//   SetFileBase tupleDir
//------------------------------------------------------------------------------
CmdExecStatus SetFileBase::exec( const string& input )
{
   if(!CmdExec::lexSingleOption( input, singleOption , false )){ return CMD_EXEC_ERROR; }
   if( pltMgr ){
      std::cout << "Warning! Deleting previous incidence of PlotManager" << std::endl;
      delete pltMgr ;
   }
   pltMgr = new AnalysisMgr( singleOption );
   currentState = PLOTINIT ; 
   return CMD_EXEC_DONE;
}
void SetFileBase::usage( ostream& os ) const {} 
void SetFileBase::help() const {}

//------------------------------------------------------------------------------ 
//   SetLumi
//------------------------------------------------------------------------------
CmdExecStatus SetLumi::exec( const string& input )
{
   CHECKMGR; 
   if(!CmdExec::lexSingleOption( input , singleOption , false )) { return CMD_EXEC_ERROR; }
   pltMgr->setLumi( std::stof( singleOption ));
   return CMD_EXEC_DONE; 
}
void SetLumi::usage( ostream& os ) const {} 
void SetLumi::help() const {}

//------------------------------------------------------------------------------ 
//   Print
//------------------------------------------------------------------------------
CmdExecStatus Print::exec( const string& options )
{
   CHECKMGR;
   pltMgr->Print();
   return CMD_EXEC_DONE; 

}
void Print::usage( ostream& os ) const {} 
void Print::help() const {}

//------------------------------------------------------------------------------ 
//   AddFile
//------------------------------------------------------------------------------
CmdExecStatus AddFile::exec( const string& input )
{
   CHECKMGR; 
   options.clear();
   if(!CmdExec::lexOptions( input , options, 2 )) { return CMD_EXEC_DONE; }

   if( !pltMgr->sample(options[0]) ){
      std::cerr << "Error! Sample " << options[0] << "not found!" << std::endl;
      return CMD_EXEC_ERROR;
   } 
   pltMgr->sample(options[0])->addFile(options[1]);
   currentState = PLOTINIT ; 

   return CMD_EXEC_DONE; 
}
void AddFile::usage( ostream& os ) const {} 
void AddFile::help() const {} 

//------------------------------------------------------------------------------ 
//   SetXSection
//------------------------------------------------------------------------------
CmdExecStatus SetXSection::exec( const string& input )
{ 
   CHECKMGR; 
   options.clear();
   if(!CmdExec::lexOptions( input , options, 2 )) { return CMD_EXEC_DONE; }

   if( !pltMgr->sample(options[0]) ){
      std::cerr << "Error! Sample " << options[0] << "not found!" << std::endl;
      return CMD_EXEC_ERROR;
   } 
   pltMgr->sample(options[0])->setCrossSection(std::stof(options[1]));

   return CMD_EXEC_DONE; 
}
void SetXSection::usage( ostream& os ) const {} 
void SetXSection::help() const {}


//------------------------------------------------------------------------------ 
//   SetEff
//------------------------------------------------------------------------------
CmdExecStatus SetEff::exec( const string& input )
{
   CHECKMGR; 
   options.clear();
   if(!CmdExec::lexOptions( input , options, 2 )) { return CMD_EXEC_DONE; }

   if( !pltMgr->sample(options[0]) ){
      std::cerr << "Error! Sample " << options[0] << "not found!" << std::endl;
      return CMD_EXEC_ERROR;
   } 
   pltMgr->sample(options[0])->setSelectionEff(std::stof(options[1]));

   return CMD_EXEC_DONE;  
}

void SetEff::usage( ostream& os ) const {} 
void SetEff::help() const {}

//------------------------------------------------------------------------------ 
//   SetSignal
//------------------------------------------------------------------------------
CmdExecStatus SetSignal::exec( const string& input )
{
   CHECKMGR;
   options.clear();
   if(!CmdExec::lexSingleOption(input,singleOption)){ return CMD_EXEC_ERROR; }
  
   if( !pltMgr->setSignalMass( singleOption ) ) { 
      std::cerr << "Error setting signal!" << std::endl;
      return CMD_EXEC_ERROR; 
   }
   return CMD_EXEC_DONE;
}
void SetSignal::usage( ostream& os ) const {}
void SetSignal::help() const {}

//------------------------------------------------------------------------------ 
//   MakeBasic
//------------------------------------------------------------------------------
CmdExecStatus MakeBasic::exec( const string& input )
{
   CHECKMGR ;
   if(!CmdExec::lexOptions( input , options , 0 )){ return CMD_EXEC_ERROR ; } 

   if( currentState >= PLOTBASIC ){
      std::cerr << "No update since last generation, skipping commnd" << std::endl;
      return CMD_EXEC_ERROR ; 
   }

   pltMgr->makeBasicPlots();
   currentState = PLOTBASIC;
   return CMD_EXEC_DONE; 
}
void MakeBasic::usage( ostream& os ) const {} 
void MakeBasic::help() const {}

//------------------------------------------------------------------------------ 
//   MakeCombine
//------------------------------------------------------------------------------
CmdExecStatus MakeCombine::exec( const string& input )
{
   CHECKMGR ;
   if( currentState < PLOTBASIC ){
      std::cerr << "Basic Plots not Initialized! Please run MakeBasic First!" << std::endl;
      return CMD_EXEC_ERROR ; 
   }

   if(!CmdExec::lexSingleOption( input , singleOption , 1 )) { return CMD_EXEC_ERROR; } 
   pltMgr->makeDataToBGPlot( singleOption );

   return CMD_EXEC_DONE; 
}
void MakeCombine::usage( ostream& os ) const {} 
void MakeCombine::help() const {}

//------------------------------------------------------------------------------ 
//   MakeSignalPlot
//------------------------------------------------------------------------------
CmdExecStatus MakeSignalPlot::exec( const string& input )
{
   CHECKMGR ;
   if( currentState < PLOTBASIC ){
      std::cerr << "Basic Plots not Initialized! Please run MakeBasic First!" << std::endl;
      return CMD_EXEC_ERROR ; 
   }

   if(!CmdExec::lexSingleOption( input , singleOption , 1 )) { return CMD_EXEC_ERROR; } 
   pltMgr->makeSignalPlot( singleOption );

   return CMD_EXEC_DONE; 
}
void MakeSignalPlot::usage( ostream& os ) const {} 
void MakeSignalPlot::help() const {}

//------------------------------------------------------------------------------ 
//   ClearPlot
//------------------------------------------------------------------------------
CmdExecStatus ClearPlot::exec( const string& input )
{
   delete pltMgr; 
   pltMgr = 0 ; 
   currentState = PLOTNONE;
   return CMD_EXEC_DONE;
}
void ClearPlot::usage( ostream& os ) const {} 
void ClearPlot::help() const {}
