/*******************************************************************************
 *
 *  Filename    : ChannelMgr_PlotStyle.cc
 *  Description : Setting Histogram default styles
 *  Author      : Yi-Mu "Enoch" Chen [ ensc@hep1.phys.ntu.edu.tw ]
 *  
*******************************************************************************/
#include "TstarAnalysis/CombineAnalysis/interface/ChannelMgr.h"
#include "THStack.h"
#include "TH1F.h"

//------------------------------------------------------------------------------ 
//   Defining font size
//------------------------------------------------------------------------------
#define AXIS_LABEL_SIZE 10
#define AXIS_TITLE_SIZE 10

void ChannelMgr::setFontStyle( TH1F* hist ) const
{
   hist->SetStats(0);

   // Disable x axis, enable for lower plot
   hist->GetXaxis()->SetLabelSize(0);
   hist->GetXaxis()->SetTitleSize(0);
   hist->GetYaxis()->SetTitleFont(43);
   hist->GetYaxis()->SetLabelFont(43);
   hist->GetYaxis()->SetTitleSize( AXIS_TITLE_SIZE );
   hist->GetYaxis()->SetLabelSize( AXIS_LABEL_SIZE );

}

void ChannelMgr::setXAxisFont( TH1F* hist ) const
{
   hist->GetXaxis()->SetTitleFont(43);
   hist->GetXaxis()->SetLabelFont(43);
   hist->GetXaxis()->SetTitleSize( AXIS_TITLE_SIZE );
   hist->GetXaxis()->SetLabelSize( AXIS_LABEL_SIZE );
}

void ChannelMgr::matchHeights( TH1F* x, TH1F* y ) const
{
   float y_max = 1.2* std::max( x->GetMaximum() , x->GetMaximum() );
   x->SetMaximum( y_max );
   x->SetMaximum( y_max );
}

