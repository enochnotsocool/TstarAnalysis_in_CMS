/*******************************************************************************
 *
 *  Filename    : ChannelMgr_Save.cc
 *  Description : Creating names for the various functions 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"

using namespace std;

//------------------------------------------------------------------------------ 
//   Static global variables
//------------------------------------------------------------------------------
static string plot_dir   = "./data/plots/";
static string latex_dir  = "./data/latex/" ; 
static string shape_dir  = "./data/shapes/";
static string card_dir   = "./data/cards/" ;
static string combine_dir = "./data/limits" ;

static string shape_prefix = "Shape_";
static string card_prefix  = "datacard_";

static const string root_ext = ".root";
static string plot_extention = ".eps";

//------------------------------------------------------------------------------ 
//   ChannelMgr Method implementation 
//------------------------------------------------------------------------------
const std::string ChannelMgr::PlotFilePath( const std::string& name ) const
{
   return  plot_dir + _name + name + plot_extention ; 
}

const string ChannelMgr::ShapeFilePath( const std::string& massPoint ) const
{
   return shape_dir + shape_prefix +_name + massPoint + root_ext;
}

const string ChannelMgr::CardeFilePath( const std::string& massPoint ) const 
{
   return card_dir + card_prefix + _name + massPoint + ".txt";
}

const string ChannelMgr::RawCombineOutput( const string& massPoint, const string& method ) const
{
   return "higgsCombineTest." + method + ".mH" + MassNumberString(massPoint) + ".root"; 
}

const string ChannelMgr::StoreCombineOutput( const string& massPoint, const string& method ) const
{
   return combine_dir + _name + "_" + MassNumberString(massPoint) + "_" + method + root_ext;
}

const string ChannelMgr::MassNumberString( const string& massPoint ) const 
{
   string ans = massPoint;
   for( auto it = ans.begin() ; it != ans.end() ; ++it ){
      if( (*it) < '0' || (*it) > '9' ){
         ans.erase(it) ; --it; }
   }
   for( auto it = ans.begin() ; it != ans.end() ; ++it ){
      if( (*it) == '0'  ){
         ans.erase(it) ; --it;
      } else {
         break;
      } 
   }
   return ans;
}

