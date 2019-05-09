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

using namespace TMVA;

void RegressionResult( TString myMethodList = "" ) 
{
   TMVA::Tools::Instance();

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    
   
   Float_t ptbj, ebj, etabj, btgbj, btg_D_bj, phibj;
  
   reader->AddVariable( "ptbj", &ptbj);
   reader->AddVariable( "ebj", &ebj);
   reader->AddVariable( "etabj", &etabj);
   reader->AddVariable( "btgbj", &btgbj);
   reader->AddVariable( "btg_D_bj", &btg_D_bj); 
   reader->AddVariable( "phibj",  &phibj);

   TString methodName = "BDTG method";
   TString weightfile = "dataset/weights/TMVARegression_BDTG.weights.xml";
   reader->BookMVA( methodName, weightfile ); 
   
  
   TH1* h = new TH1F( "BDTG", "BDTG method", 100, 0, 2 );
   TH1* h1 = new TH1F( "Target Ptbq", "Target ptbq", 100, 0, 1000 );
   TH1* h2 = new TH1F( "Ptbj", "Ptbj", 100, 0, 2 );
   
   TFile *input(0);
   TString fname = "./preRegOut.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); 
   }
   else if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
  
    std::cout << "--- TMVARegressionApp        : Using input file: " << input->GetName() << std::endl;

    TTree* theTree = (TTree*)input->Get("main");
    Float_t ptbq;
    theTree->SetBranchAddress( "ptbj", &ptbj );
    theTree->SetBranchAddress( "ptbq", &ptbq );

    TStopwatch sw;
    sw.Start();
  
   for (Long64_t ievt=0; ievt<theTree->GetEntries(); ievt++) {

      if (ievt%25000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }

      theTree->GetEntry(ievt);    
      Float_t val = (reader->EvaluateRegression("BDTG method"))[0];

         h->Fill(val/ptbq); 
         // h1->Fill(ptbq);
         h2->Fill(ptbj/ptbq);
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   TFile *target  = new TFile( "RegResult.root","RECREATE" );
   h->Write();
   // h1->Write();
   h2->Write();

   target->Close();
  
   delete reader;
    
   std::cout << "==> Done!" << std::endl << std::endl;
}
