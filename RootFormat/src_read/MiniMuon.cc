#include "MiniMuon.h"
#include "ParticleReader.h"

const TLorentzVector& MiniMuon::Vec() { return MuonBranches._VecList[ _index ]; }const float& MiniMuon::trackRelIso() { return MuonBranches._trackRelIsoList[ _index ]; }
