#ifndef __MINIMuon_H__
#define __MINIMuon_H__

class MiniMuon
{
public:
   MiniMuon( size_t x ) { _index = x ; } 
   virtual ~MiniMuon ();

   
  const TLorentzVector& Vec();
  const float& trackRelIso();

private:
   size_t index ;
};


#endif // __Muon_H__
