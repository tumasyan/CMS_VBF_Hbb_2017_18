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

using namespace TMVA;
void mbb_Correlation()
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
   reader->BookMVA("TMVAClassification_BDTG", "../dataset/weights/TMVAClassification_BDTG.weights.xml" );

// ***************************************************************************************************************
   TFile *f0 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/Data_Derived/NTuples_Full_Data_.root");
   TFile *f1 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT200to300_TuneCP5_.root");
   TFile *f2 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT300to500_TuneCP5_.root");
   TFile *f3 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT500to700_TuneCP5_.root");
   TFile *f4 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT700to1000_TuneCP5_.root");
   TFile *f5 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1000to1500_TuneCP5_.root");
   TFile *f6 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT1500to2000_TuneCP5_.root");
   TFile *f7 = TFile::Open("../../../Making_Ntuples_For_SigBkgDiscrimination/MC_Derived/NTuples_QCD_HT2000toInf_TuneCP5_.root");
   TTree * ntpb[] =  { (TTree*)f0->Get("Bkg"),(TTree*)f1->Get("Bkg"),(TTree*)f2->Get("Bkg"),(TTree*)f3->Get("Bkg"),
                       (TTree*)f4->Get("Bkg"),(TTree*)f5->Get("Bkg"),(TTree*)f6->Get("Bkg"),(TTree*)f6->Get("Bkg")
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

   int nbin=20;
   double binw=(2.0/nbin);
   Double_t mbbvMC[20];
   Double_t mbbeMC[20];
   Double_t mbbvData[20];
   Double_t mbbeData[20];
   int fff=0;
   for(int il=0;il<nbin;il++)
   {
    double BDT_Cut_Min=-1+il*binw;
    double BDT_Cut_Max=BDT_Cut_Min+binw;
//***************************************************************************************

  TFile *f = new TFile("xxx.root","RECREATE");
  gStyle->SetOptFile(0);
  gStyle->SetOptStat("mre");
  gStyle->SetPaintTextFormat("1.2e");
  TH1D * _MinvMC    = new TH1D("MC_obs","MC_obs",120,80,200);
  TH1D * _MinvData  = new TH1D("data_obs","data_obs",120,80,200);
//***************************************************************************************

// MC-QCD Samples
  for(int k=1;k<nBProc;k++)
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
     if(reader->EvaluateMVA("TMVAClassification_BDTG")<=BDT_Cut_Min) continue;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")>BDT_Cut_Max) continue;
     if(minvbb>200 || minvbb<80) continue;
     _MinvMC->Fill(minvbb,MyB_weight[k]);
    }

// Data (k=0)
   for(int i=0;i<ntpb[0]->GetEntries();i++)
    {
     ntpb[0]->GetEntry(i);
     minvqq   = MyB_minvqq[0];
     detaqq   = MyB_detaqq[0];
     dphiqq   = MyB_dphiqq[0];
     btgb1_D  = MyB_btgb1_D[0];
     btgb2_D  = MyB_btgb2_D[0];
     qtgq1    = MyB_qtgq1[0];
     qtgq2    = MyB_qtgq2[0];
     NJ_ingap = MyB_NJ_ingap[0];
     pt_All   = MyB_pt_All[0];
     pz_All   = MyB_pz_All[0];
     Njet_20  = MyB_Njet_20[0];
     HTT_rest_20  = MyB_HTT_rest_20[0];
     E_rest_20  = MyB_E_rest_20[0];
     minvbb   = MyB_minvbb[0];
     if(reader->EvaluateMVA("TMVAClassification_BDTG")<=BDT_Cut_Min) continue;
     if(reader->EvaluateMVA("TMVAClassification_BDTG")>BDT_Cut_Max) continue;
     if(minvbb>200 || minvbb<80) continue;
     _MinvData->Fill(minvbb,MyB_weight[0]);
    }

   f->Write();
   mbbvMC[il]=_MinvMC->GetMean();
   mbbeMC[il]=_MinvMC->GetMeanError();
   mbbvData[il]=_MinvData->GetMean();
   mbbeData[il]=_MinvData->GetMeanError();

   fff++;
   delete f;
  }
  delete f0;
  delete f1;
  delete f2;
  delete f3;
  delete f4;
  delete f5;
  delete f6;
  delete f7;
// ********************************* Ploting **********************************
  Double_t bdtv[nbin];
  Double_t bdte[nbin];
  double binCent = -1 + binw/2;
  for(int i=0;i<nbin;i++)
    {
     bdtv[i]=binCent+i*binw;
     bdte[i]=binw/2;
    }
  TCanvas *c1 = new TCanvas("a","a",600,600,700,600);
  TMultiGraph *mg = new TMultiGraph();
  TGraphErrors *gr1 = new TGraphErrors(nbin,bdtv,mbbvData,bdte,mbbeData);
  TGraphErrors *gr2 = new TGraphErrors(nbin,bdtv,mbbvMC,bdte,mbbeMC);

  gr1->SetMarkerStyle(20);
  gr1->SetMarkerColor(2);
  gr1->SetLineColor(2);
  gr1->SetTitle("");

  gr2->SetMarkerStyle(4);
  gr2->SetMarkerColor(4);
  gr2->SetLineColor(4);
  gr2->GetYaxis()->SetTitleOffset(1.4);
  gr2->SetTitle("");

  mg->SetMaximum(200);
  mg->SetMinimum(80);
  mg->Add(gr1);
  mg->Add(gr2);
  mg->Draw("ap");
  mg->GetXaxis()->SetTitle("BDT-out");
  mg->GetYaxis()->SetTitle("< m_{bb} > (GeV)");
  mg->GetYaxis()->SetTitleOffset(1.4);
  gPad->Update();

  TLegend *leg = new TLegend(0.6, 0.7, 0.8, 0.8);
  leg->SetFillColor(0);
  leg->SetLineWidth(0);
  leg->AddEntry(gr1, "2017F Data", "lp");
  leg->AddEntry(gr2, "QCD MC", "lp");
  leg->Draw();



}

