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

void plotAllHelium();
void color_palette();

void plotAllHelium()
{
  gStyle->SetOptStat(0);

  FileStat_t staty;
  char headName[FILENAME_MAX];

  RawAnitaHeader *header = 0;
  TChain *headChain = new TChain("headTree");

  std::cout << "Getting runs" << std::endl;
  
  for (int run=0;run<=1; run++)
    {
      sprintf(headName,"/unix/anita4/helium2/root/run%d/timedHeadFile%d.root",run,run);
      
      if(gSystem->GetPathInfo(headName,staty))
	{
	  continue;
	}
      headChain->Add(headName);
    
  }

  for (int run=367;run<=367; run++)
    {
      sprintf(headName,"/unix/anita4/helium2/root/run%d/timedHeadFile%d.root",run,run);
      
      if(gSystem->GetPathInfo(headName,staty))
	{
	  continue;
	}
      headChain->Add(headName);
    
  }

    for (int run=12084;run<=12086; run++)
    {
      sprintf(headName,"/unix/anita4/helium2/root/run%d/timedHeadFile%d.root",run,run);
      
      if(gSystem->GetPathInfo(headName,staty))
	{
	  continue;
	}
      headChain->Add(headName);
    
  }
  
  headChain->SetBranchAddress("header",&header);
  int headEntries = headChain->GetEntries();

  UInt_t firstRealTime = 1483001655;
  UInt_t lastRealTime = 1483039848;

  //TH2D *h = new TH2D(Form("h"), Form("Run %d ; realTime; eventNumber", run), 10000, firstRealTime, lastRealTime, 10000, firstEvNum, lastEvNum);

  TH1D *h = new TH1D(Form("h"), Form("Run 367 + additional runs;Entries;realTime"), 10000, firstRealTime, lastRealTime);

  for (unsigned int entry=0;entry<headEntries;entry++)
    {
      headChain->GetEntry(entry);

      h->Fill(header->realTime);
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
