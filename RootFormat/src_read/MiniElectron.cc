#include "MiniElectron.h"
#include "ParticleReader.h"

const TLorentzVector& MiniElectron::Vec() { return ElectronBranches._VecList[ _index ]; }
