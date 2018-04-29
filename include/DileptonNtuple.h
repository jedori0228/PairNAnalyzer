//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 14 17:25:37 2017 by ROOT version 6.08/00
// from TTree Ntp_DiElectron/Ntp_DiElectron
// found on file: DiLeptonAnalyzer_data_DoubleEG_cat_v8-0-7.root
//////////////////////////////////////////////////////////

#ifndef DileptonNtuple_h
#define DileptonNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "CutInfo.h"

// Header file for the classes stored in the TTree if any.

class DileptonNtuple {
public :
  TTree       *fChain;  //!pointer to the analyzed TTree or TChain
  Int_t        fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Double_t      M_N1;
  Double_t      M_N2;
  Double_t      M_Z;
  Double_t      isSS;
  Double_t      HT;
  Double_t      ST;
  Double_t      weight;
  Double_t      weight_err;

  //==== Function to call above varialbes
  double GetVar(TString var);

  // List of branches
  TBranch      *b_M_N1;
  TBranch      *b_M_N2;
  TBranch      *b_M_Z;
  TBranch      *b_isSS;
  TBranch      *b_HT;
  TBranch      *b_ST;
  TBranch      *b_weight;
  TBranch      *b_weight_err;

  DileptonNtuple(TString filename, TString treename, bool pdfSyst=false);
  virtual ~DileptonNtuple();
  virtual Int_t   GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void    Init(TTree *tree);
  virtual void    Loop();
  
  vector<TString> CutVariables;
  vector<TString> CutDirections;
  vector<double> CutValues;
  void SetCutVariablesToUse(TString var, TString cutdir, double cutvalue);
  TH1D *hist_for_error, *hist_for_error_up;
  TH1D *hist_for_tau21_up;

  vector<CutInfo> cutinfos;
  void SetCutVariablesToUse(CutInfo ci);

  bool Pass();

  bool DoDebug;
  bool PrintBool(bool b);
  bool TreeExist;
  bool ReadPdfSystematic;
  bool IsData;

  bool DrawPlot;
  TString plot_var, plot_name;
  double plot_x_min, plot_x_max;
  int plot_nbin;
  TH1D *hist_plot;
  void MakePlotHistogram();
  void FillPlotHistogram();

  //==== Variables To Save
  int unweighted_yield;
  double weighted_yield;

};

#endif

#ifdef DileptonNtuple_cxx
DileptonNtuple::DileptonNtuple(TString filename, TString treename, bool pdfSyst) :
fChain(0),
DoDebug(false),
unweighted_yield(0), weighted_yield(0.)
{

  TH1::SetDefaultSumw2(true);

  TTree *tree;
  TFile *f = new TFile(filename);
  tree = (TTree*)f->Get(treename);

  ReadPdfSystematic = pdfSyst;
  if(filename.Contains("data")) IsData = true;
  else IsData = false;

  Init(tree);
  if(!TreeExist){
    f->Close();
    delete f;
  }

  CutVariables.clear();
  CutDirections.clear();
  CutValues.clear();
/*
  hist_Pdf_Replica = NULL;
  hist_Pdf_Alpha = NULL;
  hist_Pdf_Scale = NULL;

  //cout << "filename = " << filename << endl;
  //cout << "-> ReadPdfSystematic = " << ReadPdfSystematic << endl;
  if(ReadPdfSystematic){
    hist_Pdf_Replica = new TH1D("hist_Pdf_Replica", "", 100, 0., 100.);
    hist_Pdf_Alpha = new TH1D("hist_Pdf_Alpha", "", 7, 0., 7.);
    hist_Pdf_Scale = new TH1D("hist_Pdf_Scale", "", 6, 0., 6.);
  }
*/
}

DileptonNtuple::~DileptonNtuple()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t DileptonNtuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t DileptonNtuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

void DileptonNtuple::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
/*
  PdfWeights = 0;
  ScaleWeights = 0;
*/
  // Set branch addresses and branch pointers
  if (!tree){
    TreeExist = false;
    return;
  }
  TreeExist = true;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("M_N1", &M_N1, &b_M_N1);
  fChain->SetBranchAddress("M_N2", &M_N2, &b_M_N2);
  fChain->SetBranchAddress("M_Z", &M_Z, &b_M_Z);
  fChain->SetBranchAddress("isSS", &isSS, &b_isSS);
  fChain->SetBranchAddress("HT", &HT, &b_HT);
  fChain->SetBranchAddress("ST", &ST, &b_ST);
  fChain->SetBranchAddress("weight", &weight, &b_weight);
  fChain->SetBranchAddress("weight_err", &weight_err, &b_weight_err);

}

double DileptonNtuple::GetVar(TString var){

  if(var=="M_N1") return M_N1;
  else if(var=="M_N2") return M_N2;
  else if(var=="M_Z") return M_Z;
  else if(var=="isSS") return isSS;
  else if(var=="HT") return HT;
  else if(var=="ST") return ST;
  else if(var=="weight") return weight;
  else if(var=="weight_err") return weight_err;
  else{
    cout << "[DileptonNtuple::GetVar] "<<var<<": Wrong Variable Name" << endl;
    return -999;
  }

}

void DileptonNtuple::SetCutVariablesToUse(TString var, TString cutdir, double cutvalue){

  if(DoDebug){
    cout << "[DileptonNtuple::SetCutVariablesToUse] "<<var<<" "<<cutdir<<" "<<cutvalue << endl;
  }
  CutVariables.push_back( var );
  CutDirections.push_back( cutdir );
  CutValues.push_back( cutvalue );

}

void DileptonNtuple::SetCutVariablesToUse(CutInfo ci){

  if(DoDebug){
    cout << "[DileptonNtuple::SetCutVariablesToUse] "<<ci.var<<" "<<ci.cutdir<<" "<<ci.cutvalue << endl;
  }
  cutinfos.push_back( ci );

}

bool DileptonNtuple::Pass(){

  bool outpass = true;

/*
  for(unsigned int i=0; i<CutVariables.size(); i++){

    TString var = CutVariables.at(i);
    TString cutdir = CutDirections.at(i);
    double cutvalue = CutValues.at(i);
*/

  //==== HOTFIX
  int counter = 0;
  bool bool_ml1jj = true;
  bool bool_ml2jj = true;

  for(unsigned int i=0; i<cutinfos.size(); i++){

    TString var    = cutinfos.at(i).var;
    TString cutdir = cutinfos.at(i).cutdir;
    double cutvalue = cutinfos.at(i).cutvalue;

    double value = GetVar(var);

    if(DoDebug){
      cout << "[DileptonNtuple::Pass] "<<var<<" "<<value<<" "<<cutdir<<" "<<cutvalue << endl;
    }

    if(cutdir==">"){
      if( !(value>cutvalue) ) return PrintBool(false);
    }
    else if(cutdir==">="){
      if( !(value>=cutvalue) ) return PrintBool(false);
    }
    else if(cutdir=="<"){
      if( !(value<cutvalue) ) return PrintBool(false);
    }
    else if(cutdir=="<="){
      if( !(value<=cutvalue) ) return PrintBool(false);
    }
    else if(cutdir=="=="){
      if( !(value==cutvalue) ) return PrintBool(false);
    }
    else if(cutdir=="!="){
      if( !(value!=cutvalue) ) return PrintBool(false);
    }

    else{
      cout << "[DileptonNtuple::Cut] cutdir should be >/>=/</<=/==/!= : " << cutdir << endl;
      return PrintBool(false);
    }

  }

  return PrintBool(outpass);

}

bool DileptonNtuple::PrintBool(bool b){

  if(DoDebug){
    if(b) cout << "[DileptonNtuple::PrintBool] returning True" << endl;
    else cout << "[DileptonNtuple::PrintBool] returning False" << endl;
  }
  return b;

}

void DileptonNtuple::MakePlotHistogram(){

  if(!DrawPlot) return;

  hist_plot = new TH1D(plot_name, "", plot_nbin, plot_x_min, plot_x_max);

}

void DileptonNtuple::FillPlotHistogram(){

  if(!DrawPlot) return;

  if(plot_var=="M_N"){
    hist_plot->Fill(M_N1, weight);
    hist_plot->Fill(M_N2, weight);
  }
  else{
    hist_plot->Fill(GetVar(plot_var), weight);
  }

}


#endif // #ifdef DileptonNtuple_cxx








