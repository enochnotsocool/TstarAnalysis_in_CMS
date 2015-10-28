/*******************************************************************************
 *
 *  Filename    : plotCmd.cc
 *  Description : Implementation of commands
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/

#include <iostream>
#include "util.h"
#include "plotCmd.h"
#include "PlotMerging.h"

using namespace std;

bool initPlotCmd()
{
   cout << "Hello" << endl;
   if (!(cmdMgr->regCmd("InitBase"    , 4 , new SetFileBase ) &&
         cmdMgr->regCmd("Print"       , 4 , new Print       ) &&
         cmdMgr->regCmd("AddType"     , 4 , new AddType     ) &&
         cmdMgr->regCmd("AddFile"     , 4 , new AddFile     ) &&
         cmdMgr->regCmd("SetXSection" , 4 , new SetXSection ) &&
         cmdMgr->regCmd("SetEff"      , 4 , new SetEff      ) &&
         cmdMgr->regCmd("SetColor"    , 4 , new SetColor    ) &&
         cmdMgr->regCmd("SetLine"     , 4 , new SetLine     ) &&
         cmdMgr->regCmd("MakePlot"    , 4 , new MakePlot    )
                                                            )    ) {
      cerr << "Registering \"plot\" commands fails... exiting" << endl;
      return false;
   }
   return true;
}
//------------------------------------------------------------------------------ 
//   Global variables
//------------------------------------------------------------------------------
extern PlotMerging* pltMgr;
static std::vector<std::string> options;
static std::string  singleOption;
#define CHECKMGR   \
   if( !pltMgr ) { std::cerr << "Error! Program not yet initialized!" << std::endl; \
      return CMD_EXEC_ERROR; }

//------------------------------------------------------------------------------ 
//   SetFileBase tupleDir
//------------------------------------------------------------------------------
CmdExecStatus SetFileBase::exec( const string& option )
{
   if(!CmdExec::lexSingleOption( option, singleOption , false )){ return CMD_EXEC_ERROR; }
   if( pltMgr ){
      std::cout << "Warning! Deleting previous incidence of PlotManager" << std::endl;
      delete pltMgr ;
   }
   pltMgr = new PlotMerging( singleOption );
   return CMD_EXEC_DONE;
}
void SetFileBase::usage( ostream& os ) const {} 
void SetFileBase::help() const {}

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
//   AddType
//------------------------------------------------------------------------------
CmdExecStatus AddType::exec( const string& option )
{
   CHECKMGR; 
   options.clear();
   if(!CmdExec::lexOptions( option, options, 1  )) { return CMD_EXEC_ERROR; } 

   pltMgr->addSample( options[0] );

   return CMD_EXEC_DONE;
}
void AddType::usage( ostream& os ) const {} 
void AddType::help() const {}

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
   pltMgr->sample(options[0])->setCrossSection(1.);

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
   pltMgr->sample(options[0])->setSelectionEff(1.);

   return CMD_EXEC_DONE;  
}

void SetEff::usage( ostream& os ) const {} 
void SetEff::help() const {}

//------------------------------------------------------------------------------ 
//   SetColor
//------------------------------------------------------------------------------
CmdExecStatus SetColor::exec( const string& input )
{
   CHECKMGR; 
   options.clear();
   if(!CmdExec::lexOptions( input , options, 2 )) { return CMD_EXEC_DONE; }

   if( !pltMgr->sample(options[0]) ){
      std::cerr << "Error! Sample " << options[0] << "not found!" << std::endl;
      return CMD_EXEC_ERROR;
   } 
   pltMgr->sample(options[0])->setFillColor(1);

   return CMD_EXEC_DONE; 
}
void SetColor::usage( ostream& os ) const {} 
void SetColor::help() const {}

//------------------------------------------------------------------------------ 
//   SetLine
//------------------------------------------------------------------------------
CmdExecStatus SetLine::exec( const string& input )
{ 
   CHECKMGR; 
   options.clear();
   if(!CmdExec::lexOptions( input , options, 2 )) { return CMD_EXEC_DONE; }

   if( !pltMgr->sample(options[0]) ){
      std::cerr << "Error! Sample " << options[0] << "not found!" << std::endl;
      return CMD_EXEC_ERROR;
   } 
   pltMgr->sample(options[0])->setLineColor(1);

   return CMD_EXEC_DONE; 
}
void SetLine::usage( ostream& os ) const {} 
void SetLine::help() const {}

//------------------------------------------------------------------------------ 
//   MakePlot
//------------------------------------------------------------------------------
CmdExecStatus MakePlot::exec( const string& options ){ return CMD_EXEC_DONE; }
void MakePlot::usage( ostream& os ) const {} 
void MakePlot::help() const {}
