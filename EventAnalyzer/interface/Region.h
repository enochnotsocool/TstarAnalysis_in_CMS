/***************************************************************************************************
 *
 *  Filename    : Region.h
 *  Description : Defining regions as a list of reference to objects
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : This is used to interaction with the EventAnalyzer class
 *                In this class, all of the interaction with external classes would use 
 *                pointers
 *
***************************************************************************************************/

#ifndef __REGION_H__
#define __REGION_H__

class Region {
public:
   Region ();
   virtual ~Region ();
   virtual bool isRegionEvent( const MiniEvent* ) const = 0 ;
   virtual void processEvent( const MiniEvent* ) const = 0 ; 
   virtual void process() const = 0; 

   void pushback( const MiniEvent* ) ;
private:
   std::vector<const MiniEvent*>    _eventList;
};


//-------------------------------------------------------------------------------------------------- 
//   Macros shorthand for inheritance class virtual functions
//-------------------------------------------------------------------------------------------------- 
#define REGION_VIRTUALS( REGION_NAME )                    \
   virtual ~ # REGION_NAME ();                            \
   virtual bool isRegionEvent( const MiniEvent* ) const ; \
   virtual void processEvent( const MiniEvent* ) ;        \
   virtual void process() ;                               \
};

//-------------------------------------------------------------------------------------------------- 
//   Region definitions
//--------------------------------------------------------------------------------------------------
class AA_Signal : public Region {
   REGION_VIRTUALS( AA_Signal ) ;
};

#endif // __REGION_H__

