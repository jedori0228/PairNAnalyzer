#ifndef PdfSystematics_h
#define PdfSystematics_h

class PdfSystematics{
public :

  PdfSystematics();
  TDirectory *MakeTempDir();

  TH1D *hist_Pdf_Replica;
  TH1D *hist_Pdf_Alpha;
  TH1D *hist_Pdf_Scale;

  TString SampleName;
  bool IsTch();

  double Yield_Central;
  double Syst_Pdf_Replica_Eff;
  double Syst_Pdf_Replica_Den;
  double Syst_Pdf_Replica_Num;

  double Syst_Pdf_Alpha_Eff;
  double Syst_Pdf_Alpha_Den;
  double Syst_Pdf_Alpha_Num;

  double Syst_Pdf_Scale_Eff;
  double Syst_Pdf_Scale_Den;
  double Syst_Pdf_Scale_Num;

  double Syst_Pdf_Total;

  bool SeparateEffDen;
  bool ForXsecLimitOnly;
  bool Debug;

  void CalculatePdfSystematic();

};


PdfSystematics::PdfSystematics(){

  Yield_Central = 0.;
  SeparateEffDen = false;
  ForXsecLimitOnly = false;
  Debug = false;

  hist_Pdf_Replica = NULL;
  hist_Pdf_Alpha= NULL;
  hist_Pdf_Scale= NULL;

}

TDirectory *PdfSystematics::MakeTempDir(){

  gROOT->cd();
  TDirectory* tempDir = 0;
  int counter = 0;
  while (not tempDir) {
    // First, let's find a directory name that doesn't exist yet:                                                                                                                    
    std::stringstream dirname;
    dirname << "HNCommonLeptonFakes_%i" << counter;
    if (gROOT->GetDirectory((dirname.str()).c_str())) {
      ++counter;
      continue;
    }
    // Let's try to make this directory:                                                                                                                                             
    tempDir = gROOT->mkdir((dirname.str()).c_str());

  }

  return tempDir;

}

void PdfSystematics::CalculatePdfSystematic(){

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString filepath = ENV_FILE_PATH+"/"+dataset+"/SignalPDF/";

  TFile *file_Den = new TFile(filepath+"DiLeptonAnalyzer_"+SampleName+"_cat_v8-0-7.root");
  TH1D *hist_Replica_Den = (TH1D *)file_Den->Get("ForTree_PdfWeights");
  TH1D *hist_Scale_Den = (TH1D *)file_Den->Get("ForTree_ScaleWeights");
  TH1D *hist_central_Den = (TH1D *)file_Den->Get("ForTree_Central");

  if(!hist_Replica_Den) return;

  double den_central = hist_central_Den->GetBinContent(1);
  double num_central = Yield_Central;
  double eff_central = Yield_Central/den_central;

  bool istch = IsTch();

  if(Debug){
    cout << "istch = " << istch << endl; 
    cout << "Yield_Central = " << Yield_Central << endl;
    cout << "Pseudo Efficiency = " << eff_central << endl;
    cout << "Den = " << den_central << endl;
  }

  //==== PDF Error

  Syst_Pdf_Replica_Eff = 0.;
  Syst_Pdf_Replica_Den = 0.;
  Syst_Pdf_Replica_Num = 0.;
  int pdferror_start_bin = 0;
  if(istch) pdferror_start_bin = 1; //==== for t-ch, first bin is same as central

  //==== hist_Pdf_Replica : bin1~bin100 are filled
  //==== hist_Replica_Den : for t-ch, bin2~bin101 should be used
  TH1D *for_Syst_Pdf_Replica_Eff = new TH1D("for_Syst_Pdf_Replica_Eff", "", 100, 0., 100.);
  TH1D *for_Syst_Pdf_Replica_Den = new TH1D("for_Syst_Pdf_Replica_Den", "", 100, 0., 100.);
  TH1D *for_Syst_Pdf_Replica_Num = new TH1D("for_Syst_Pdf_Replica_Num", "", 100, 0., 100.);
  for(unsigned int i=1; i<=hist_Pdf_Replica->GetXaxis()->GetNbins(); i++){
    double num = hist_Pdf_Replica->GetBinContent(i);
    double den = hist_Replica_Den->GetBinContent(i+pdferror_start_bin);
    double this_eff = num/den;

    double reldiff_eff = (this_eff-eff_central)/eff_central;
    double reldiff_den = (den-den_central)/den_central;
    double reldiff_num = (num-num_central)/num_central;

    for_Syst_Pdf_Replica_Eff->Fill(reldiff_eff);
    for_Syst_Pdf_Replica_Den->Fill(reldiff_den);
    for_Syst_Pdf_Replica_Num->Fill(reldiff_num);

    Syst_Pdf_Replica_Eff += reldiff_eff*reldiff_eff;
    Syst_Pdf_Replica_Den += reldiff_den*reldiff_den;
    Syst_Pdf_Replica_Num += reldiff_num*reldiff_num;

  }

  //Syst_Pdf_Replica_Eff = sqrt(Syst_Pdf_Replica_Eff/(hist_Pdf_Replica->GetXaxis()->GetNbins()-1));
  //Syst_Pdf_Replica_Den = sqrt(Syst_Pdf_Replica_Den/(hist_Pdf_Replica->GetXaxis()->GetNbins()-1));
  //Syst_Pdf_Replica_Num = sqrt(Syst_Pdf_Replica_Num/(hist_Pdf_Replica->GetXaxis()->GetNbins()-1));

  Syst_Pdf_Replica_Eff = for_Syst_Pdf_Replica_Eff->GetRMS();
  Syst_Pdf_Replica_Den = for_Syst_Pdf_Replica_Den->GetRMS();
  Syst_Pdf_Replica_Num = for_Syst_Pdf_Replica_Num->GetRMS();

  if(Debug){
    cout << "Pdf Replica Eff -> " << Syst_Pdf_Replica_Eff << endl;
    cout << "Pdf Replica Den -> " << Syst_Pdf_Replica_Den << endl;
    cout << "Pdf Replica Num -> " << Syst_Pdf_Replica_Num << endl;

    cout << "RMS of for_Syst_Pdf_Replica_Eff -> " << for_Syst_Pdf_Replica_Eff->GetRMS() << endl;
    cout << "RMS of for_Syst_Pdf_Replica_Den -> " << for_Syst_Pdf_Replica_Den->GetRMS() << endl;
    cout << "RMS of for_Syst_Pdf_Replica_Num -> " << for_Syst_Pdf_Replica_Num->GetRMS() << endl;

  }
  delete for_Syst_Pdf_Replica_Eff;
  delete for_Syst_Pdf_Replica_Den;
  delete for_Syst_Pdf_Replica_Num;

  //==== PDF Alpha

  Syst_Pdf_Alpha_Eff = 0.;
  Syst_Pdf_Alpha_Den = 0.;
  Syst_Pdf_Alpha_Num = 0.;
  if(istch){
    for(unsigned int i=1; i<=hist_Pdf_Alpha->GetXaxis()->GetNbins(); i++){
      double num = hist_Pdf_Alpha->GetBinContent(i);
      double den = hist_Replica_Den->GetBinContent(i+100); // For LUX pdf, PdfWeights at(101)~at(107) are extra sources
      double this_eff = num/den;

      double reldiff_eff = (this_eff-eff_central)/eff_central;
      double reldiff_den = (den-den_central)/den_central;
      double reldiff_num = (num-num_central)/num_central;

      Syst_Pdf_Alpha_Eff += reldiff_eff*reldiff_eff;
      Syst_Pdf_Alpha_Den += reldiff_den*reldiff_den;
      Syst_Pdf_Alpha_Num += reldiff_num*reldiff_num;

    }
    Syst_Pdf_Alpha_Eff = sqrt(Syst_Pdf_Alpha_Eff);
    Syst_Pdf_Alpha_Den = sqrt(Syst_Pdf_Alpha_Den);
    Syst_Pdf_Alpha_Num = sqrt(Syst_Pdf_Alpha_Num);
  }
  else{

    double num_alphaS_1 = hist_Pdf_Alpha->GetBinContent(1);
    double num_alphaS_2 = hist_Pdf_Alpha->GetBinContent(2);
    double den_alphaS_1 = hist_Replica_Den->GetBinContent(100);
    double den_alphaS_2 = hist_Replica_Den->GetBinContent(101);
    double eff_alphaS_1 = num_alphaS_1/den_alphaS_1;
    double eff_alphaS_2 = num_alphaS_2/den_alphaS_2;

    Syst_Pdf_Alpha_Eff = (eff_alphaS_2-eff_alphaS_1)/2./eff_central;
    Syst_Pdf_Alpha_Den = (den_alphaS_2-den_alphaS_1)/2./den_central;
    Syst_Pdf_Alpha_Num = (num_alphaS_2-num_alphaS_1)/2./num_central;

  }
  if(Debug){
    cout << "Pdf Alpha Eff -> " << Syst_Pdf_Alpha_Eff << endl;
    cout << "Pdf Alpha Den -> " << Syst_Pdf_Alpha_Den << endl;
    cout << "Pdf Alpha Num -> " << Syst_Pdf_Alpha_Num << endl;
  }

  //==== PDF Scale

  Syst_Pdf_Scale_Eff = -999.;
  Syst_Pdf_Scale_Den = -999.;
  Syst_Pdf_Scale_Num = -999.;
  for(unsigned int i=1; i<=hist_Pdf_Scale->GetXaxis()->GetNbins(); i++){
    double num = hist_Pdf_Scale->GetBinContent(i);
    double den = hist_Scale_Den->GetBinContent(i);
    double this_eff = num/den;

    double reldiff_eff = (this_eff-eff_central)/eff_central;
    double reldiff_den = (den-den_central)/den_central;
    double reldiff_num = (num-num_central)/num_central;

    if(reldiff_eff>Syst_Pdf_Scale_Eff){
      Syst_Pdf_Scale_Eff = reldiff_eff;
    }
    if(reldiff_den>Syst_Pdf_Scale_Den){
      Syst_Pdf_Scale_Den = reldiff_den;
    }
    if(reldiff_num>Syst_Pdf_Scale_Num){
      Syst_Pdf_Scale_Num = reldiff_num;
    }

  }
  if(Debug){
    cout << "Pdf Scale Eff -> " << Syst_Pdf_Scale_Eff << endl;
    cout << "Pdf Scale Den -> " << Syst_Pdf_Scale_Den << endl;
    cout << "Pdf Scale Num -> " << Syst_Pdf_Scale_Num << endl;
  }



  //==== Sum-up
  Syst_Pdf_Total = 0;

  if(SeparateEffDen){
    if(!ForXsecLimitOnly){
      Syst_Pdf_Total += Syst_Pdf_Replica_Eff*Syst_Pdf_Replica_Eff;
      Syst_Pdf_Total += Syst_Pdf_Alpha_Eff*Syst_Pdf_Alpha_Eff;
      Syst_Pdf_Total += Syst_Pdf_Scale_Eff*Syst_Pdf_Scale_Eff;
    }
    Syst_Pdf_Total += Syst_Pdf_Replica_Den*Syst_Pdf_Replica_Den;
    Syst_Pdf_Total += Syst_Pdf_Alpha_Den*Syst_Pdf_Alpha_Den;
    Syst_Pdf_Total += Syst_Pdf_Scale_Den*Syst_Pdf_Scale_Den;
  }
  else{
    Syst_Pdf_Total += Syst_Pdf_Replica_Num*Syst_Pdf_Replica_Num;
    Syst_Pdf_Total += Syst_Pdf_Alpha_Num*Syst_Pdf_Alpha_Num;
    Syst_Pdf_Total += Syst_Pdf_Scale_Num*Syst_Pdf_Scale_Num;
  }

  Syst_Pdf_Total = sqrt(Syst_Pdf_Total);

  if(Debug) cout << "==> Total = " << Syst_Pdf_Total << endl;

  file_Den->Close();
  delete file_Den;

}

bool PdfSystematics::IsTch(){

  if(SampleName.Contains("Tchannel")) return true;
  else return false;

}

#endif
