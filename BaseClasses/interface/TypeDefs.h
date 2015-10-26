/*******************************************************************************
 *
 *  Filename    : TypeDefs.h
 *  Description : Header for defining types
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

typedef std::vector<const reco::GsfElectron*> ElectronList;
typedef std::vector<const pat::Muon*>         MuonList; 
typedef std::vector<const pat::Jet*>          JetList;
typedef edm::Ptr<reco::GsfElectron>           ElecEDMPtr;

#endif // __TYPEDEFS_H__

