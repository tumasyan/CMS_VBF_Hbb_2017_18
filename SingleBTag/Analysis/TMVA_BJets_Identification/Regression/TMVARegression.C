#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/TMVARegGui.h"


using namespace TMVA;

void TMVARegression( TString myMethodList = "" )
{
   TMVA::Tools::Instance();
   std::cout << std::endl;
   std::cout << "==> Start TMVARegression" << std::endl;

   TString outfileName( "TMVAReg.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVARegression", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression" );
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   dataloader->AddVariable( "ptbj", "PT", "units", 'F' );
   dataloader->AddVariable( "ebj", "Energy", "units", 'F' );
   dataloader->AddVariable( "etabj", "ETA", "units", 'F' );
   dataloader->AddVariable( "btgbj", "BTAG", "units", 'F' );
   dataloader->AddVariable( "btg_D_bj", "BTAG_D", "units", 'F' );
   dataloader->AddVariable( "phibj", "PHI", "units", 'F' );

   dataloader->AddTarget( "ptbq" );
   TFile *input(0);
   TString fname = "./preRegOut.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); 
   }
   else if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }

   std::cout << "--- TMVARegression           : Using input file: " << input->GetName() << std::endl;

   TTree *regTree = (TTree*)input->Get("main");

   // global event weights per tree (see below for setting event-wise weights)
   Double_t regWeight  = 1.0;

   dataloader->AddRegressionTree( regTree, regWeight );

   TCut mycut = ""; // for example: TCut mycut = "abs(var1)<0.5 && abs(var2-0.5)<1";

   dataloader->PrepareTrainingAndTestTree( mycut,
                                         "nTrain_Regression=0:nTest_Regression=0:SplitMode=Random:NormMode=NumEvents:!V" );

   factory->BookMethod( dataloader,  TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=150::BoostType=Grad:Shrinkage=0.1:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=3:MaxDepth=4" ); //NTrees=2000

   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();
   outputFile->Close();

   std::cout << "==> TMVARegression is done!" << std::endl;

   delete factory;
   delete dataloader;
}
