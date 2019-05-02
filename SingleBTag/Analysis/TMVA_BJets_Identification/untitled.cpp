void untitled() 
{ 
	TFile *f = new TFile("hs.root","update");
	TTree *T = (TTree*)f->Get("ntuple");
    float px,py;
    float pt;
    TBranch *bpt = T->Branch("pt",&pt,"pt/F");
    T->SetBranchAddress("px",&px);
    T->SetBranchAddress("py",&py);
    Long64_t nentries = T->GetEntries(); 
    for (Long64_t i=0;i<nentries;i++)
     { 
     	T->GetEntry(i);
     	pt = TMath::Sqrt(px*px+py*py);
     	bpt->Fill();
     } 
     T->Print(); 
     T->Write(); 
     delete f; 
 }