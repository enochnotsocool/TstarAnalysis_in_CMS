import FWCore.ParameterSet.Config as cms

DefaultObjectSelection = cms.PSet(
      #----- Vertex Selection parameters  -------------------------------------------
      Vertex_Minimum_DegreeOfFreedom = cms.double(4.0),
      Vertex_Maximum_Z               = cms.double(24.0),
      Vertex_Maximum_Rho             = cms.double(2.0),

      #----- Muon Selection parameters  ---------------------------------------------
      Muon_Minimum_Pt             = cms.double(30.0 ),
      Muon_Maximum_Eta            = cms.double( 2.1 ),
      Muon_Maximum_Isolation      = cms.double( 0.05),
      Muon_Veto_Minimum_Pt        = cms.double(15.0),
      Muon_Veto_Maximum_Eta       = cms.double( 2.4),
      Muon_Veto_Maximum_Isolation = cms.double( 0.10),

      #----- Electron selection parameters  -----------------------------------------
      Electron_Minimum_Pt       = cms.double(30.0),
      Electron_Maximum_Eta      = cms.double( 2.1),
      Electron_Veto_Minimum_Pt  = cms.double(15.0),
      Electron_Veto_Maximum_Eta = cms.double( 2.4),
      Electron_Mininum_CrackEta = cms.double( 1.44),
      Electron_Maximum_CrackEta = cms.double( 1.57),

      #----- Jet Selection parameters  ----------------------------------------------
      Jet_Minimum_Pt     = cms.double(50.0),
      Jet_Maximum_Eta    = cms.double(2.4),
      Jet_Minimum_DeltaR = cms.double(0.4)
      )
