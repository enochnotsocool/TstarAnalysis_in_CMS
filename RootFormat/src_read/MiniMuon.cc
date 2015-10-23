#include "MiniMuon.h"
#include "ParticleReader.h"

const float& MiniMuon::Pt() { return MuonBranches._PtList[ _index ]; }const float& MiniMuon::Eta() { return MuonBranches._EtaList[ _index ]; }const float& MiniMuon::Phi() { return MuonBranches._PhiList[ _index ]; }const float& MiniMuon::Energy() { return MuonBranches._EnergyList[ _index ]; }const float& MiniMuon::trackRelIso() { return MuonBranches._trackRelIsoList[ _index ]; }
