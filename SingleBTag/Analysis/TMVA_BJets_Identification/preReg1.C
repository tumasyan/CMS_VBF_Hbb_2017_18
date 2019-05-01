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


void preReg1()
{

  TFile *f1 = new TFile("../../Preselected_NTuples/Training__VBFHToBB_M_125__.root");
  TFile *f2 = new TFile("For_BB_MVA_Training.root");
  double pi=3.14159265;

//*************************************** True b-jets ***************************************
  TTree *partb1 = (TTree*)f1->Get("Training/B_Jets_True_1");
  TTree *partb2 = (TTree*)f1->Get("Training/B_Jets_True_2");

  TTree *rec_b = (TTree*)f2->Get("bb");

  // TTree *partq1 = (TTree*)f1->Get("Training/Q_Jets_True_1");
  // TTree *partq2 = (TTree*)f1->Get("Training/Q_Jets_True_2");
  Float_t ptb1_True;
  Float_t ptb2_True;
  Float_t pt_rec;

  partb1->SetBranchAddress("bj1_pt",&ptb1_True);
  partb2->SetBranchAddress("bj2_pt",&ptb2_True);
  rec_b->SetBranchAddress("pt",&pt_rec);
 

  TFile *f = new TFile("preRegOut.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");
  TNtuple * tree = new TNtuple{"tree","tree","mc_pt:rec_pt"};
  // TNtuple * rec_bb = new TNtuple{"rec_bb","rec_bb","pt"};

//***************************************************************************************

// ***********************************************************************************

for(int i=0;i<partb1->GetEntries();i++)
 {
  partb1->GetEntry(i);
  // partb2->GetEntry(i);
  rec_b->GetEntry(i);

  tree -> Fill(ptb1_True, pt_rec);
  // mc_bb -> Fill(ptb2_True);
 }

 // for(int i=0;i<rec_b->GetEntries();i++)
 // {
 //  rec_b->GetEntry(i);
 //  rec_bb -> Fill(pt_rec);
 // }
// ******************************************************************************

  f->Write();
}


