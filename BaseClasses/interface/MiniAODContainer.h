/*******************************************************************************
 *
 *  Filename    : MiniAODContainter.h
 *  Description : A Dummy object containing common miniAOD interactive objects
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#ifndef __MINIAODCONTAINTER_H__
#define __MINIAODCONTAINTER_H__

//----- MiniAOD object interaction  --------------------------------------------
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

//------------------------------------------------------------------------------ 
//   Beginning code segments for common use
//------------------------------------------------------------------------------
#define MINIAOD_OBJS                                            \
   edm::InputTag _hltsrc;                                       \
   edm::InputTag _rhosrc ;                                      \
   edm::InputTag _metsrc  ;                                     \
   edm::InputTag _pileupsrc;                                    \
   edm::InputTag _beamspotsrc ;                                 \
   edm::InputTag _vertexsrc ;                                   \
   edm::InputTag _muonsrc ;                                     \
   edm::InputTag _elecsrc ;                                     \
   edm::InputTag _jetsrc  ;                                     \
   edm::InputTag _gensrc  ;                                     \
   edm::InputTag _lhesrc  ;                                     \
   edm::Handle<edm::TriggerResults>            _triggerResults; \
   edm::Handle<double>                         _rho;            \
   edm::Handle<std::vector<pat::MET>>          _metList;        \
   edm::Handle<std::vector<PileupSummaryInfo>> _pileupList;     \
   edm::Handle<reco::VertexCollection>         _vertexList;     \
   edm::Handle<reco::BeamSpot>                 _beamSpot;       \
   edm::Handle<edm::View<pat::Jet>>            _jetList;        \
   edm::Handle<edm::View<pat::Muon>>           _muonList;       \
   edm::Handle<edm::View<reco::GsfElectron>>   _electronList;   \
   edm::Handle<GenEventInfoProduct>            _genHandle;      \
   edm::Handle<LHEEventProduct>                _lheHandle;      \
   edm::Service<TFileService> fs;                               \
   TFileDirectory results ;

#define GET_MINIAOD_LABELS\
   _hltsrc      = iConfig.getUntrackedParameter<edm::InputTag>( "hltsrc"     , edm::InputTag("TriggerResults::HLT"           )  ) ;\
   _rhosrc      = iConfig.getUntrackedParameter<edm::InputTag>( "rhosrc"     , edm::InputTag("fixedGridRhoFastjetAll"        )  ) ;\
   _metsrc      = iConfig.getUntrackedParameter<edm::InputTag>( "metsrc"     , edm::InputTag("slimmedMETs"                   )  ) ;\
   _pileupsrc   = iConfig.getUntrackedParameter<edm::InputTag>( "pileupsrc"  , edm::InputTag("slimmedAddPileupInfo"          )  ) ;\
   _vertexsrc   = iConfig.getUntrackedParameter<edm::InputTag>( "vertexsrc"  , edm::InputTag("offlineSlimmedPrimaryVertices" )  ) ;\
   _beamspotsrc = iConfig.getUntrackedParameter<edm::InputTag>( "beamspotsrc", edm::InputTag("offlineBeamSpot"               )  ) ;\
   _muonsrc     = iConfig.getUntrackedParameter<edm::InputTag>( "muonsrc"    , edm::InputTag("slimmedMuons"                  )  ) ;\
   _elecsrc     = iConfig.getUntrackedParameter<edm::InputTag>( "elecsrc"    , edm::InputTag("slimmedElectrons"              )  ) ;\
   _jetsrc      = iConfig.getUntrackedParameter<edm::InputTag>( "jetsrc"     , edm::InputTag("slimmedJets"                   )  ) ;\
   _gensrc      = iConfig.getUntrackedParameter<edm::InputTag>( "gensrc"     , edm::InputTag("generator"                     )  ) ;\
   _lhesrc      = iConfig.getUntrackedParameter<edm::InputTag>( "lhesrc"     , edm::InputTag("externalLHEProducer"           )  ) ;\
   results      = TFileDirectory( fs->mkdir( "results"                                                                       )  ) ;

#define GET_MINIAOD_OBJS\
   iEvent.getByLabel( _hltsrc      , _triggerResults ) ;\
   iEvent.getByLabel( _rhosrc      , _rho            ) ;\
   iEvent.getByLabel( _metsrc      , _metList        ) ;\
   iEvent.getByLabel( _pileupsrc   , _pileupList     ) ;\
   iEvent.getByLabel( _vertexsrc   , _vertexList     ) ;\
   iEvent.getByLabel( _beamspotsrc , _beamSpot       ) ;\
   iEvent.getByLabel( _muonsrc     , _muonList       ) ;\
   iEvent.getByLabel( _jetsrc      , _jetList        ) ;\
   iEvent.getByLabel( _elecsrc     , _electronList   ) ;\
   iEvent.getByLabel( _gensrc      , _genHandle      ) ;\
   iEvent.getByLabel( _lhesrc      , _lheHandle      ) ;

#endif // __MINIAODCONTAINTER_H__
