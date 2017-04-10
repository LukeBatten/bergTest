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
#include "G12Pos.h"
#include "TFile.h"
#include "TTree.h"
#include "TF2.h"
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

Int_t resSize = 2048;

void anitaSimplePlotter()
{

  std::cout << "Simple functions to map location" << std::endl;
  
}

TString mapName = "antarcticaIceMapBWa4.png";


//////// Simple functions below

// Enter your lat, long and command line to draw position on the Antarctic continent
void interactiveEntry()
{

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

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

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  amp->Fill(-latitude, longitude);
  
  amp->DrawHist("colz");

  return;

}


//// FROM ADU5A DATA

void findFromADU5Adata(Int_t run)
{

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

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

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

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

//// ADU5B DATA

void findFromADU5Bdata(Int_t run)
{

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  TFile *adu5BFile = new TFile( TString::Format("/unix/anita4/flight2016/root/run%d/gpsFile%d.root",run,run) );
  TTree * adu5BPatTree = (TTree*)adu5BFile->Get("adu5bPatTree"); 
  Adu5Pat * pat = 0;
  adu5BPatTree->SetBranchAddress("pat",&pat);
  UInt_t maxEntries = adu5BPatTree->GetEntries();
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      adu5BPatTree->GetEntry(entry);
      
      amp->Fill(-1 * pat->latitude, pat->longitude);
    }
  
  amp->DrawHist("colz");
    
}

/// Plots full run lat and long on map for a range of runs
void findFromADU5Bdata(Int_t firstRun, Int_t lastRun)
{

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  FileStat_t staty;
  char adu5BName[FILENAME_MAX];
  
  TChain *adu5BChain = new TChain("adu5bPatTree");

  for (int run=firstRun;run<lastRun+1; run++)
    { 
      sprintf(adu5BName,"/unix/anita4/flight2016/root/run%d/gpsFile%d.root",run,run);
      if(gSystem->GetPathInfo(adu5BName,staty))
	{
	  continue;
	}
      adu5BChain->Add(adu5BName);
    }
  
  Adu5Pat * pat = 0;
  adu5BChain->SetBranchAddress("pat",&pat);
  UInt_t maxEntries = adu5BChain->GetEntries();
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      adu5BChain->GetEntry(entry);
      
      amp->Fill(-1 * pat->latitude, pat->longitude);
    }
  
  amp->DrawHist("colz");
    
}

//// G12 DATA

void findFromG12data(Int_t run)

{
  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  TFile *G12File = new TFile( TString::Format("/unix/anita4/flight2016/root/run%d/gpsFile%d.root",run,run) );
  TTree * G12PosTree = (TTree*)G12File->Get("g12PosTree"); 
  G12Pos * pos = 0;
  G12PosTree->SetBranchAddress("pos",&pos);
  UInt_t maxEntries = G12PosTree->GetEntries();
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      G12PosTree->GetEntry(entry);
      
      amp->Fill(-1 * pos->latitude, pos->longitude);
    }
  
  amp->DrawHist("colz");
    
}

/// Plots full run lat and long on map for a range of runs
void findFromG12data(Int_t firstRun, Int_t lastRun)
{

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  FileStat_t staty;
  char G12Name[FILENAME_MAX];
  
  TChain *G12Chain = new TChain("g12PosTree");

  for (int run=firstRun;run<lastRun+1; run++)
    { 
      sprintf(G12Name,"/unix/anita4/flight2016/root/run%d/gpsFile%d.root",run,run);
      if(gSystem->GetPathInfo(G12Name,staty))
	{
	  continue;
	}
      G12Chain->Add(G12Name);
    }
  
  G12Pos * pos = 0;
  G12Chain->SetBranchAddress("pos",&pos);
  UInt_t maxEntries = G12Chain->GetEntries();
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      G12Chain->GetEntry(entry);
      
      amp->Fill(-1 * pos->latitude, pos->longitude);
    }
  
  amp->DrawHist("colz");
    
}

//// Interpolated / weighted gps data

void findFromADU5Idata(Int_t run)
{

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  TFile *adu5IFile = new TFile( TString::Format("/unix/anita4/flight2016/root/run%d/timedGpsEvent%d.root",run,run) );
  TTree * adu5PatTree = (TTree*)adu5IFile->Get("adu5PatTree"); 
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
void findFromADU5Idata(Int_t firstRun, Int_t lastRun)
{

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest", "Testing", resSize, resSize);

  FileStat_t staty;
  char adu5IName[FILENAME_MAX];
  
  TChain *adu5IChain = new TChain("adu5PatTree");

  for (int run=firstRun;run<lastRun+1; run++)
    { 
      sprintf(adu5IName,"/unix/anita4/flight2016/root/run%d/timedGpsEvent%d.root",run,run);
      if(gSystem->GetPathInfo(adu5IName,staty))
	{
	  continue;
	}
      adu5IChain->Add(adu5IName);
    }
  
  Adu5Pat * pat = 0;
  adu5IChain->SetBranchAddress("pat",&pat);
  UInt_t maxEntries = adu5IChain->GetEntries();
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {
      adu5IChain->GetEntry(entry);
      
      amp->Fill(-1 * pat->latitude, pat->longitude);
    }
  
  amp->DrawHist("colz");
    
}

///////// HIGHLIGHT A SET OF RUNS FROM THE WHOLE FLIGHT
// firstRun and lastRun are the runs you wish to plot in total
// runToHighlight and runToHighlight2 are the runs you wish to highlight

// Two uses:

// void highlightRun(80, 90) plots the full flight but highlights runs 80-90

// void highlightRun(80, 90, 70, 100) plots part of the flight (70 - 100) and highlights runs 80-90

void highlightRun(Int_t runToHighlight, Int_t runToHighlight2, Int_t firstRun = 50, Int_t lastRun = 170)
{
  
  void initializeInternals();

  Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter* amp = new Acclaim::AntarcticaMapPlotter::AntarcticaMapPlotter("hTest2", "Testing2", resSize, resSize);

  FileStat_t staty;
  char adu5IName[FILENAME_MAX];
  
  TChain *adu5IChain = new TChain("adu5PatTree");

  for (int run=firstRun;run<lastRun+1; run++)
    { 
      sprintf(adu5IName,"/unix/anita4/flight2016/root/run%d/timedGpsEvent%d.root",run,run);
      if(gSystem->GetPathInfo(adu5IName,staty))
	{
	  continue;
	}
      adu5IChain->Add(adu5IName);
    }
  
  Adu5Pat * pat = 0;
  adu5IChain->SetBranchAddress("pat",&pat);
  UInt_t maxEntries = adu5IChain->GetEntries();

  std::vector<Double_t> latsHighlight;
  std::vector<Double_t> longsHighlight;
  
  std::vector<Double_t> lats;
  std::vector<Double_t> longs;

  Int_t lastSeenRun = 0;

  amp->DrawHist("colz");
  
  std::cout << "Finding points to plot..." << std::endl;

  Int_t highlightCount = 0;
  Int_t nonHighlightCount = 0;
  
  for (unsigned int entry=0;entry<maxEntries;entry++)
    {

      adu5IChain->GetEntry(entry);
      
      if(pat->run > lastSeenRun)
	{
	  std::cout << "Currently on run..." << pat->run << std::endl;
	}
      
      if(pat->run >= runToHighlight && pat->run <= runToHighlight2)
	{
	  latsHighlight.push_back(pat->latitude);
	  longsHighlight.push_back(pat->longitude);
	  highlightCount++;
	}

      else
	{
	  lats.push_back(pat->latitude);
	  longs.push_back(pat->longitude);
	  nonHighlightCount++;
	}

      lastSeenRun = pat->run;
      
    }

  std::cout << "Plotting now (may take a while!)" << std::endl;
  
  amp->addTGraph("grTest", "More Testing", nonHighlightCount, &lats[0], &longs[0]);
  amp->getCurrentTGraph()->SetMarkerStyle(8);
  amp->getCurrentTGraph()->SetMarkerSize(0.8);
  amp->getCurrentTGraph()->SetMarkerColor(2);

  amp->DrawTGraph("psame");

  // Highlight
  amp->addTGraph("grTestHighlight", "More Testing Highlight", highlightCount, &latsHighlight[0], &longsHighlight[0]);
  amp->getCurrentTGraph()->SetMarkerStyle(8);
  amp->getCurrentTGraph()->SetMarkerSize(0.8);
  amp->getCurrentTGraph()->SetMarkerColor(3);    
  //
  
  amp->DrawTGraph("psame");
  
}
