/*******************************************************************************
 *
 *  Filename    : SampleListing.cc
 *  Description : Implementation for simple listing file 
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/SampleListing.h"
#include "CMSSW_Utils/Utils_Functions/interface/Utils.h"
#include <iostream>
#include <fstream>

using namespace std;

//------------------------------------------------------------------------------ 
//   Declaring global variables
//------------------------------------------------------------------------------
SampleTable availableSamples;

//------------------------------------------------------------------------------ 
//   Dummy static variables for out-of-range return
//------------------------------------------------------------------------------
static SampleMgr   _dummy_sample_ ( "dummy", "" );
static SampleList  _dummy_list_( "dummy" , "" );

//------------------------------------------------------------------------------ 
//   SampleList member functions
//------------------------------------------------------------------------------
SampleList::SampleList( const string& name , const std::string& latex ):
   _name(name), _latex_name(latex)
{}

SampleList::SampleList( const SampleList& x ):
   _name(x._name), _latex_name(x._latex_name), _sampleList(x._sampleList)
{}

SampleList::~SampleList(){}

SampleMgr& SampleList::operator[]( const string& input ) 
{
   for( auto& sample : _sampleList ){
      if( input == sample.Name() ){ 
         return sample; }
   }
   cout << "Warning! Sample (" << input << ") not found! Return dummy!" << endl;
   return _dummy_sample_;
}

const SampleMgr& SampleList::operator[]( const string& input ) const 
{
   for( const auto& sample : _sampleList ){
      if( input == sample.Name() ){ 
         return sample; }
   }
   cout << "Warning! Sample (" << input << ") not found! Return dummy!" << endl;
   return _dummy_sample_;
}

bool SampleList::HasSample( const string& input ) const
{
   for( const auto& sample : _sampleList ){
      if( input == sample.Name() ){ 
         return true; }
   }
   return false;
}

const string SampleList::MakeLatexName() const 
{
   string ans = _latex_name;
   ConvertToRegularLatex(ans);
   return ans;
}
const string SampleList::MakeRootTitle() const 
{
   string ans = _latex_name;
   ConvertToRootFlavorLatex(ans);
   return ans;
}

const Parameter SampleList::ExpectedYield( const double totallumi ) const 
{
   Parameter ans;
   for( const auto& sample : _sampleList ) {
      if( sample.GetRawEventCount() > 0 ) {
         ans += sample.ExpectedYield( totallumi );}
   }
   return ans;
}

void SampleList::SetFillColor( const Color_t c , const double a )
{
   for( auto& sample : _sampleList ){
      sample.SetFillColor(c,a);
   }
}

void SampleList::SetLineColor( const Color_t c )
{
   for( auto& sample : _sampleList ){
      sample.SetLineColor(c);
   }
}


//------------------------------------------------------------------------------ 
//   SampleTable member functions
//------------------------------------------------------------------------------
SampleTable::SampleTable()
{}

SampleTable::SampleTable( const SampleTable& x ):
   _table(x._table)
{}

SampleTable::~SampleTable()
{}

SampleList& SampleTable::operator[]( const string& input )
{
   for( auto& list : _table ){
      if( input == list.Name() ){
         return list; }
   }
   cout << "Warning! List (" << input << ") not found! Return dummy!" << endl;
   return _dummy_list_;
}

const SampleList& SampleTable::operator[]( const string& input ) const 
{
   for( const auto& list : _table ){
      if( input == list.Name() ){
         return list; }
   }
   cout << "Warning! List (" << input << ") not found! Return dummy!" << endl;
   return _dummy_list_;
}

bool SampleTable::HasList( const string& input ) const 
{
   for( const auto& list : _table ){
      if( input ==list.Name() ){
         return true;}
   }
   return false;
}

SampleMgr& SampleTable::Sample( const string& input )  
{
   for( auto& list : _table ){
      for( auto& sample : list ){
         if( input == sample.Name() ){
            return sample; }
      }
   }
   cout << "Warning! Sample (" << input << ") not found! Return dummy!" << endl;
   return _dummy_sample_;
}

const SampleMgr& SampleTable::Sample( const string& input )  const
{
   for( const auto& list : _table ){
      for( const auto& sample : list ){
         if( input == sample.Name() ){
            return sample; }
      }
   }
   cout << "Warning! Sample (" << input << ") not found! Return dummy!" << endl;
   return _dummy_sample_;
}

bool SampleTable::HasSample( const string& input ) const
{
   for( const auto& list : _table ){
      if( list.HasSample(input) ){ 
         return true; }
   }
   return false;
}


bool SampleTable::InitFromFile( const std::string&  cfgfile )
{
   unsigned line_num = 0;
   ifstream file( cfgfile );
   string line;
   vector<string> tokens;

   while( getline(file,line) ){
      cout << "\rReading file " << cfgfile << " at line " << ++line_num << flush;
      if( !BreakLineToWords(line,tokens,"|" ) ) { continue; }
      for( auto& token : tokens ){
         StripTrailingSpace(token);}

      if( tokens.size() != 7 ) {
         //cerr << "Skipping over with too little columns" << endl; 
         continue;
      }
      const string listname  = tokens[0];
      const string listlatex = tokens[1];
      if( !HasList(listname) ){
         // cerr << "Adding new list: " << listname << " " << listlatex << endl;
         AddList( SampleList(listname,listlatex) );
      }
      const string samplename  = tokens[2];
      const string samplelatex = tokens[3];
      if( (*this)[listname].HasSample(samplename) ){
         // cerr << "\rWarning! Skipping duplicate sample at line (" << line_num << ")!"<< endl;
         continue;
      } else {
         //cerr << "Adding new sample: " << samplename << " " << samplelatex << endl;
         (*this)[listname].AddSample( SampleMgr(samplename,samplelatex) );
      }
      const double crs = StrToFloat( tokens[4] );
      const double up  = StrToFloat( tokens[5] );
      const double low = StrToFloat( tokens[6] );
      const Parameter crx( crs,up,low );
      (*this)[listname][samplename].SetCrossSection(crx); 
   }

   return true;
}

void SampleTable::Print() const 
{
   cout << "\n-------------------------------------------------------------" << endl;
   for( const auto& list : _table ){
      for( const auto& sample : list ){
         cout << list.Name() << " " << sample.Name() << " " << sample.CrossSection() << endl;
      }
   }
   cout << "\n-------------------------------------------------------------" << endl;
}

