/*******************************************************************************
 *
 *  Filename    : Utils.h
 *  Description : List of Generic function not specific to any package
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <vector>

//----- utils_string.cc  -------------------------------------------------------
extern bool  BreakLineToWords( const std::string&, std::vector<std::string>& );
extern float StrToFloat( const std::string& );


#endif // __UTILS_H__
