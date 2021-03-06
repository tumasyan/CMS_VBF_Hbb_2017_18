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

void bdt()
{
   Float_t minvqq,detaqq,dphiqq,btgb1_D,btgb2_D,qtgq1,qtgq2,NJ_ingap,pt_All,pz_All,Njet_20,HTT_rest_20,E_rest_20,minvbb;
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );
   reader->AddVariable( "mqq",                   &minvqq );
   reader->AddVariable( "detaqq",                &detaqq );
   reader->AddVariable( "dphiqq",                &dphiqq );
   reader->AddVariable( "btgb1_D",                 &btgb1_D );
   reader->AddVariable( "btgb2_D",                 &btgb2_D );
   reader->AddVariable( "qtgq1",                 &qtgq1 );
   reader->AddVariable( "qtgq2",                 &qtgq2 );
   reader->AddVariable( "pt_All",                 &pt_All );
   reader->AddVariable( "pz_All",                 &pz_All );
   reader->AddVariable( "Njet_20",                 &Njet_20 );
   reader->AddVariable( "E_rest_20",            &E_rest_20 );
   reader->AddSpectator( "minvbb",                 &minvbb );

   reader->BookMVA("TMVAClassification_BDTG", "dataset/weights/TMVAClassification_BDTG.weights.xml" );

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
   TFile *f14 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_WJetsToQQ_HT400to600_qc19_3j_TuneCP5_.root");
   TFile *f15 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_WJetsToQQ_HT600to800_qc19_3j_TuneCP5_.root");
   TFile *f16 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_WJetsToQQ_HT_800toInf_qc19_3j_TuneCP5_.root");
//ZJets
   TFile *f17 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ZJetsToQQ_HT400to600_qc19_4j_TuneCP5_.root");
   TFile *f18 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ZJetsToQQ_HT600to800_qc19_4j_TuneCP5_.root");
   TFile *f19 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_ZJetsToQQ_HT_800toInf_qc19_4j_TuneCP5_.root");
//DYJets_ToQQ
   TFile *f20 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_DYJetsToQQ_HT180_.root");
// Full Data
   TFile *f21 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_Full_Data_.root");

   TTree * ntpb[] =  { (TTree*)f0->Get("Bkg"),(TTree*)f1->Get("Bkg"),(TTree*)f2->Get("Bkg"),(TTree*)f3->Get("Bkg"),(TTree*)f4->Get("Bkg"),(TTree*)f5->Get("Bkg"),(TTree*)f6->Get("Bkg"),
                        (TTree*)f7->Get("Bkg"),(TTree*)f8->Get("Bkg"),(TTree*)f9->Get("Bkg"),(TTree*)f10->Get("Bkg"),
                        (TTree*)f11->Get("Bkg"),(TTree*)f12->Get("Bkg"),(TTree*)f13->Get("Bkg"),
                        (TTree*)f14->Get("Bkg"),(TTree*)f15->Get("Bkg"),(TTree*)f16->Get("Bkg"),
                        (TTree*)f17->Get("Bkg"),(TTree*)f18->Get("Bkg"),(TTree*)f19->Get("Bkg"),
                        (TTree*)f20->Get("Bkg"),
                        (TTree*)f21->Get("Bkg")
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
  TFile *f = new TFile("BDT_Output.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");

  double xmin=-1;
  double xmax=1;

  TH1D * _BDT_VBF_Hbb  = new TH1D("BDT_VBF_Hbb","BDT_VBF_Hbb",100,xmin,xmax);
  TH1D * _BDT_ggF_Hbb  = new TH1D("BDT_ggF_Hbb","BDT_ggF_Hbb",100,xmin,xmax);
  TH1D * _BDT_QCD  = new TH1D("BDT_QCD","BDT_QCD",100,xmin,xmax);
  TH1D * _BDT_Single_Top  = new TH1D("BDT_Single_Top","BDT_Single_Top",100,xmin,xmax);
  TH1D * _BDT_tt  = new TH1D("BDT_tt","BDT_tt",100,xmin,xmax);
  TH1D * _BDT_WJets  = new TH1D("BDT_WJets","BDT_WJets",100,xmin,xmax);
  TH1D * _BDT_ZJets  = new TH1D("BDT_ZJets","BDT_ZJets",100,xmin,xmax);
  TH1D * _BDT_DYJets = new TH1D("BDT_DYJets","BDT_DYJets",100,xmin,xmax);
  TH1D * _BDT_DATA   = new TH1D("BDT_DATA","BDT_DATA",100,xmin,xmax);
//***************************************************************************************

  for(int k=0;k<nSProc;k++)
   for(int i=0;i<ntps[k]->GetEntries();i++)
    {
     ntps[k]->GetEntry(i);
     minvqq   = MyS_minvqq[k];
     detaqq   = MyS_detaqq[k];
     dphiqq   = MyS_dphiqq[k];
     btgb1_D  = MyS_btgb1_D[k];
     btgb2_D  = MyS_btgb2_D[k];
     qtgq1    = MyS_qtgq1[k];
     qtgq2    = MyS_qtgq2[k];
     NJ_ingap = MyS_NJ_ingap[k];
     pt_All   = MyS_pt_All[k];
     pz_All   = MyS_pz_All[k];
     Njet_20  = MyS_Njet_20[k];
     HTT_rest_20  = MyS_HTT_rest_20[k];
     E_rest_20  = MyS_E_rest_20[k];
     minvbb   = MyS_minvbb[k];
     if(k==0)
      _BDT_VBF_Hbb->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyS_weight[k]);
     if(k==1)
      _BDT_ggF_Hbb->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyS_weight[k]);
    }

  for(int k=0;k<nBProc;k++)
   for(int i=0;i<ntpb[k]->GetEntries();i++)
    {
     ntpb[k]->GetEntry(i);
     minvqq   = MyB_minvqq[k];
     detaqq   = MyB_detaqq[k];
     dphiqq   = MyB_dphiqq[k];
     btgb1_D  = MyB_btgb1_D[k];
     btgb2_D  = MyB_btgb2_D[k];
     qtgq1    = MyB_qtgq1[k];
     qtgq2    = MyB_qtgq2[k];
     NJ_ingap = MyB_NJ_ingap[k];
     pt_All   = MyB_pt_All[k];
     pz_All   = MyB_pz_All[k];
     Njet_20  = MyB_Njet_20[k];
     HTT_rest_20  = MyB_HTT_rest_20[k];
     E_rest_20  = MyB_E_rest_20[k];
     minvbb   = MyB_minvbb[k];
     if(k<7)
      _BDT_QCD->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyB_weight[k]);
     else if(k>=7 && k<11)
      _BDT_Single_Top->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyB_weight[k]);
     else if(k>=11 && k<14)
      _BDT_tt->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyB_weight[k]);
     else if(k>=14 && k<17)
      _BDT_WJets->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyB_weight[k]);
     else if(k>=17 && k<20)
      _BDT_ZJets->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyB_weight[k]);
     else if(k==20)
      _BDT_DYJets->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyB_weight[k]);
     else if(k==21)
      _BDT_DATA->Fill(reader->EvaluateMVA("TMVAClassification_BDTG"),MyB_weight[k]);
     if (reader->EvaluateMVA("TMVAClassification_BDTG") < -2)
       {
         cout<<reader->EvaluateMVA("TMVAClassification_BDTG")<<endl;
         cout<<MyB_minvqq[k]<<"   "<<MyB_detaqq[k]<<"   "<<MyB_dphiqq[k]<<"   "<<MyB_btgb1_D[k]<<"   "<<MyB_btgb2_D[k]<<"   "<<MyB_qtgq1[k]<<endl;
       }
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
  delete f20;
  delete f21;
}