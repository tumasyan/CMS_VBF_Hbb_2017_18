
void corr_res(){

//  Double_t mbbv[] ={131.001,130.568,130.178,130.046,129.962,129.389,129.105,129.711,129.312,129.017,128.838,128.608,129.327,128.9,128.893,128.385,129.077,127.842,128.401,130.508};
//  Double_t mbbe[] ={0.176679,0.147737,0.171472,0.197273,0.218648,0.238932,0.260601,0.285475,0.309072,0.33116,0.354903,0.370463,0.380301,0.389217,0.405531,0.410608,0.425536,0.463579,0.564854,1.25899};
  Double_t mbbv[] ={131.303,130.991,130.308,130.023,129.764,129.731,129.912,129.741,129.245,129.814,129.722,130.006,130.264,130.188,130.376,130.561,130.378,130.594,130.632,128.891};
  Double_t mbbe[] ={0.161292,0.132349,0.145026,0.154294,0.163717,0.171891,0.180261,0.188319,0.193921,0.204739,0.213573,0.223518,0.232762,0.240763,0.254191,0.274643,0.310838,0.404265,0.670474,6.67484};
  Int_t nbin = sizeof(mbbv)/sizeof(mbbv[0]);
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
  TGraphErrors* gr = new TGraphErrors(nbin,bdtv,mbbv,bdte,mbbe);
//  gr->SetMarkerSize(1.5);
  gr->SetMarkerStyle(20);
  gr->SetMarkerColor(2);
  gr->SetLineColor(2);
  gr->GetXaxis()->SetRangeUser(-1,1);
  gr->GetYaxis()->SetRangeUser(80,200);
  gr->GetXaxis()->SetTitle("BDT-out");
  gr->GetYaxis()->SetTitle("< m_{bb} > (GeV)");
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->SetTitle("");
  gr->Draw("ap");

}