#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

void btg1()
{

// ***************************************************************************************************************
// Signal
   TFile *f00 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_VBFHToBB_M_125_.root");
   TFile *f01 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_GluGluHToBB_M125_.root");
   TTree * ntps[2] = {(TTree*)f00->Get("Sig"), (TTree*)f01->Get("Sig")};
   int nSProc = sizeof(ntps)/sizeof(ntps[0]);
   Float_t MyS_weight[nSProc],MyS_minvqq[nSProc],MyS_detaqq[nSProc],MyS_dphiqq[nSProc],MyS_btgb1_D[nSProc],MyS_btgb2_D[nSProc],MyS_qtgq1[nSProc],MyS_qtgq2[nSProc],MyS_NJ_ingap[nSProc],MyS_pt_All[nSProc],MyS_pz_All[nSProc],MyS_Njet_20[nSProc],MyS_HTT_rest_20[nSProc],MyS_E_rest_20[nSProc],MyS_minvbb[nSProc];

   for(int k=0;k<nSProc;k++)
   {
    ntps[k]->SetBranchAddress( "weight",                   &MyS_weight[k] );
    ntps[k]->SetBranchAddress( "mqq",                   &MyS_minvqq[k] );
    ntps[k]->SetBranchAddress( "detaqq",                &MyS_detaqq[k] );
    ntps[k]->SetBranchAddress( "dphiqq",                &MyS_dphiqq[k] );
    ntps[k]->SetBranchAddress( "btgb1_D",                 &MyS_btgb1_D[k] );
    ntps[k]->SetBranchAddress( "btgb2_D",                 &MyS_btgb2_D[k] );
    ntps[k]->SetBranchAddress( "qtgq1",                 &MyS_qtgq1[k] );
    ntps[k]->SetBranchAddress( "qtgq2",                 &MyS_qtgq2[k] );
    ntps[k]->SetBranchAddress( "NJ_ingap",                 &MyS_NJ_ingap[k] );
    ntps[k]->SetBranchAddress( "pt_All",                 &MyS_pt_All[k] );
    ntps[k]->SetBranchAddress( "pz_All",                 &MyS_pz_All[k] );
    ntps[k]->SetBranchAddress( "Njet_20",                 &MyS_Njet_20[k] );
    ntps[k]->SetBranchAddress( "HTT_rest_20",                 &MyS_HTT_rest_20[k] );
    ntps[k]->SetBranchAddress( "E_rest_20",                 &MyS_E_rest_20[k] );
    ntps[k]->SetBranchAddress( "minvbb",                 &MyS_minvbb[k] );
   }

// QCD
   TFile *f0 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT200to300_TuneCP5_.root");
   TFile *f1 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT300to500_TuneCP5_.root");
   TFile *f2 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT500to700_TuneCP5_.root");
   TFile *f3 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT700to1000_TuneCP5_.root");
   TFile *f4 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1000to1500_TuneCP5_.root");
   TFile *f5 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1500to2000_TuneCP5_.root");
   TFile *f6 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT2000toInf_TuneCP5_.root");
//Single_Top
   TFile *f7  = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ST_tW_top_5f_inclusiveDecays_TuneCP5_.root");
   TFile *f8  = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_.root");
   TFile *f9  = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ST_t_channel_top_4f_inclusiveDecays_TuneCP5_.root");
   TFile *f10 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ST_t_channel_antitop_4f_inclusiveDecays_TuneCP5_.root");
//ttbar
   TFile *f11 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_TTTo2L2Nu_TuneCP5_.root");
   TFile *f12 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_TTToHadronic_TuneCP5_.root");
   TFile *f13 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_TTToSemiLeptonic_TuneCP5_.root");
//WJets
   TFile *f14 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_WJetsToQQ_HT400to600_TuneCP5_.root");
   TFile *f15 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_WJetsToQQ_HT600to800_TuneCP5_.root");
//ZJets
   TFile *f16 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ZJetsToQQ_HT400to600_TuneCP5_.root");
   TFile *f17 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ZJetsToQQ_HT600to800_3j_TuneCP5_.root");
   TFile *f18 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ZJetsToQQ_HT_800toInf_TuneCP5_.root");
//DYJets_ToQQ
   TFile *f19 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_DYJetsToQQ_HT180_.root");
// Full Data
   TFile *f20 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_Full_Data_.root");

   TTree * ntpb[21] = { (TTree*)f0->Get("Bkg"),(TTree*)f1->Get("Bkg"),(TTree*)f2->Get("Bkg"),(TTree*)f3->Get("Bkg"),(TTree*)f4->Get("Bkg"),(TTree*)f5->Get("Bkg"),(TTree*)f6->Get("Bkg"),
                        (TTree*)f7->Get("Bkg"),(TTree*)f8->Get("Bkg"),(TTree*)f9->Get("Bkg"),(TTree*)f10->Get("Bkg"),
                        (TTree*)f11->Get("Bkg"),(TTree*)f12->Get("Bkg"),(TTree*)f13->Get("Bkg"),
                        (TTree*)f14->Get("Bkg"),(TTree*)f15->Get("Bkg"),
                        (TTree*)f16->Get("Bkg"),(TTree*)f17->Get("Bkg"),(TTree*)f18->Get("Bkg"),
                        (TTree*)f19->Get("Bkg"),
                        (TTree*)f20->Get("Bkg")
                      };

   int nBProc = sizeof(ntpb)/sizeof(ntpb[0]);
   Float_t MyB_weight[nBProc],MyB_minvqq[nBProc],MyB_detaqq[nBProc],MyB_dphiqq[nBProc],MyB_btgb1_D[nBProc],MyB_btgb2_D[nBProc],MyB_qtgq1[nBProc],MyB_qtgq2[nBProc],MyB_NJ_ingap[nBProc],MyB_pt_All[nBProc],MyB_pz_All[nBProc],MyB_Njet_20[nBProc],MyB_HTT_rest_20[nBProc],MyB_E_rest_20[nBProc],MyB_minvbb[nBProc];
   for(int k=0;k<nBProc;k++)
   {
    ntpb[k]->SetBranchAddress( "weight",                   &MyB_weight[k]);
    ntpb[k]->SetBranchAddress( "mqq",                   &MyB_minvqq[k]);
    ntpb[k]->SetBranchAddress( "detaqq",                &MyB_detaqq[k]);
    ntpb[k]->SetBranchAddress( "dphiqq",                &MyB_dphiqq[k]);
    ntpb[k]->SetBranchAddress( "btgb1_D",                 &MyB_btgb1_D[k]);
    ntpb[k]->SetBranchAddress( "btgb2_D",                 &MyB_btgb2_D[k]);
    ntpb[k]->SetBranchAddress( "qtgq1",                 &MyB_qtgq1[k]);
    ntpb[k]->SetBranchAddress( "qtgq2",                 &MyB_qtgq2[k]);
    ntpb[k]->SetBranchAddress( "NJ_ingap",                 &MyB_NJ_ingap[k]);
    ntpb[k]->SetBranchAddress( "pt_All",                 &MyB_pt_All[k]);
    ntpb[k]->SetBranchAddress( "pz_All",                 &MyB_pz_All[k]);
    ntpb[k]->SetBranchAddress( "Njet_20",                 &MyB_Njet_20[k]);
    ntpb[k]->SetBranchAddress( "HTT_rest_20",                 &MyB_HTT_rest_20[k]);
    ntpb[k]->SetBranchAddress( "E_rest_20",                 &MyB_E_rest_20[k]);
    ntpb[k]->SetBranchAddress( "minvbb",                 &MyB_minvbb[k]);
   }
//***************************************************************************************
  TFile *f = new TFile("BTG1_Output.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");

  int nbin=100;
  double xmin=0;
  double xmax=1;

  TH1D * _BTG1_VBF_Hbb  = new TH1D("BTG1_VBF_Hbb","BTG1_VBF_Hbb",nbin,xmin,xmax);
  TH1D * _BTG1_ggF_Hbb  = new TH1D("BTG1_ggF_Hbb","BTG1_ggF_Hbb",nbin,xmin,xmax);
  TH1D * _BTG1_QCD  = new TH1D("BTG1_QCD","BTG1_QCD",nbin,xmin,xmax);
  TH1D * _BTG1_Single_Top  = new TH1D("BTG1_Single_Top","BTG1_Single_Top",nbin,xmin,xmax);
  TH1D * _BTG1_tt  = new TH1D("BTG1_tt","BTG1_tt",nbin,xmin,xmax);
  TH1D * _BTG1_WJets  = new TH1D("BTG1_WJets","BTG1_WJets",nbin,xmin,xmax);
  TH1D * _BTG1_ZJets  = new TH1D("BTG1_ZJets","BTG1_ZJets",nbin,xmin,xmax);
  TH1D * _BTG1_DYJets = new TH1D("BTG1_DYJets","BTG1_DYJets",nbin,xmin,xmax);
  TH1D * _BTG1_DATA   = new TH1D("BTG1_DATA","BTG1_DATA",nbin,xmin,xmax);
//***************************************************************************************

  for(int k=0;k<nSProc;k++)
   for(int i=0;i<ntps[k]->GetEntries();i++)
    {
     ntps[k]->GetEntry(i);
     if(k==0)
      _BTG1_VBF_Hbb->Fill(MyS_btgb1_D[k],MyS_weight[k]);
     if(k==1)
      _BTG1_ggF_Hbb->Fill(MyS_btgb1_D[k],MyS_weight[k]);
    }

  for(int k=0;k<nBProc;k++)
   for(int i=0;i<ntpb[k]->GetEntries();i++)
    {
     ntpb[k]->GetEntry(i);
     if(k<7)
      _BTG1_QCD->Fill(MyB_btgb1_D[k],MyB_weight[k]);
     else if(k>=7 && k<11)
      _BTG1_Single_Top->Fill(MyB_btgb1_D[k],MyB_weight[k]);
     else if(k>=11 && k<14)
      _BTG1_tt->Fill(MyB_btgb1_D[k],MyB_weight[k]);
     else if(k>=14 && k<16)
      _BTG1_WJets->Fill(MyB_btgb1_D[k],MyB_weight[k]);
     else if(k>=16 && k<19)
      _BTG1_ZJets->Fill(MyB_btgb1_D[k],MyB_weight[k]);
     else if(k==19)
      _BTG1_DYJets->Fill(MyB_btgb1_D[k],MyB_weight[k]);
     else if(k==20)
      _BTG1_DATA->Fill(MyB_btgb1_D[k],MyB_weight[k]);
    }



  f->Write();
  delete f00;
  delete f01;

  delete f0;
  delete f1;
  delete f2;
  delete f3;
  delete f4;
  delete f5;
  delete f6;
  delete f7;
  delete f8;
  delete f9;
  delete f10;
  delete f11;
  delete f12;
  delete f13;
  delete f14;
  delete f15;
  delete f16;
  delete f17;
  delete f18;
  delete f19;
}

