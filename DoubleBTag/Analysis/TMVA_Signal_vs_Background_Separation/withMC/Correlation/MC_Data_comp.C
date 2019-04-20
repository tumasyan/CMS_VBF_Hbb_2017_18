
void MC_Data_comp(){

  Double_t mbbvD[] ={131.027,130.937,130.542,130.028,129.765,129.856,129.697,129.543,129.811,129.55,129.898,129.852,130.298,130.346,130.55,130.5,130.739,130.842,130.769,0};
  Double_t mbbeD[] ={0.173288,0.133602,0.146948,0.155297,0.162225,0.169732,0.176456,0.183109,0.191977,0.199592,0.209451,0.219698,0.228005,0.23542,0.249655,0.271635,0.317,0.441532,0.883601,0};
  Double_t mbbvM[] ={131.029,132.092,130.881,128.79,126.451,130.075,128.722,128.615,127.963,127.639,127.754,128.793,129.371,130.161,128.741,130.689,128.353,128.587,127.02,0};
  Double_t mbbeM[] ={1.23043,0.772879,0.817739,0.872242,0.891227,1.04428,1.08852,1.0198,0.988179,1.28812,1.26974,1.2585,1.10878,1.38326,1.47844,1.43788,1.54259,2.4658,6.13849,0};

  Int_t nbin = sizeof(mbbvD)/sizeof(mbbvD[0]);
  Double_t binw = 2.0/nbin;
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
  TGraphErrors *gr1 = new TGraphErrors(nbin,bdtv,mbbvD,bdte,mbbeD);
  TGraphErrors *gr2 = new TGraphErrors(nbin,bdtv,mbbvM,bdte,mbbeM);

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
  gPad->Update();

  TLegend *leg = new TLegend(0.6, 0.7, 0.8, 0.8);
//  leg->SetFillColor(0);
  leg->SetLineWidth(0);
  leg->AddEntry(gr1, "2017F Data", "lp");
  leg->AddEntry(gr2, "QCD MC", "lp");
  leg->Draw();

}