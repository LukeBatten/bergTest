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

void plotIndivHelium();

void plotIndiv(Int_t run, Int_t COL, TLegend *leg)
{
  
  gStyle->SetOptStat(0);
  TFile *headFile = new TFile( TString::Format("/unix/anita4/helium2/root/run%d/timedHeadFile%d.root",run,run) );
  TTree * headTree = (TTree*)headFile->Get("headTree"); 
  RawAnitaHeader * header = 0;
  headTree->SetBranchAddress("header",&header);
  int headEntries = headTree->GetEntries();

  // For the He2 extra runs: Entries aren't in order w/ realTime or eventNumber, and all over the place...
  // Find min, max manually

  UInt_t firstRealTime = 1483001655;
  UInt_t lastRealTime = 1483047115;

  TH1D *h = new TH1D(Form("h"), Form("Last flight run + additional runs from He2 drive;realTime;Entries"), 10000, firstRealTime, lastRealTime);

  for (unsigned int entry=0;entry<headEntries;entry++)
    {
      headTree->GetEntry(entry);

      h->Fill(header->realTime);
    }

  h->SetLineColor(COL);
  h->SetLineWidth(4);
  h->Draw("same");
  h->GetXaxis()->SetTimeDisplay(1);
  h->GetXaxis()->SetTimeFormat("%b %d, %H:%M");
  
  leg->AddEntry(h,TString::Format("Run %d",run),"blob");

  return;
}

void plotIndivHelium()
{
  
  TLegend* leg = new TLegend(0.4,0.6,0.55,0.9);
  
  plotIndiv(0,1,leg);
  plotIndiv(1,2,leg);
  plotIndiv(367,880,leg);
  plotIndiv(12084,8,leg);
  plotIndiv(12085,800,leg);
  plotIndiv(12086,4,leg);

  leg->Draw();
  
  return;
  
}
