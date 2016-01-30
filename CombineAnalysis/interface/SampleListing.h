/*******************************************************************************
 *
 *  Filename    : SampleListing.h
 *  Description : Container classes for SampleMgr to organize by type
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __SAMPLELISTING_H__
#define __SAMPLELISTING_H__

#include "TstarAnalysis/CombineAnalysis/interface/SampleMgr.h"
#include <vector>
#include <string>

class SampleTable;
extern SampleTable availableSamples;
extern bool  InitSampleList(const std::string& );
extern void  PrintSampleList();

class SampleList
{
public:
   SampleList( const std::string&, const std::string& );
   SampleList( const SampleList& );
   virtual ~SampleList ();

   //----- Container like access functions  ---------------------------------------
   typedef std::vector<SampleMgr>::iterator        iterator;
   typedef std::vector<SampleMgr>::const_iterator  const_iterator;
   iterator begin()             { return _sampleList.begin(); }
   iterator end()               { return _sampleList.end() ; }
   const_iterator begin() const { return _sampleList.begin(); }
   const_iterator end()   const { return _sampleList.end();   }
   void AddSample( const SampleMgr& x ) { _sampleList.push_back(x); }
   SampleMgr& front() { return _sampleList.front(); }
   const SampleMgr& front() const { return _sampleList.front(); }
   unsigned size() const { return _sampleList.size(); }

   // Self defined access functions
   const std::string& Name()      const { return _name; }
   const std::string  RootName()  const  { return MakeRootTitle() ; }
   const std::string  LatexName() const { return MakeLatexName() ; }
   SampleMgr&       operator[]( const std::string& );
   const SampleMgr& operator[]( const std::string& ) const ;
   bool  HasSample( const std::string& ) const;

   void SetFillColor( const Color_t , const double=1.0);
   void SetLineColor( const Color_t );
   const Parameter ExpectedYield( const double)const;

private:
   const std::string _name;
   const std::string _latex_name;
   std::vector<SampleMgr>  _sampleList;

   const std::string MakeLatexName() const ;
   const std::string MakeRootTitle() const ;
};

class SampleTable
{
public:
   SampleTable();
   SampleTable( const SampleTable& );
   virtual ~SampleTable ();
   bool InitFromFile( const std::string& );

   //----- Container like access functions  ---------------------------------------
   typedef std::vector<SampleList>::iterator       iterator;
   typedef std::vector<SampleList>::const_iterator const_iterator;
   typedef std::vector<SampleList>::reverse_iterator       riterator;
   typedef std::vector<SampleList>::const_reverse_iterator rconst_iterator;
   iterator begin() { return _table.begin(); }
   iterator end()   { return _table.end(); }
   riterator rbegin() { return _table.rbegin(); }
   riterator rend()   { return _table.rbegin(); }
   const_iterator begin() const { return _table.begin(); }
   const_iterator end()   const { return _table.end() ; }
   rconst_iterator rbegin() const { return _table.rbegin(); }
   rconst_iterator rend()   const { return _table.rend(); }
   void AddList( const SampleList& x ) { _table.push_back(x); }

   SampleList&       operator[]( const std::string& );
   const SampleList& operator[]( const std::string& ) const;
   bool HasList( const std::string& ) const;
   void Print() const;
   
   SampleMgr& Sample( const std::string& );
   const SampleMgr& Sample( const std::string& ) const;
   bool HasSample( const std::string& ) const;

private:
   std::vector<SampleList> _table;
};

#endif // __SAMPLELISTING_H__
