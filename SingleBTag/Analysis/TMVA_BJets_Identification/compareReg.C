#include "TStyle.h"
#include "TGaxis.h"
#include "TRandom.h"

#include <iostream>
#include <math.h>
#include <TF1.h>
#include <TH1D.h>
#include "TCanvas.h"

void compareReg()
{
  gStyle->SetOptFile(0);
  gStyle->SetOptStat(0);

  TCanvas *Convas_1 = new TCanvas();
  TFile* f1 = new TFile("TMVARegApp.root");
  TFile* f2 = new TFile("preRegOut.root");

      TH1D * histo1 = (TH1D*)f1->Get("BDTG");
     TH1D * histo2 = (TH1D*)f2->Get("main/ptbj");
      histo1->Draw();
     histo2->Draw("same");

     // Convas_1->SaveAs("aaa.png");
}