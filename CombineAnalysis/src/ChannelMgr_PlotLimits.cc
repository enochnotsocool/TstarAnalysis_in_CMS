/*******************************************************************************
 *
 *  Filename    : ChannelMgr_PlotLimits.cc
 *  Description : Plotting the confidence level plots for a signal channel.
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"

#include "TMultiGraph.h"
#include "TGraphAsymmErrors.h"

using namespace std;

void ChannelMgr::MakeLimitPlot() const
{
   const string savepath = plotfilepath( "limit" );
   const unsigned binCount = Tstar_M0700 - Tstar_M1600 + 1; 
   double temp1;
   // double temp2;
   double mass[binCount]         = {0};
   double masserr[binCount]      = {0};
   double obs_lim[binCount]      = {0};
   double exp_lim[binCount]      = {0};
   double one_sig_up[binCount]   = {0};
   double one_sig_down[binCount] = {0};
   double two_sig_up[binCount]   = {0};
   double two_sig_down[binCount] = {0};

   //----- Getting Limits from file  ---------------------------------------------- 
   for( int i = Tstar_M0700 ; i > SIGNAL_END ; --i ){
      unsigned bin = -i - 1;
      string lim_file = store_combineoutput( (SampleName)i, "Asymptotic" );
      TFile* file = TFile::Open( lim_file.c_str() );
      TTree* tree = ((TTree*)file->Get("limit"));
      tree->SetBranchAddress( "limit"    , &temp1 );
      // tree->SetBranchAddress( "limitErr" , &temp2 );

      tree->GetEntry(0); two_sig_down[bin] = temp1;
      tree->GetEntry(1); one_sig_down[bin] = temp1;
      tree->GetEntry(2); exp_lim[bin]      = temp1; 
      tree->GetEntry(3); one_sig_up[bin]   = temp1;
      tree->GetEntry(4); two_sig_up[bin]   = temp1;

      tree->GetEntry(5); 
      obs_lim[bin] = temp1;  // obs_err[bin] = temp2;

      mass[bin]    = MassNumber((SampleName)i);
      masserr[bin] = 50.;

      two_sig_up[bin] -= exp_lim[bin]; 
      one_sig_up[bin] -= exp_lim[bin];
      two_sig_down[bin] = exp_lim[bin] - two_sig_down[bin];
      one_sig_down[bin] = exp_lim[bin] - one_sig_down[bin];
      file->Close();
   }

   //----- Plot Objects  ----------------------------------------------------------
   TCanvas* c1                = new TCanvas("c1", "c1", 1600, 1000 );
   TMultiGraph* mg            = new TMultiGraph();
   TGraphAsymmErrors* one_sig = new TGraphAsymmErrors(binCount,mass,exp_lim,masserr,masserr,one_sig_down,one_sig_up);
   TGraphAsymmErrors* two_sig = new TGraphAsymmErrors(binCount,mass,exp_lim,masserr,masserr,two_sig_down,two_sig_up);
   TGraph* exp                = new TGraph(binCount,mass,exp_lim);
   TGraph* obs                = new TGraph(binCount,mass,obs_lim);
   TLegend* l                 = new TLegend(0.55,0.65,0.95,0.95);
 
   //----- Setting Styles  --------------------------------------------------------
   one_sig->SetFillColor( kGreen  );
   one_sig->SetLineColor( kGreen  );
   one_sig->SetLineWidth(0);
   one_sig->SetFillStyle(1001);
   two_sig->SetFillColor( kYellow );
   two_sig->SetLineColor( kYellow );
   two_sig->SetLineWidth(0);
   two_sig->SetFillStyle(1002);

   exp->SetLineColor(kBlack);
   exp->SetLineWidth(2);
   exp->SetLineStyle(2);

   obs->SetLineColor(kBlack);
   obs->SetLineWidth(2);
   obs->SetLineStyle(1);

   mg->SetTitle("Exclusion Limit");
   
   l->AddEntry( (TObject*)0 , "" , "" );
   l->AddEntry( (TObject*)0 , "#sqrt{s} = 13TeV,   #int L dt = 2.2pb^{-1}  " , "" );
   l->AddEntry( obs , "CL_{s} Observed" , "l" );
   l->AddEntry( exp , "CL_{s} Expected" , "l" );
   l->AddEntry( one_sig , "CL_{s} Expected #pm 1 #sigma" , "f" );
   l->AddEntry( two_sig , "CL_{s} Expected #pm 2 #sigma" , "f" );
   l->AddEntry( (TObject*)0 , "" , "" );

   //----- Plotting  --------------------------------------------------------------
   mg->Add(two_sig);
   mg->Add(one_sig);
   mg->Add(exp);
   mg->Add(obs);
   mg->Draw("AL3");
   l->Draw();
   mg->GetXaxis()->SetTitle( "t^{*} Mass (GeV/c^{2})" );    // MUST Be after draw!!
   mg->GetYaxis()->SetTitle( "#sigma_{ex}/#sigma_{pred}" ); // https://root.cern.ch/root/roottalk/roottalk09/0078.html
   
   //----- Saving and cleaning up  ------------------------------------------------
   c1->SaveAs( savepath.c_str() );
   delete one_sig;
   delete two_sig;
   delete obs;
   delete exp;
   delete mg;
   delete l;
   delete c1;
}


