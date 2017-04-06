#include "AnitaConventions.h"
#include "UsefulAnitaEvent.h"
#include "AnitaGeomTool.h"
#include "RawAnitaHeader.h"
#include "TimedAnitaHeader.h"
#include "PrettyAnitaHk.h"
#include "FFTtools.h"
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

void plotHelium();

void color_palette();
void plotHelium()
{
  gStyle->SetOptStat(0);

  Int_t run = 12086;
  TFile *headFile = new TFile( TString::Format("/unix/anita4/helium2/root/run%d/timedHeadFile%d.root",run,run) );

  
  TTree * headTree = (TTree*)headFile->Get("headTree"); 
  RawAnitaHeader * header = 0;
  headTree->SetBranchAddress("header",&header);
  int headEntries = headTree->GetEntries();

  // For the He2 extra runs: Entries aren't in order w/ realTime or eventNumber, and all over the place...
  // Find min, max manually
  
  UInt_t firstEvNum = 2147483647;
  UInt_t lastEvNum = 0;
  UInt_t firstRealTime = 2147483647;
  UInt_t lastRealTime = 0;

  UInt_t EvNum = 0;
  UInt_t ReTime = 0;

  for (unsigned int entry=0;entry<headEntries;entry++)
    {
      headTree->GetEntry(entry);
      
      EvNum = header->eventNumber;
      
      if(EvNum < firstEvNum)
	{
	  firstEvNum = EvNum;
	}

      if(EvNum > lastEvNum)
	{
	  lastEvNum = EvNum;
	}

      ReTime = header->realTime;
      
      if(ReTime < firstRealTime)
	{
	  firstRealTime = ReTime;
	}

      if(ReTime > lastRealTime)
	{
	  lastRealTime = ReTime;
	}

    }

  cout << firstEvNum << endl;
  cout << lastEvNum << endl;
  cout << firstRealTime << endl;
  cout << lastRealTime << endl;

  
  TH2D *h = new TH2D(Form("h"), Form("Run %d ; realTime; eventNumber", run), 10000, firstRealTime, lastRealTime, 10000, firstEvNum, lastEvNum);

  for (unsigned int entry=0;entry<headEntries;entry++)
    {

      headTree->GetEntry(entry);

      h->Fill(header->realTime,header->eventNumber);
      
    }

  h->SetMarkerStyle(20);
  h->SetMarkerSize(0.5);
  h->SetMarkerColor(4);
  //h->Draw("colz");
  h->Draw();
  h->GetXaxis()->SetTimeDisplay(1);
  h->GetXaxis()->SetTimeFormat("%b %d, %H:%M");
     
  return;
  
}

void color_palette(){
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
  Double_t red[NRGBs]   = {0.00, 0.00, 0.87, 1.00, 0.51};
  Double_t green[NRGBs] = {0.00, 0.81, 1.00, 0.20, 0.00};
  Double_t blue[NRGBs]  = {0.51, 1.00, 0.12, 0.00, 0.00};
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

}
