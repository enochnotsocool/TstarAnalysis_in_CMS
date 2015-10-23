#include "MiniJet.h"
#include "ParticleReader.h"

const float& MiniJet::Pt() { return JetBranches._PtList[ _index ]; }const float& MiniJet::Eta() { return JetBranches._EtaList[ _index ]; }const float& MiniJet::Phi() { return JetBranches._PhiList[ _index ]; }const float& MiniJet::Energy() { return JetBranches._EnergyList[ _index ]; }
