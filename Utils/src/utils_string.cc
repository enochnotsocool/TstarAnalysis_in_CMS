/*******************************************************************************
 *
 *  Filename    : utils_string.cc
 *  Description : String parsing functions
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

float StrToFloat( const string& x )
{
   float ans;
   istringstream iss( x );
   iss >> ans;
   return ans;
}

bool BreakLineToWords( const string& line, vector<string>& words )
{
   vector<string> temp;
   istringstream iss(line);
   copy( istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(temp));
   words = temp;
   // Comment handling
   if( words.empty() ) { return false; }
   if( words[0][0] == '#' ) { return false; }
   return true;
}

