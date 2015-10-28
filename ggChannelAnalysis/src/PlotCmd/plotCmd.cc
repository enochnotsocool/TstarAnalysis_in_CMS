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
   if (!(cmdMgr->regCmd("SetFileBase", 4, new SetFileBase) &&
         cmdMgr->regCmd("AddType", 4, new AddType) &&
         cmdMgr->regCmd("AddFile", 4, new AddFile) &&
         cmdMgr->regCmd("SetColor", 4, new SetColor) &&
         cmdMgr->regCmd("SetLine", 4, new SetLine) &&
         cmdMgr->regCmd("MakePlot", 4, new MakePlot )
      )) {
      cerr << "Registering \"plot\" commands fails... exiting" << endl;
      return false;
   }
   return true;
}

//------------------------------------------------------------------------------ 
//   SetFileBase tupleDir
//------------------------------------------------------------------------------
CmdExecStatus SetFileBase::exec( const string& options ){ return CMD_EXEC_DONE; }
void SetFileBase::usage( ostream& os ) const {} 
void SetFileBase::help() const {}

//------------------------------------------------------------------------------ 
//   AddType
//------------------------------------------------------------------------------
CmdExecStatus AddType::exec( const string& options ){ return CMD_EXEC_DONE; }
void AddType::usage( ostream& os ) const {} 
void AddType::help() const {}

//------------------------------------------------------------------------------ 
//   AddFile
//------------------------------------------------------------------------------
CmdExecStatus AddFile::exec( const string& options ){ return CMD_EXEC_DONE; }
void AddFile::usage( ostream& os ) const {} 
void AddFile::help() const {} 

//------------------------------------------------------------------------------ 
//   SetColor
//------------------------------------------------------------------------------
CmdExecStatus SetColor::exec( const string& options ){ return CMD_EXEC_DONE; }
void SetColor::usage( ostream& os ) const {} 
void SetColor::help() const {}

//------------------------------------------------------------------------------ 
//   SetLine
//------------------------------------------------------------------------------
CmdExecStatus SetLine::exec( const string& options ){ return CMD_EXEC_DONE; }
void SetLine::usage( ostream& os ) const {} 
void SetLine::help() const {}

//------------------------------------------------------------------------------ 
//   MakePlot
//------------------------------------------------------------------------------
CmdExecStatus MakePlot::exec( const string& options ){ return CMD_EXEC_DONE; }
void MakePlot::usage( ostream& os ) const {} 
void MakePlot::help() const {}
