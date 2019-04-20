
void MC_Data_comp(){

  Double_t mbbvD[] ={130.962,130.563,130.262,130.186,129.697,129.507,129.114,129.513,129.441,128.605,129.103,128.863,129.161,128.87,129.131,128.18,128.95,128.477,128.08,130.215};
  Double_t mbbeD[] ={0.178722,0.147073,0.171286,0.196899,0.220091,0.236988,0.260555,0.286438,0.307123,0.328885,0.354786,0.369164,0.38412,0.389863,0.405015,0.411115,0.427326,0.4638,0.556749,1.24321};
  Double_t mbbvM[] ={130.871,129.705,129.062,129.558,128.519,124.716,128.844,125.943,129.732,127.954,125.771,127.437,121.353,124.611,131.403,124.636,127.434,125.782,126.742,118.797};
  Double_t mbbeM[] ={1.18115,0.927247,1.08957,1.43043,1.76596,1.38524,1.85119,1.5044,1.82096,1.92269,3.7457,2.09312,2.03009,2.23253,3.05978,2.94994,2.00215,2.42974,2.58977,6.82203};

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