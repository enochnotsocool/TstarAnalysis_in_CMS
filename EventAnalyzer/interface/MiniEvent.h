/***************************************************************************************************
 *
 *  Filename    : MiniEvent.h
 *  Description : Using a custom Event Class for ease of acces
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
 *  Details     : Here, we will only be storing the objects of interest in a std::vector
 *
***************************************************************************************************/
#ifndef __MINIEVENT_H__
#define __MINIEVENT_H__

class MiniEvent
{
public:
   MiniEvent ();
   virtual ~MiniEvent ();
 
private:
   // Physical object list
   std::vector<Jets>      _jetList;
   std::vector<Muons>     _muonList;
   std::vector<Electrons> _electronList;
   std::vector<Photons>   _photonsList;

   // Event specific objects list
   Double_t    _Event 

};

#endif // __MINIEVENT_H__

