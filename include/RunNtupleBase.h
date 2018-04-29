#ifndef RunNtupleBase_h
#define RunNtupleBase_h

#include "DileptonNtuple.C"
#include "CutRangeInfo.h"
#include "AnalysisInputs.h"
#include "PdfSystematics.h"
#include "mylib.h"

class RunNtupleBase{
public:

  bool DoDebug, PrintYield, ShowData;
  bool RunSystematic;
  bool DrawBinnedYieldPlot;
  bool MakeYieldTable;

  bool MakeShapeFile;
  TString shape_var;
  double shape_x_min, shape_x_max;
  int shape_nbin;
  vector<TH1D *> hist_shapes;
  vector<double> yield_shapes;

  PdfSystematics pdfsyst;
  Long64_t LogEvery;

  THStack *MC_stacked;
  TString find_MCsector(int i_file);

  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  vector<int> MCsector_first_index;
  vector<TString> onlybkgd, samples_to_use;

  TString treeskim;
  TString preselection; // To Get Relative Efficiency, we need to call Nevents_<preselection>

  TString DataPD, channel, channel_for_jetres;
  TString filepath, plotpath, filename_prefix, filename_suffix;
  vector<TString> samples;
  AnalysisInputs analysisInputs;
  void SetSourceSystematics();
  double uncert_lumi, uncert_cf, uncert_fake;

  //==== Signals
  vector<TString> signals;
  vector<double> MaxPunzis;
  double MinEffPresel;
  vector<double> signal_yield_nocut, signal_yield_preselection;

  //==== Cut
  CutRangeInfo cutrangeinfo;

  //==== functions
  RunNtupleBase();
  double PunziFunction(double eff_sig, double bkg_tot, double bkg_err2);
  void printcurrunttime();
  void mkdir(TString path);

  void FillSignalInfo();
  void ClearSignalInfo();
  void AddSamplesToList(vector<TString> bkgs);
  void PrintSampleList();
  void SetCutCard(TString path);
  void Run();
  void BookPlotHist(int n_sample);

  //=== Final Results
  double y_observed;
  double total_bkgs, fake_bkgs, prompt_bkgs, cf_bkgs;
  double total_bkgs_err, fake_bkgs_err, prompt_bkgs_err, cf_bkgs_err;
  vector<double> signal_rate, signal_err, signal_eff;

  double fake_bkgs_stat; // sumw2+FR-propagation
  double prompt_bkgs_stat; // sumw2
  double cf_bkgs_stat; // sumw2
  vector<double> signal_stat;

  double fake_bkgs_syst; // 31%
  double prompt_bkgs_syst; // MCSF uncert
  double cf_bkgs_syst; // 21%



};

RunNtupleBase::RunNtupleBase() : 
DoDebug(false), PrintYield(false), ShowData(false), RunSystematic(false), DrawBinnedYieldPlot(false), MakeYieldTable(false), MakeShapeFile(false), LogEvery(100),
plotpath("")
{

  MC_stacked = new THStack("MC_stacked", "");

}


double RunNtupleBase::PunziFunction(double eff_sig, double bkg_tot, double bkg_err2){

  double den = 1 + sqrt( bkg_tot + bkg_err2 );

  return eff_sig/den;

}


void RunNtupleBase::printcurrunttime(){

  TDatime datime;
  cout << datime.GetYear()<<"/"<<datime.GetMonth()<<"/"<<datime.GetDay()<<" "<<datime.GetHour()<<":"<<datime.GetMinute()<<":"<<datime.GetSecond();

}

void RunNtupleBase::mkdir(TString path){

  if(plotpath==""){
    cout << "[RunNtupleBase::mkdir] plotpath is not set" << endl;
    return;
  }

  if( !gSystem->mkdir(path, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << path << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

}

void RunNtupleBase::FillSignalInfo(){

  if(signals.size()==0){

    cout << "[RunNtupleBase::FillSignalInfo] Not using signal" << endl;
    return;

  }

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString this_filepath = WORKING_DIR+"/data/SignalN_MC.txt";

  //==== Get NoCut/Preselection Entry
  for(unsigned int i=0; i<signals.size(); i++){
    TString filename = "PairNAnalyzer_"+signals.at(i)+"_cat_v8-0-7.root";
    TFile *file = new TFile(filepath+"/Signal/"+filename);
    TH1D *hist_preselection = (TH1D*)file->Get("Nevents_"+channel+"_"+preselection);

    string elline;
    ifstream in(this_filepath);
    int N_MC = -999;
    while(getline(in,elline)){
      std::istringstream is( elline );
      TString samplename;
      is >> samplename;
      is >> N_MC;
      if(samplename==signals.at(i)){
        break;
      }
    }

    if(N_MC==-999) signal_yield_nocut.push_back( 0. );
    else           signal_yield_nocut.push_back( N_MC );

    if(hist_preselection) signal_yield_preselection.push_back( hist_preselection->GetEntries() );
    else                  signal_yield_preselection.push_back( 0. );

    //==== initialize MaxPunzis
    MaxPunzis.push_back(-1);
    file->Close();
    delete file;
  }

}

void RunNtupleBase::ClearSignalInfo(){

  signal_yield_nocut.clear();
  signal_yield_preselection.clear();
  MaxPunzis.clear();

}

void RunNtupleBase::AddSamplesToList(vector<TString> v){

  for(unsigned int i=0; i<v.size(); i++){
    samples.push_back( v.at(i) );
  }

}

void RunNtupleBase::PrintSampleList(){

}

void RunNtupleBase::SetSourceSystematics(){

  uncert_lumi = analysisInputs.CalculatedSysts["Luminosity"];
  uncert_cf = analysisInputs.CalculatedSysts["ChrageFlipSyst"];
  uncert_fake = analysisInputs.CalculatedSysts["FakeLooseID"];

}

void RunNtupleBase::SetCutCard(TString path){

  cutrangeinfo.DoPrint = true;
  cutrangeinfo.ReadCutCard(path);

}

TString RunNtupleBase::find_MCsector(int i_file){

  //cout << endl;
  //for(unsigned int i=0; i<onlybkgd.size(); i++) cout << onlybkgd.at(i) << ", ";
  //cout << endl;
  //for(unsigned int i=0; i<MCsector_first_index.size(); i++) cout << MCsector_first_index.at(i) << ", ";
  //cout << endl;

  for(unsigned int i=0; i<MCsector_first_index.size()-1; i++){
    if(MCsector_first_index.at(i) <= i_file && i_file < MCsector_first_index.at(i+1)){
      return samples_to_use.at(i);
    }
  }
  return samples_to_use.back();
}

void RunNtupleBase::BookPlotHist(int n_sample){

  for(int i=0; i<n_sample; i++){
    TH1D *hist_temp = new TH1D(TString::Itoa(i,10), "", shape_nbin, shape_x_min, shape_x_max);
    hist_shapes.push_back( hist_temp );
    yield_shapes.push_back(0.);
  }

}








#endif
