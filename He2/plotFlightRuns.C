// Quick plotting macro to look at when flight begins

#include "AnitaConventions.h"
#include "UsefulAnitaEvent.h"
#include "AnitaGeomTool.h"
#include "RawAnitaHeader.h"
#include "TimedAnitaHeader.h"
#include "PrettyAnitaHk.h"
#include "FFTtools.h"
#include "TLegend.h"
#include "TurfRate.h"
#include "Adu5Pat.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2.h"
#include "TH1.h"
#include "TColor.h"
#include "TImage.h"
#include "TMath.h"
#include "TStyle.h"
#include "TSystem.h"
#include <iostream>
#include <fstream>
#include "TMarker.h"
#include "TLatex.h"
#include "TEllipse.h"
#include "TLine.h"
#include "TPaveText.h"

void plotFlightRuns();

void plotIndiv(Int_t run, Int_t COL, TLegend *leg)
{
  
  gStyle->SetOptStat(0);
  TFile *gpsFile = new TFile( TString::Format("/unix/anita4/flight2016/root/run%d/gpsFile%d.root",run,run) );
  TTree * adu5PatTree = (TTree*)gpsFile->Get("adu5PatTree"); 
  Adu5Pat * pat = 0;
  adu5PatTree->SetBranchAddress("pat",&pat);
  int maxEntries = adu5PatTree->GetEntries();

  // For the He2 extra runs: Entries aren't in order w/ realTime or eventNumber, and all over the place...
  // Find min, max manually

  UInt_t firstRealTime = 1480692736;
  UInt_t lastRealTime = 1480722241;

  TH2D *h = new TH2D(Form("h"), Form("Flight start altitude;realTime;altitude"), 10000, firstRealTime, lastRealTime, 10000, 36000, 41000);

  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      adu5PatTree->GetEntry(entry);

      h->Fill(pat->realTime, pat->altitude);
    }

  h->SetMarkerColor(COL);
  h->SetLineColor(COL);
  h->SetLineWidth(4);
  h->SetMarkerSize(1.5);
  h->SetMarkerStyle(20);
  h->Draw("same");
  h->GetXaxis()->SetTimeDisplay(1);
  h->GetXaxis()->SetTimeFormat("%H:%M");
  
  leg->AddEntry(h,TString::Format("Run %d",run),"blob");

  return;
}

void plotFlightRuns()
{
  
  TLegend* leg = new TLegend(0.1,0.6,0.25,0.9);
  plotIndiv(40,2,leg);
  plotIndiv(41,1,leg);
  plotIndiv(42,8,leg);
  plotIndiv(43,800,leg);
  plotIndiv(44,4,leg);

  leg->Draw();
  
  return;
  
}
