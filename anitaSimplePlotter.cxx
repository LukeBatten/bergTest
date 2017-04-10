// Trivial program to plot lat and long onto continent either manually or from GPS data

#include "AntarcticaMapPlotter.h"
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

Int_t resSize = 512;

void anitaSimplePlotter()
{

  std::cout << "Simple functions to map location" << std::endl;
  
}

//////// Simple functions below

// Enter your lat, long and command line to draw position on the Antarctic continent
void interactiveEntry()
{

  AntarcticaMapPlotter* amp = new AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  Double_t latitude, longitude;
  
  std::cout << "Enter the latitude: " << std::endl;
  std::cin >> latitude;
  std::cout << "Enter the longitude: " << std::endl;
  std::cin >> longitude;

  amp->Fill(-latitude, longitude);
  
  amp->DrawHist("colz");

  return;

}

void manualEntry(Double_t latitude, Double_t longitude)
{

  AntarcticaMapPlotter* amp = new AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  amp->Fill(-latitude, longitude);
  
  amp->DrawHist("colz");

  return;

}

/// Plots full run lat and long on map
void findFromADU5Adata(Int_t run)
{

  AntarcticaMapPlotter* amp = new AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  TFile *adu5AFile = new TFile( TString::Format("/unix/anita4/flight2016/root/run%d/gpsFile%d.root",run,run) );
  TTree * adu5PatTree = (TTree*)adu5AFile->Get("adu5PatTree"); 
  Adu5Pat * pat = 0;
  adu5PatTree->SetBranchAddress("pat",&pat);
  UInt_t maxEntries = adu5PatTree->GetEntries();
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      adu5PatTree->GetEntry(entry);
      
      amp->Fill(-1 * pat->latitude, pat->longitude);
    }
  
  amp->DrawHist("colz");
  
  
}

/// Plots full run lat and long on map for a range of runs
void findFromADU5Adata(Int_t firstRun, Int_t lastRun)
{

  AntarcticaMapPlotter* amp = new AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  FileStat_t staty;
  char adu5AName[FILENAME_MAX];
  
  TChain *adu5AChain = new TChain("adu5PatTree");

   for (int run=firstRun;run<lastRun+1; run++)
    { 
      sprintf(adu5AName,"/unix/anita4/flight2016/root/run%d/gpsFile%d.root",run,run);
      if(gSystem->GetPathInfo(adu5AName,staty))
	{
	  continue;
	}
      adu5AChain->Add(adu5AName);
    }
  
  Adu5Pat * pat = 0;
  adu5AChain->SetBranchAddress("pat",&pat);
  UInt_t maxEntries = adu5AChain->GetEntries();
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      adu5AChain->GetEntry(entry);
      
      amp->Fill(-1 * pat->latitude, pat->longitude);
    }
  
  amp->DrawHist("colz");
  
  
}
