/*******************************************************************************
 *
 *  Filename    : ObjectSelection.cc
 *  Description : Constructor and destructor for Object Selector class
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/BaseClasses/interface/ObjectSelection.h"

ObjectSelection::ObjectSelection( const edm::ParameterSet& iConfig ):
   //----- Vertex Selection parameters  -------------------------------------------
   fVertex_Minimum_DegreeOfFreedom( iConfig.getParameter<double>( "Vertex_Minimum_DegreeOfFreedom" )),
   fVertex_Maximum_Z( iConfig.getParameter<double>( "Vertex_Maximum_Z" )),
   fVertex_Maximum_Rho( iConfig.getParameter<double>( "Vertex_Maximum_Rho" )),

   //----- Muon Selection parameters  ---------------------------------------------
   fMuon_Minimum_Pt( iConfig.getParameter<double>( "Muon_Minimum_Pt" )),
   fMuon_Maximum_Eta( iConfig.getParameter<double>( "Muon_Maximum_Eta" )),
   fMuon_Maximum_Isolation( iConfig.getParameter<double>( "Muon_Maximum_Isolation" )),
   fMuon_Veto_Minimum_Pt( iConfig.getParameter<double>( "Muon_Veto_Minimum_Pt" )),
   fMuon_Veto_Maximum_Eta( iConfig.getParameter<double>( "Muon_Veto_Maximum_Eta" )),
   fMuon_Veto_Maximum_Isolation( iConfig.getParameter<double>( "Muon_Veto_Maximum_Isolation" )),
  
   //----- Electron selection parameters  -----------------------------------------
   fElectron_Minimum_Pt( iConfig.getParameter<double>( "Electron_Minimum_Pt" )),
   fElectron_Maximum_Eta( iConfig.getParameter<double>( "Electron_Maximum_Eta" )),
   fElectron_Veto_Minimum_Pt( iConfig.getParameter<double>( "Electron_Veto_Minimum_Pt" )),
   fElectron_Veto_Maximum_Eta( iConfig.getParameter<double>( "Electron_Veto_Maximum_Eta" )),
   fElectron_Mininum_CrackEta( iConfig.getParameter<double>( "Electron_Mininum_CrackEta" )),
   fElectron_Maximum_CrackEta( iConfig.getParameter<double>( "Electron_Maximum_CrackEta" )),

   //----- Jet Selection parameters  ----------------------------------------------
   fJet_Minimum_Pt( iConfig.getParameter<double>( "Jet_Minimum_Pt" )),
   fJet_Maximum_Eta( iConfig.getParameter<double>( "Jet_Maximum_Eta" )),
   fJet_Minimum_DeltaR( iConfig.getParameter<double>( "Jet_Minimum_DeltaR" ))
{
}

ObjectSelection::~ObjectSelection(){}
