/*******************************************************************************
 *
 *  Filename    : CombineMgr_PlotLimits.cc
 *  Description : Plotting final limit results
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/CombineMgr.h"
#include "TGraphAsymmErrors.h"

using namespace std;

void CombineMgr::MakeLimitPlots()
{
   const string lim_dir = "./data/limits/" ;
   const unsigned binCount = Tstar_M0700 - Tstar_M1600 + 1; 
   double temp1;
   double temp2;
   double mass[binCount]         = {0};
   double masserr[binCount]      = {0};
   double obs_lim[binCount]      = {0};
   double obs_err[binCount]      = {0};
   double exp_lim[binCount]      = {0};
   double one_sig_up[binCount]   = {0};
   double one_sig_down[binCount] = {0};
   double two_sig_up[binCount]   = {0};
   double two_sig_down[binCount] = {0};

   
   for( int i = Tstar_M0700 ; i > SIGNAL_END ; --i ){
      unsigned bin = -i - 1;
      string lim_file = lim_dir + LimitFile((SampleName)i, "Asymptotic");
      cout << i 
         << " sample id: " << SampleName(i) 
         << " bin:" << bin 
         << "| " << Tstar_M1600 
         << " File name:" << lim_file << endl;
      TFile* file = TFile::Open( lim_file.c_str() );
      TTree* tree = ((TTree*)file->Get("limit"));
      tree->SetBranchAddress( "limit"    , &temp1 );
      tree->SetBranchAddress( "limitErr" , &temp2 );

      tree->GetEntry(0); two_sig_down[bin] = temp1;
      tree->GetEntry(1); one_sig_down[bin] = temp1;
      tree->GetEntry(2); exp_lim[bin]      = temp1; 
      tree->GetEntry(3); one_sig_up[bin]   = temp1;
      tree->GetEntry(4); two_sig_up[bin]   = temp1;

      tree->GetEntry(5); 
      obs_lim[bin] = temp1;  obs_err[bin] = temp2;

      mass[bin]    = MassNumber((SampleName)i) + 50. ;
      masserr[bin] = 50.;

      two_sig_up[bin] -= exp_lim[bin]; 
      one_sig_up[bin] -= exp_lim[bin];
      two_sig_down[bin] = exp_lim[bin] - two_sig_down[bin];
      one_sig_down[bin] = exp_lim[bin] - one_sig_down[bin];
      file->Close();
      
      if( i == int(Tstar_M1600) ) { break; }
   }

   TCanvas* c1 = new TCanvas("c1", "c1", 1000, 600 );
   TGraphAsymmErrors* one_sig = new TGraphAsymmErrors(binCount,mass,exp_lim,masserr,masserr,one_sig_down,one_sig_up);
   TGraphAsymmErrors* two_sig = new TGraphAsymmErrors(binCount,mass,exp_lim,masserr,masserr,two_sig_down,two_sig_up);
   TGraphAsymmErrors* obs     = new TGraphAsymmErrors(binCount,mass,obs_lim,masserr,masserr,obs_err,obs_err);
  
   one_sig->SetFillColor( kGreen  );
   one_sig->SetLineColor( kGreen  );
   one_sig->SetFillStyle(3001);
   two_sig->SetFillColor( kYellow );
   two_sig->SetLineColor( kYellow );
   two_sig->SetFillStyle(3002);
   obs->GetXaxis()->SetTitle( "t^{*} Mass (GeV/c^{2})" );
   obs->GetYaxis()->SetTitle( "#sigma_{ex}/#sigma_{pred}" );

   two_sig->Draw("a3");
   two_sig->Draw("p");
   one_sig->Draw("a3 SAME");
   obs->Draw("ALP SAME");
   c1->SaveAs("./data/plots/limit.eps");

   delete one_sig;
   delete two_sig;
   delete obs ;
   delete c1;
}

