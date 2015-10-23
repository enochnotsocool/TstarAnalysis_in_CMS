#include "MiniElectron.h"
#include "ParticleReader.h"

const float& MiniElectron::Pt() { return ElectronBranches._PtList[ _index ]; }const float& MiniElectron::Eta() { return ElectronBranches._EtaList[ _index ]; }const float& MiniElectron::Phi() { return ElectronBranches._PhiList[ _index ]; }const float& MiniElectron::Energy() { return ElectronBranches._EnergyList[ _index ]; }
