
void Nm1Res(){
  Double_t ROC_Integral[] = {0.844566,0.844184,0.845828,0.838596,0.831358,0.844376,0.843845,0.846177,0.8455,0.824262,0.845238,0.847176};
  double  Variable[] = {0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5,8.5,9.5,10.5,11.5};
  string  VariableS[] = {"Mqq","dEtaqq","dPhiqq","btg1","btg2","qtg1","qtg2","pt_bbqq","pz_bbqq","NJ_20","Erest20","non"};
  Int_t nbin = sizeof(ROC_Integral)/sizeof(ROC_Integral[0]);

  TCanvas* c1 = new TCanvas("a","a",600,600,800,600);
  TGraph*  gr = new TGraph(nbin,Variable,ROC_Integral);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(2);
  gr->SetLineColor(2);
  gr->GetXaxis()->SetRangeUser(0,12.5);
  gr->GetYaxis()->SetRangeUser(0.8,0.95);
  gr->GetXaxis()->SetTitle("");
  gr->GetYaxis()->SetTitle("ROC Area");
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->SetTitle("");

  TAxis *ax = gr->GetHistogram()->GetXaxis();
  Double_t x1 = ax->GetBinLowEdge(1);
  Double_t x2 = ax->GetBinUpEdge(ax->GetNbins());
  gr->GetHistogram()->GetXaxis()->Set(12,x1,x2-0.75);

   for(Int_t k=0;k<nbin;k++){
      gr->GetHistogram()->GetXaxis()->SetBinLabel(k+1,VariableS[k].c_str());
   }

   gr->GetXaxis()->SetNdivisions(50);

  gr->Draw("ap");

  TLine *line = new TLine(0,0.847176,11.8,0.847176);
  line->SetLineColor(4);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();
}