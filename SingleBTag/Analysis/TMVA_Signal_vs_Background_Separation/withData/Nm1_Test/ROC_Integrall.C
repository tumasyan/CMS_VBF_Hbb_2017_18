#include <iostream>
#include "TFile.h"

void ROC_Integrall()
{
  TFile * f0  = new TFile("../TMVA.root");
  TH1F * roc  = (TH1F*)f0->Get("dataset/Method_BDTG/BDTG/MVA_BDTG_rejBvsS");
  roc->Draw();
  cout<<roc->Integral(1,100)/100<<endl;
}

