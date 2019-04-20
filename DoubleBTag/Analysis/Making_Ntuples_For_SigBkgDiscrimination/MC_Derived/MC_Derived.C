#include "TStyle.h"
#include "TGaxis.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <math.h>
#include <TF1.h>
#include <TF2.h>
#include <TH1D.h>
#include "TCanvas.h"
#include "TROOT.h"
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include "TString.h"
#include "TSystem.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace std;

// *********************************** Spec Functions ********************************************
// D-phi
double phi_Dist(double a, double b){
   if(fabs(a - b) > 3.14159265)
    return 6.2831853 - fabs(a - b);
   return fabs(a - b);
}

// PU_reweighting
double rew[] = {0,0.798126,18.1207,14.7655,8.96119,2.78256,2.39094,1.80281,1.18334,0.866385,4.50645,5.11604,4.87425,3.63377,2.3087,1.48188,1.03325,0.838923,0.773768,0.741412,0.698234,0.670365,0.687718,0.725647,0.740976,0.720316,0.684778,0.656715,0.639069,0.638062,0.63056,0.628136,0.624424,0.625472,0.628517,0.640495,0.668228,0.711752,0.768685,0.811498,0.860919,0.969558,1.12861,1.35588,1.66454,2.05542,2.50623,2.96154,3.21858,3.36422,3.26354,3.01841,2.63201,2.18626,1.7381,1.3301,0.963607,0.681615,0.465635,0.319755,0.220719,0.153924,0.108758,0.0779425,0.0566201,0.0416081,0.0263959,0.016734,0.0121966,0.00889823,0.00647328,0.00467944,0.00335151,0.00237284,0.00165781,0.000908819,0.000508386,0.000337097,0.000219905,0.000141031,8.88541e-05,5.49556e-05,3.33457e-05,1.98403e-05,9.02122e-06,4.21836e-06,2.36058e-06,1.29579e-06,6.98202e-07,3.69623e-07,1.92468e-07,9.87022e-08,4.99156e-08,1.91257e-08,7.61235e-09,3.69361e-09,1.77501e-09,8.43189e-10,3.99759e-10,1.83632e-10};
//double rew[] = {0,0.00137714,0.175583,0.176614,0.240621,0.12205,0.219626,0.163821,0.12059,0.168279,1.08045,1.75815,2.14515,1.99374,1.65538,1.08036,0.827223,0.734306,0.763496,0.733524,0.725106,0.702037,0.720539,0.758901,0.788013,0.779858,0.738295,0.71627,0.710167,0.689311,0.705671,0.705332,0.709753,0.719683,0.711063,0.737763,0.751315,0.792437,0.855858,0.922826,0.944364,1.0897,1.20121,1.45254,1.79409,2.29608,2.78915,3.33359,3.47341,3.47066,3.40416,2.97055,2.70488,2.14745,1.64201,1.28599,0.878896,0.618772,0.410641,0.286186,0.203391,0.128493,0.091174,0.0667528,0.0440391,0.0307842,0.0196197,0.0127425,0.00861981,0.00597831,0.00431202,0.00274528,0.00140317,0.00105972,0.000596828,0.000330391,0.000300159,0.000102128,0.000107063,2.89811e-05,7.61401e-06,2.47344e-06,1.92642e-06,7.74473e-07,2.25816e-07,1.57773e-07,2.25153e-07,4.71867e-08,1.61435e-08,5.41218e-09,4.44742e-09,0,0,0,0,0,0,0,0,0};

double ReWeight(int npu) {return rew[npu];}

// *********************************** Spec Functions END ****************************************

void MC_Derived()
{
  // Inputs
   double pi=3.14159265;
   double pu_min     = -100.63;
   double PT_min_B1  = 20;
   double PT_min_B2  = 20;
   double PT_min_QQ  = 20;
   double btg_min_B1 = 0.8838;
   double qq_dETA_cut = 2.3;
   double qq_M_cut   = 240;
   double dPHI_Max   = 2.1;
   double btg_min_B2 = 0.5803;

 map<string,pair<double,int>> Processes
 {
  #include "Info_Map/Map.txt"
 };

 for (pair<string, pair<double,int>> Proc : Processes)
 {
  TString TnTname;
  TFile *f1 = new TFile("../../../Preselected_NTuples/Training__" + (TString)Proc.first + "__.root");

   TnTname = "Training/";
   if(Proc.first=="Full_Data" || Proc.first=="Data_5perc")
     TnTname = "Test_On_Data/";

//********************************** Get NTuples and Create New **********************************
  TString Ntuple_Name[7];
  for(int i=0;i<7;i++) {  Ntuple_Name[i] = TnTname + "Reco_Jet_Real_";   Ntuple_Name[i] += i;  }
  TTree *jet[7] = { (TTree*)f1->Get(Ntuple_Name[0]), (TTree*)f1->Get(Ntuple_Name[1]), (TTree*)f1->Get(Ntuple_Name[2]),
                    (TTree*)f1->Get(Ntuple_Name[3]), (TTree*)f1->Get(Ntuple_Name[4]), (TTree*)f1->Get(Ntuple_Name[5]),
                    (TTree*)f1->Get(Ntuple_Name[6])
                  };
  TTree *Other = (TTree*)f1->Get(TnTname+"Other_variables");

  TFile *f = new TFile("NTuples_"+(TString)Proc.first+"_.root","RECREATE");
  TString  Datatype = "Bkg";
  if (Proc.first == "VBFHToBB_M_125" || Proc.first =="GluGluHToBB_M125")
     Datatype = "Sig";

  TNtuple *ntuple = new TNtuple(Datatype,Datatype,"weight:mqq:detaqq:dphiqq:btgb1_D:btgb2_D:qtgq1:qtgq2:NJ_ingap:pt_All:pz_All:Njet_20:HTT_rest_20:E_rest_20:minvbb");

//********************************** Get Variables  **********************************
  Float_t ptj[7],ej[7],etaj[7],phij[7],btgj[7],btgj_D[7],qtgj[7],puidj[7],puidj_I[7];
  for(int k=0;k<7;k++)
  {
   jet[k]->SetBranchAddress("j_pt",&ptj[k]);
   jet[k]->SetBranchAddress("j_e",&ej[k]);
   jet[k]->SetBranchAddress("j_eta",&etaj[k]);
   jet[k]->SetBranchAddress("j_phi",&phij[k]);
   jet[k]->SetBranchAddress("j_btg",&btgj[k]);
   jet[k]->SetBranchAddress("j_btg_D",&btgj_D[k]);
   jet[k]->SetBranchAddress("j_qtg",&qtgj[k]);
   jet[k]->SetBranchAddress("j_puid",&puidj[k]);
   jet[k]->SetBranchAddress("j_puid_I",&puidj_I[k]);
  }

  Float_t Tnpv,Njet_20,HTT_20,E_20,Njet_10,HTT_10,E_10;
  Other->SetBranchAddress("Tnpv",&Tnpv);
  Other->SetBranchAddress("Njet_20",&Njet_20);
  Other->SetBranchAddress("HTT_20",&HTT_20);
  Other->SetBranchAddress("E_20",&E_20);
  Other->SetBranchAddress("Njet_10",&Njet_10);
  Other->SetBranchAddress("HTT_10",&HTT_10);
  Other->SetBranchAddress("E_10",&E_10);

// ***********************************************************************************

for(int i=0;i<jet[0]->GetEntries();i++)
   {
    for(int n=0;n<7;n++)
      jet[n]->GetEntry(i);
    Other->GetEntry(i);

// ************************************************* b-jets selection
    double ptb1   = 0;
    double eb1    = 0;
    double etab1  = 0;
    double phib1  = 0;
    double btgb1  = 0;
    double btgb1_D= 0;
    double qtgb1  = 0;
    double puidb1 = 0;
    double BTG_MAX1=-100;

    double ptb2   = 0;
    double eb2    = 0;
    double etab2  = 0;
    double phib2  = 0;
    double btgb2  = 0;
    double btgb2_D= 0;
    double qtgb2  = 0;
    double puidb2 = 0;
    double BTG_MAX2=-100;


// First b-selection as highest btg
   for(int k=0;k<7;k++)
    if(ptj[k]>PT_min_B1 && btgj[k]>BTG_MAX1 && btgj[k]>=btg_min_B1)
      {
       ptb1   = ptj[k];
       eb1    = ej[k];
       etab1  = etaj[k];
       phib1  = phij[k];
       btgb1  = btgj[k];
       btgb1_D= btgj_D[k];
       qtgb1  = qtgj[k];
       puidb1 = puidj[k];
       BTG_MAX1 = btgj[k];
      }

    if(ptb1<PT_min_B1) {continue;}         // No First b-jet

// Second b-jet selection
   for(int k=0;k<7;k++)
    if(ptj[k]>PT_min_B2 && ptj[k]!=ptb1 && btgj[k]>BTG_MAX2 && btgj[k]>=btg_min_B2)
      {
       ptb2   = ptj[k];
       eb2    = ej[k];
       etab2  = etaj[k];
       phib2  = phij[k];
       btgb2  = btgj[k];
       btgb2_D= btgj_D[k];
       qtgb2  = qtgj[k];
       puidb2 = puidj[k];
       BTG_MAX2 = btgj[k];
      }

     if(ptb2<PT_min_B2 || phi_Dist(phib1,phib2)>dPHI_Max) {continue; }      // No Second b-jet

// **************************** Tagging-jets BEGIN
    double ptq1   =0;
    double eq1    =0;
    double etaq1  =0;
    double phiq1  =0;
    double btgq1  =0;
    double btgq1_D=0;
    double qtgq1  =0;
    double puidq1 =0;
    double ptq2   =0;
    double eq2    =0;
    double etaq2  =0;
    double phiq2  =0;
    double btgq2  =0;
    double btgq2_D=0;
    double qtgq2  =0;
    double puidq2 =0;

    int N_Q1=10;
    int N_Q2=10;
    double dETAqq_Max=0;
    for(int m=0;m<6;m++)
     for(int n=m+1;n<7;n++)
      if( (ptj[m]>PT_min_QQ && ptj[m]!=ptb1 && ptj[m]!=ptb2 && puidj[m]>=pu_min) && (ptj[n]>PT_min_QQ && ptj[n]!=ptb1 && ptj[n]!=ptb2 && puidj[n]>=pu_min) )
       {
        double pxqq2 = (ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]))*(ptj[m]*cos(phij[m]) + ptj[n]*cos(phij[n]));
        double pyqq2 = (ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]))*(ptj[m]*sin(phij[m]) + ptj[n]*sin(phij[n]));
        double pzqq2 = (ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]))*(ptj[m]*sinh(etaj[m]) + ptj[n]*sinh(etaj[n]));
        double eqq2  = (ej[m]+ej[n])*(ej[m]+ej[n]);
        if( (sqrt(eqq2-pxqq2-pyqq2-pzqq2) > qq_M_cut) && (fabs(etaj[m]-etaj[n]) > dETAqq_Max) && (fabs(etaj[m]-etaj[n]) > qq_dETA_cut) )
          {
           N_Q1=m;
           N_Q2=n;
           dETAqq_Max = fabs(etaj[N_Q1]-etaj[N_Q2]);
          }
       }

    if(dETAqq_Max<qq_dETA_cut) {continue;}    // No tagging jets

      ptq1   = ptj[N_Q1];
      eq1    = ej[N_Q1];
      etaq1  = etaj[N_Q1];
      phiq1  = phij[N_Q1];
      btgq1  = btgj[N_Q1];
      btgq1_D  = btgj_D[N_Q1];
      qtgq1  = qtgj[N_Q1];
      puidq1 = puidj[N_Q1];
      ptq2   = ptj[N_Q2];
      eq2    = ej[N_Q2];
      etaq2  = etaj[N_Q2];
      phiq2  = phij[N_Q2];
      btgq2  = btgj[N_Q2];
      btgq2_D  = btgj_D[N_Q2];
      qtgq2  = qtgj[N_Q2];
      puidq2 = puidj[N_Q2];

// ***********************************************************************************

    double pxb1 = ptb1*cos(phib1),  pxb2 = ptb2*cos(phib2),  pxq1 = ptq1*cos(phiq1),  pxq2 = ptq2*cos(phiq2);
    double pyb1 = ptb1*sin(phib1),  pyb2 = ptb2*sin(phib2),  pyq1 = ptq1*sin(phiq1),  pyq2 = ptq2*sin(phiq2);
    double pzb1 = ptb1*sinh(etab1), pzb2 = ptb2*sinh(etab2), pzq1 = ptq1*sinh(etaq1), pzq2 = ptq2*sinh(etaq2);

    double minvbb = sqrt( (eb1+eb2)*(eb1+eb2) - (pxb1+pxb2)*(pxb1+pxb2) - (pyb1+pyb2)*(pyb1+pyb2) - (pzb1+pzb2)*(pzb1+pzb2) );
    double minvqq = sqrt( (eq1+eq2)*(eq1+eq2) - (pxq1+pxq2)*(pxq1+pxq2) - (pyq1+pyq2)*(pyq1+pyq2) - (pzq1+pzq2)*(pzq1+pzq2) );
    double pt_All = sqrt((pxb1+pxb2+pxq1+pxq2)*(pxb1+pxb2+pxq1+pxq2) + (pyb1+pyb2+pyq1+pyq2)*(pyb1+pyb2+pyq1+pyq2));
    double pz_All = (pzb1+pzb2+pzq1+pzq2);

    double pt_5 =0;
    double eta_5 =0;
    double puid_5 =-100;
    int    puid_I_5=-10;
    for(int k=0;k<7;k++)
     if(ptj[k]!=ptb1 && ptj[k]!=ptb2 && ptj[k]!=ptq1 && ptj[k]!=ptq2 && puidj[k]> pu_min)
      {
       pt_5=ptj[k];
       eta_5=etaj[k];
       puid_5=puidj[k];
       puid_I_5=puidj_I[k];
       break;
      }

    double pt_6 =0;
    double eta_6 =0;
    double puid_6 =-100;
    for(int k=0;k<7;k++)
     if(ptj[k]!=ptb1 && ptj[k]!=ptb2 && ptj[k]!=ptq1 && ptj[k]!=ptq2 && ptj[k]!=pt_5 && puidj[k]> pu_min)
      {
       pt_6=ptj[k];
       eta_6=etaj[k];
       puid_6=puidj[k];
       break;
      }

    int NJ_ingap=0;
    for(int k=0;k<7;k++)
      if((etaj[k]<etaq1 && etaj[k]>etaq2) || (etaj[k]<etaq2 && etaj[k]>etaq1) )
       if(ptj[k]>20 && puidj[k]>pu_min)
        NJ_ingap++;

// Other_variables - Njets_20, HTT_20, E_20, Njets_10 ...
   double HTT_bbqq    = ptb1+ptb2+ptq1+ptq2;
   double HTT_rest_20 = HTT_20 - HTT_bbqq;
   double HTT_rest_10 = HTT_10 - HTT_bbqq;
   double E_rest_20   = E_20-(eb1+eb2+eq1+eq2);
   double E_rest_10   = E_10-(eb1+eb2+eq1+eq2);

   double weight=1;
   if (TnTname == "Training/")
      weight = ReWeight(Tnpv)*(Proc.second.first*7730.0/(double)Proc.second.second);           // XSec scale factors are added

    ntuple->Fill(weight,minvqq,dETAqq_Max,phi_Dist(phiq1,phiq2),btgb1_D,btgb2_D,qtgq1,qtgq2,NJ_ingap,pt_All,pz_All,Njet_20,HTT_rest_20,E_rest_20,minvbb);
 }

// ******************************************************************************
  ntuple->Write();
  delete f1;

 } // Nproc loop END

}  // END

