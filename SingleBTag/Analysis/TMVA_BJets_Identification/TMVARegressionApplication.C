/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides a simple example on how to use the trained regression MVAs
/// within an analysis module
///
///  - Project   : TMVA - a Root-integrated toolkit for multivariate data analysis
///  - Package   : TMVA
///  - Exectuable: TMVARegressionApplication
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker

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

void TMVARegressionApplication( TString myMethodList = "" ) 
{
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Mutidimensional likelihood and Nearest-Neighbour methods

   Use["BDTG"]            = 1;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVARegressionApplication" << std::endl;

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   
   // Float_t var1, var2;
   // reader->AddVariable( "var1", &var1 );
   // reader->AddVariable( "var2", &var2 );
   
   Float_t ptbj, ebj, etabj, btgbj, btg_D_bj, phibj;
  
   reader->AddVariable( "ptbj", &ptbj);
   // reader->AddVariable( "ebj", &ebj);
   // reader->AddVariable( "etabj", &etabj);
   // reader->AddVariable( "btgbj", &btgbj);
   // reader->AddVariable( "btg_D_bj", &btg_D_bj); 
   // reader->AddVariable( "phibj",  &phibj);
  
   // dataloader->AddVariable( "ebj", "Energy", "units", 'F' );
   // dataloader->AddVariable( "etabj", "ETA", "units", 'F' );
   // dataloader->AddVariable( "btgbj", "BTAG", "units", 'F' );
   // dataloader->AddVariable( "btg_D_bj", "BTAG_D", "units", 'F' );
   // dataloader->AddVariable( "phibj", "PHI", "units", 'F' );


   // Spectator variables declared in the training have to be added to the reader, too
   // Float_t spec1,spec2;
   // reader->AddSpectator( "spec1:=var1*2",  &spec1 );
   // reader->AddSpectator( "spec2:=var1*3",  &spec2 );

   // --- Book the MVA methods

   TString dir    = "dataset/weights/";
   TString prefix = "TMVARegression";

   // Book method(s)

         TString methodName = "BDTG method";
         TString weightfile = dir + prefix + "_BDTG" + ".weights.xml";
         reader->BookMVA( methodName, weightfile ); 
   
   // Book output histograms

   TH1* h = new TH1F( "BDTG", "BDTG method", 2000, -100, 1000 );
   TH1* h1 = new TH1F( "Target Ptbq", "Target ptbq", 2000, -100, 1000 );
   TH1* h2 = new TH1F( "Ptbj", "Ptbj", 2000, -100, 1000 );
   
   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //
   TFile *input(0);
   TString fname = "./preRegOut.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
   else if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegressionApp        : Using input file: " << input->GetName() << std::endl;

   // --- Event loop

   // Prepare the tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
    TTree* theTree = (TTree*)input->Get("main");
    std::cout << "--- Select signal sample" << std::endl;
    Float_t ptbq;
    theTree->SetBranchAddress( "ptbj", &ptbj );
    theTree->SetBranchAddress( "ptbq", &ptbq );

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries(); ievt++) {

      if (ievt%5000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }

      theTree->GetEntry(ievt);

      // Retrieve the MVA target values (regression outputs) and fill into histograms
      // NOTE: EvaluateRegression(..) returns a vector for multi-target regression
      // Obtaining the regression output
     
         Float_t val = (reader->EvaluateRegression("BDTG method"))[0];
         // cout<<"regValue: "<<val<<endl;
//         Float_t True_pt = val*ptbj;
         h->Fill(val); 
         h1->Fill(ptbq);
         h2->Fill(ptbj);
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   // --- Write histograms

   TFile *target  = new TFile( "TMVARegApp.root","RECREATE" );
   h->Write();
   h1->Write();
   h2->Write();

   target->Close();

   std::cout << "--- Created root file: \"" << target->GetName() 
             << "\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;
}

int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList; 
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(","); 
      methodList += regMethod;
   }
   TMVARegressionApplication(methodList);
   return 0;
}
