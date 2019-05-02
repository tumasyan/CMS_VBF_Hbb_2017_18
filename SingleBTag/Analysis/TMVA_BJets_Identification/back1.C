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


void back1()
{

  TFile *f1 = new TFile("../../Preselected_NTuples/Training__VBFHToBB_M_125__.root");
  TFile *f2 = new TFile("For_BB_MVA_Training.root");
  double pi=3.14159265;

//*************************************** True b-jets ***************************************
  TTree *partb1 = (TTree*)f1->Get("Training/B_Jets_True_1");
  TTree *partb2 = (TTree*)f1->Get("Training/B_Jets_True_2");
  TTree *rec_b = (TTree*)f2->Get("bb");

  Float_t ptb1_True;
  Float_t ptb2_True;
  Float_t pt_rec;

  partb1->SetBranchAddress("bj1_pt",&ptb1_True);
  partb2->SetBranchAddress("bj2_pt",&ptb2_True);
  rec_b->SetBranchAddress("pt",&pt_rec);
 

  TFile *f = new TFile("preRegOut.root","RECREATE");
  gStyle->SetOptFile(0);
  // gStyle->SetOptStat("mre");
  // gStyle->SetPaintTextFormat("1.2e");

  TTree * main = new TTree{"main","main"};

//***************************************************************************************

// ***********************************************************************************
int i;
  Float_t pt_true;



 TBranch * mc_pt = main->Branch("mc_pt",&pt_true,"mc_pt");

for(i=0;i<partb1->GetEntries();i++)
 {
  partb1->GetEntry(i);
  partb2->GetEntry(i);

  pt_true = ptb1_True; 
  // main->Fill()

  mc_pt -> Fill();
  pt_true = ptb2_True; 
  // main->Fill()

  mc_pt -> Fill();

  // mc_pt -> Fill(ptb2_True);
 }
// main-> Write();


 TBranch *rec_pt = main->Branch("rec_pt",&pt_rec,"rec_pt");

 for(i=0;i<rec_b->GetEntries();i++)
 {
  rec_b -> GetEntry(i);
  rec_pt -> Fill();
  // main->Fill()
  // rec_bb -> Fill(pt_rec);
  // mc_bb->SetBranchAddress("rec_pt",&pt_rec);
 }
// main->Fill();
// cout<<rec_b->GetEntries()<<endl;
main-> Print();
// main-> Write();
// ******************************************************************************

  f-> Write();
  // f-> Close();
  delete f;
}


