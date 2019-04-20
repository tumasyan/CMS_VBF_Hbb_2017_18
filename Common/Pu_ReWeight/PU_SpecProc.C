#include "TStyle.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <math.h>
#include <TF1.h>
#include <TF2.h>
#include <TH1D.h>
#include "TCanvas.h"
#include "TROOT.h"
#include "TNtuple.h"


void PU_SpecProc()
{

//  TFile *f = new TFile("Training__QCD_HT1000to1500_TuneCP5__.root");
//  TFile *f = new TFile("../../Preselected_NTuples/Training__QCD_HT700to1000_TuneCP5__.root");
//  TFile *f = new TFile("../../Preselected_NTuples/Training__QCD_HT500to700_TuneCP5__.root");
  TFile *f = new TFile("../../Preselected_NTuples/Training__QCD_HT300to500_TuneCP5__.root");
//  TFile *f = new TFile("../../Preselected_NTuples/Training__QCD_HT200to300_TuneCP5__.root");
//  TFile *f = new TFile("../../Preselected_NTuples/Training__QCD_HT1000to1500_TuneCP5__.root");
//  TFile *f = new TFile("../../Preselected_NTuples/Training__QCD_HT1500to2000_TuneCP5__.root");
//  TFile *f = new TFile("../../Preselected_NTuples/Training__QCD_HT2000toInf_TuneCP5__.root");
  TTree *other = (TTree*)f->Get("Training/Other_variables");
  Float_t npv;
  other->SetBranchAddress("Tnpv",&npv);

  TFile *f1 = new TFile("PUSPEC.root","RECREATE");
  TH1D *_PUMC = new TH1D("PUMC","PUMC",100,0,100);

  for(int i=0;i<other->GetEntries();i++)
   {
    other->GetEntry(i);
    _PUMC->Fill(npv);
   }
f1->Write();
}


