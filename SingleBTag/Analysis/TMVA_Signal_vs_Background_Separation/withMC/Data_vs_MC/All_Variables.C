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

void All_Variables()
{
   TString Var_Name[] = {"PT1","PT2","PT3","PTALL","MINVQQ","DETAQQ","BTG1","BTG2","MINVBB"};
   int Nbin[]         = {50,50,50,100,100,100,100,100,100};
   double Xmin[]      = {100,80,60,100,400,4,0,0,0};
   double Xmax[]      = {500,400,300,1000,3000,10,1,1,500};
   int nVar = sizeof(Var_Name)/sizeof(Var_Name[0]);

for(int variable = 0; variable < nVar; variable++)
 {

// ***************************************************************************************************************
// Signal
   TFile *f00 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_VBFHToBB_M_125_.root");
   TFile *f01 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_GluGluHToBB_M125_.root");
   TTree * ntps[2]    = {(TTree*)f00->Get("Sig"), (TTree*)f01->Get("Sig")};
   TTree * ntps_pt[2] = {(TTree*)f00->Get("Sig_pt"), (TTree*)f01->Get("Sig_pt")};
   int nSProc = sizeof(ntps)/sizeof(ntps[0]);

   Float_t MyS_weight[nSProc],MyS_Var[nSProc];
   for(int k=0;k<nSProc;k++)
   {
    ntps[k]->SetBranchAddress( "weight",     &MyS_weight[k] );
    if(Var_Name[variable]=="PT1")
      ntps_pt[k]->SetBranchAddress( "PT1",   &MyS_Var[k] );
    else if(Var_Name[variable]=="PT2")
      ntps_pt[k]->SetBranchAddress( "PT2",   &MyS_Var[k] );
    else if(Var_Name[variable]=="PT3")
      ntps_pt[k]->SetBranchAddress( "PT3",   &MyS_Var[k] );
    else if(Var_Name[variable]=="PTALL")
      ntps[k]->SetBranchAddress( "pt_All",   &MyS_Var[k] );
    else if(Var_Name[variable]=="MINVQQ")
      ntps[k]->SetBranchAddress( "mqq",      &MyS_Var[k] );
    else if(Var_Name[variable]=="DETAQQ")
      ntps[k]->SetBranchAddress( "detaqq",   &MyS_Var[k] );
    else if(Var_Name[variable]=="BTG1")
      ntps[k]->SetBranchAddress( "btgb1_D",  &MyS_Var[k] );
    else if(Var_Name[variable]=="BTG2")
      ntps[k]->SetBranchAddress( "btgb2_D",  &MyS_Var[k] );
    else if(Var_Name[variable]=="MINVBB")
      ntps[k]->SetBranchAddress( "minvbb",   &MyS_Var[k] );
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

   TTree * ntpb[] = { (TTree*)f0->Get("Bkg"),(TTree*)f1->Get("Bkg"),(TTree*)f2->Get("Bkg"),(TTree*)f3->Get("Bkg"),(TTree*)f4->Get("Bkg"),(TTree*)f5->Get("Bkg"),(TTree*)f6->Get("Bkg"),
                        (TTree*)f7->Get("Bkg"),(TTree*)f8->Get("Bkg"),(TTree*)f9->Get("Bkg"),(TTree*)f10->Get("Bkg"),
                        (TTree*)f11->Get("Bkg"),(TTree*)f12->Get("Bkg"),(TTree*)f13->Get("Bkg"),
                        (TTree*)f14->Get("Bkg"),(TTree*)f15->Get("Bkg"),(TTree*)f16->Get("Bkg"),
                        (TTree*)f17->Get("Bkg"),(TTree*)f18->Get("Bkg"),(TTree*)f19->Get("Bkg"),
                        (TTree*)f20->Get("Bkg"),
                        (TTree*)f21->Get("Bkg")
                      };

   TTree * ntpb_pt[] = { (TTree*)f0->Get("Bkg_pt"),(TTree*)f1->Get("Bkg_pt"),(TTree*)f2->Get("Bkg_pt"),(TTree*)f3->Get("Bkg_pt"),(TTree*)f4->Get("Bkg_pt"),(TTree*)f5->Get("Bkg_pt"),(TTree*)f6->Get("Bkg_pt"),
                           (TTree*)f7->Get("Bkg_pt"),(TTree*)f8->Get("Bkg_pt"),(TTree*)f9->Get("Bkg_pt"),(TTree*)f10->Get("Bkg_pt"),
                           (TTree*)f11->Get("Bkg_pt"),(TTree*)f12->Get("Bkg_pt"),(TTree*)f13->Get("Bkg_pt"),
                           (TTree*)f14->Get("Bkg_pt"),(TTree*)f15->Get("Bkg_pt"),(TTree*)f16->Get("Bkg_pt"),
                           (TTree*)f17->Get("Bkg_pt"),(TTree*)f18->Get("Bkg_pt"),(TTree*)f19->Get("Bkg_pt"),
                           (TTree*)f20->Get("Bkg_pt"),
                           (TTree*)f21->Get("Bkg_pt")
                         };


   int nBProc = sizeof(ntpb)/sizeof(ntpb[0]);

   Float_t MyB_weight[nBProc],MyB_Var[nBProc];
   for(int k=0;k<nBProc;k++)
   {
    ntpb[k]->SetBranchAddress( "weight",     &MyB_weight[k] );
    if(Var_Name[variable]=="PT1")
      ntpb_pt[k]->SetBranchAddress( "PT1",   &MyB_Var[k] );
    else if(Var_Name[variable]=="PT2")
      ntpb_pt[k]->SetBranchAddress( "PT2",   &MyB_Var[k] );
    else if(Var_Name[variable]=="PT3")
      ntpb_pt[k]->SetBranchAddress( "PT3",   &MyB_Var[k] );
    else if(Var_Name[variable]=="PTALL")
      ntpb[k]->SetBranchAddress( "pt_All",   &MyB_Var[k] );
    else if(Var_Name[variable]=="MINVQQ")
      ntpb[k]->SetBranchAddress( "mqq",      &MyB_Var[k] );
    else if(Var_Name[variable]=="DETAQQ")
      ntpb[k]->SetBranchAddress( "detaqq",   &MyB_Var[k] );
    else if(Var_Name[variable]=="BTG1")
      ntpb[k]->SetBranchAddress( "btgb1_D",  &MyB_Var[k] );
    else if(Var_Name[variable]=="BTG2")
      ntpb[k]->SetBranchAddress( "btgb2_D",  &MyB_Var[k] );
    else if(Var_Name[variable]=="MINVBB")
      ntpb[k]->SetBranchAddress( "minvbb",   &MyB_Var[k] );
   }

//***************************************************************************************
  TString Name = Var_Name[variable];

  TFile *f = new TFile(Name+"_Output.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");

  int nbin=Nbin[variable];
  double xmin=Xmin[variable];
  double xmax=Xmax[variable];

  TH1D * _Var_VBF_Hbb  = new TH1D(Name+"_VBF_Hbb",Name+"_VBF_Hbb",nbin,xmin,xmax);
  TH1D * _Var_ggF_Hbb  = new TH1D(Name+"_ggF_Hbb",Name+"_ggF_Hbb",nbin,xmin,xmax);
  TH1D * _Var_QCD  = new TH1D(Name+"_QCD",Name+"_QCD",nbin,xmin,xmax);
  TH1D * _Var_Single_Top  = new TH1D(Name+"_Single_Top",Name+"_Single_Top",nbin,xmin,xmax);
  TH1D * _Var_tt  = new TH1D(Name+"_tt",Name+"_tt",nbin,xmin,xmax);
  TH1D * _Var_WJets  = new TH1D(Name+"_WJets",Name+"_WJets",nbin,xmin,xmax);
  TH1D * _Var_ZJets  = new TH1D(Name+"_ZJets",Name+"_ZJets",nbin,xmin,xmax);
  TH1D * _Var_DYJets = new TH1D(Name+"_DYJets",Name+"_DYJets",nbin,xmin,xmax);
  TH1D * _Var_DATA   = new TH1D(Name+"_DATA",Name+"_DATA",nbin,xmin,xmax);
//***************************************************************************************

  for(int k=0;k<nSProc;k++)
   for(int i=0;i<ntps[k]->GetEntries();i++)
    {
     ntps[k]    -> GetEntry(i);
     ntps_pt[k] -> GetEntry(i);
     if(k==0)
      _Var_VBF_Hbb->Fill(MyS_Var[k],MyS_weight[k]);
     if(k==1)
      _Var_ggF_Hbb->Fill(MyS_Var[k],MyS_weight[k]);
    }

  for(int k=0;k<nBProc;k++)
   for(int i=0;i<ntpb[k]->GetEntries();i++)
    {
     ntpb[k]    -> GetEntry(i);
     ntpb_pt[k] -> GetEntry(i);
     if(k<7)
      _Var_QCD->Fill(MyB_Var[k],MyB_weight[k]);
     else if(k>=7 && k<11)
      _Var_Single_Top->Fill(MyB_Var[k],MyB_weight[k]);
     else if(k>=11 && k<14)
      _Var_tt->Fill(MyB_Var[k],MyB_weight[k]);
     else if(k>=14 && k<17)
      _Var_WJets->Fill(MyB_Var[k],MyB_weight[k]);
     else if(k>=17 && k<20)
      _Var_ZJets->Fill(MyB_Var[k],MyB_weight[k]);
     else if(k==20)
      _Var_DYJets->Fill(MyB_Var[k],MyB_weight[k]);
     else if(k==21)
      _Var_DATA->Fill(MyB_Var[k],MyB_weight[k]);
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

 }   // End of variable loop
}

