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


 // D-phi
 double phi_Dist(double a, double b){
   if(fabs(a - b) > 3.14159265)
    return 6.2831853 - fabs(a - b);
   return fabs(a - b);
}


void preReg()
{

  TFile *f1 = new TFile("../../Preselected_NTuples/Training__VBFHToBB_M_125__.root");

  TTree *bj1 = (TTree*)f1->Get("Training/B_Jets_True_1");
  TTree *bj2 = (TTree*)f1->Get("Training/B_Jets_True_2");
  TTree *bq = (TTree*)f1->Get("Training/bs");

  Float_t ptbj1;
  Float_t ptbj2;
  Float_t ebj1;
  Float_t ebj2;
  Float_t etabj1;
  Float_t etabj2;
  Float_t btgbj1;
  Float_t btgbj2;
  Float_t btg_D_bj1;
  Float_t btg_D_bj2;
  Float_t phibj1;
  Float_t phibj2;

  Float_t ptbq1;
  Float_t ptbq2;

  bj1->SetBranchAddress("bj1_pt",&ptbj1);
  bj2->SetBranchAddress("bj2_pt",&ptbj2);
  bj1->SetBranchAddress("bj1_e",&ebj1);
  bj2->SetBranchAddress("bj2_e",&ebj2);
  bj1->SetBranchAddress("bj1_eta",&etabj1);
  bj2->SetBranchAddress("bj2_eta",&etabj2);
  bj1->SetBranchAddress("bj1_btg",&btgbj1);
  bj2->SetBranchAddress("bj2_btg",&btgbj2);
  bj1->SetBranchAddress("bj1_btg_D",&btg_D_bj1);
  bj2->SetBranchAddress("bj2_btg_D",&btg_D_bj2);
  bj1->SetBranchAddress("bj1_phi",&phibj1);
  bj2->SetBranchAddress("bj2_phi",&phibj2);

  bq->SetBranchAddress("b1_pt",&ptbq1);
  bq->SetBranchAddress("b2_pt",&ptbq2);

  TFile *f = new TFile("preRegOut.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");

  TNtuple * main = new TNtuple{"main","main","ptbq:ptbj:ebj:etabj:btgbj:btg_D_bj:phibj"};

//***************************************************************************************

// ***********************************************************************************
int i;

for(i=0;i<bj1->GetEntries();i++)
 {
  bj1->GetEntry(i);
  bj2->GetEntry(i);
  bq->GetEntry(i);

  main -> Fill(ptbq1, ptbj1, ebj1, etabj1, btgbj1, btg_D_bj1, phibj1);
  main -> Fill(ptbq2, ptbj2, ebj2, etabj2, btgbj2, btg_D_bj2, phibj2);
 }

  f->Write();
}


