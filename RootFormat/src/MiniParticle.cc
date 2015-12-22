#include "TstarAnalysis/RootFormat/interface/MiniParticle.h"  

MiniParticle::MiniParticle() {}
MiniParticle::~MiniParticle(){}


const  TLorentzVector& MiniParticle::p4() const{ return _p4; }
double MiniParticle::pt()     const { return _p4.Pt(); }
double MiniParticle::eta()    const { return _p4.Eta();}
double MiniParticle::phi()    const { return _p4.Phi();}
double MiniParticle::energy() const { return _p4.Energy(); }
double MiniParticle::px()     const { return _p4.Px(); }
double MiniParticle::py()     const { return _p4.Py(); }
double MiniParticle::pz()     const { return _p4.Pz(); }
double MiniParticle::mass()   const { return _p4.Mag(); }

