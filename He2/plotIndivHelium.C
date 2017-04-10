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

void plotIndivNTU(Int_t run, Int_t COL, TLegend *leg)
{
  
  gStyle->SetOptStat(0);
  TFile *headFile = new TFile( TString::Format("/unix/anita4/flight2016/root/run%d/timedHeadFile%d.root",run,run) );
  TTree * headTree = (TTree*)headFile->Get("headTree"); 
  RawAnitaHeader * header = 0;
  headTree->SetBranchAddress("header",&header);
  int headEntries = headTree->GetEntries();

  // For the He2 extra runs: Entries aren't in order w/ realTime or eventNumber, and all over the place...
  // Find min, max manually

  UInt_t firstRealTime = 1483001655;
  UInt_t lastRealTime = 1483047115;

  TH1D *h = new TH1D(Form("h"), Form("Last flight run from NTU drive + additional run data from He2 drive;realTime;Entries"), 10000, firstRealTime, lastRealTime);

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
  
  leg->AddEntry(h,TString::Format("NTU Run %d",run),"blob");

  return;
}

void plotIndivHe2(Int_t run, Int_t COL, TLegend *leg)
{
  
  gStyle->SetOptStat(0);
  TFile *headFile = new TFile( TString::Format("/unix/anita4/helium2/root/run%d/timedHeadFile%d.root",run,run) );
  TTree * headTree = (TTree*)headFile->Get("headTree"); 
  RawAnitaHeader * header = 0;
  headTree->SetBranchAddress("header",&header);
  int headEntries = headTree->GetEntries();

  // For the He2 extra runs: Entries aren't in order w/ realTime or eventNumber, and all over the place...
  // Find min, max manually

  UInt_t firstRealTime = 1483001500;
  UInt_t lastRealTime = 1483047300;
  
  //UInt_t firstRealTime = 1483001655;
  //UInt_t lastRealTime = 1483047115;

  TH1D *h = new TH1D(Form("h"), Form("Last flight run from NTU drive + additional run data from He2 drive;realTime;Entries"), 10000, firstRealTime, lastRealTime);

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
  
  leg->AddEntry(h,TString::Format("He2 Run %d",run),"blob");

  return;
}

void plotIndivHelium()
{
  
  TLegend* leg = new TLegend(0.4,0.6,0.55,0.9);
  
  plotIndivHe2(0,1,leg);
  plotIndivHe2(1,2,leg);
  plotIndivHe2(2,3,leg);
  //plotIndivNTU(1,46,leg); //  NOT in this range
  plotIndivHe2(367,7,leg); // Plot this before NTU, as there is more data
  plotIndivNTU(367,6,leg); // 
  plotIndivHe2(12084,8,leg);
  plotIndivHe2(12085,800,leg);
  plotIndivHe2(12086,4,leg);

  leg->Draw();
  
  return;
  
}
