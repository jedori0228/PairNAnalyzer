#include "canvas_margin.h"

void draw(){

vector<double> vec_mZR = {
1000, 1000, 1000, 1000, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 
};
vector<double> vec_mN = {
100, 200, 300, 400, 100, 200, 300, 400, 500, 600, 700, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 100, 1100, 1200, 200, 300, 400, 500, 600, 700, 800, 900, 
};
vector<double> vec_Xsec = {
8.510e-01, 7.037e-01, 4.675e-01, 2.014e-01, 1.367e-01, 1.248e-01, 1.060e-01, 8.402e-02, 5.794e-02, 3.018e-02, 7.009e-03, 3.178e-02, 2.985e-02, 2.739e-02, 2.421e-02, 2.043e-02, 1.594e-02, 1.139e-02, 6.766e-03, 2.645e-03, 1.872e-03, 9.153e-03, 9.271e-04, 2.236e-04, 8.723e-03, 8.171e-03, 7.463e-03, 6.748e-03, 5.881e-03, 4.917e-03, 3.936e-03, 2.883e-03, 
};

  gStyle->SetOptStat(0);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_FILE_PATH = getenv("FILE_PATH");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalCrossSection/";

  if( !gSystem->mkdir(plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  map< double, vector< pair<double, double> > > map__mZR__mN_Xsec;
  vector<Color_t> colors = {
    kRed, kOrange, kYellow, kGreen, kBlue, kViolet,
  };

  for(unsigned int i=0; i<vec_mZR.size(); i++){

    double mZR = vec_mZR.at(i);
    double mN = vec_mN.at(i);
    double Xsec = vec_Xsec.at(i);

    map__mZR__mN_Xsec[mZR].push_back( make_pair(mN, Xsec) );

  }

  TCanvas *c1 = new TCanvas("c1", "", 600, 600);
  canvas_margin(c1);
  c1->cd();
  TH1D *dummy = new TH1D("dummy", "", 10000, 0., 10000.);
  hist_axis(dummy);
  dummy->Draw("hist");
  dummy->GetXaxis()->SetRangeUser(90., 3000.);
  dummy->GetYaxis()->SetRangeUser(1e-5, 1.);
  dummy->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy->GetYaxis()->SetTitle("#sigma(pp#rightarrowZ'#rightarrowNN#rightarrow#mu#mujjjj) (pb)");
  c1->SetLogx();
  c1->SetLogy();

  TLegend *lg = new TLegend(0.5, 0.5, 0.9, 0.9);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);

  int counter = 0;
  for(map< double, vector< pair<double, double>  > >::iterator it=map__mZR__mN_Xsec.begin(); it!=map__mZR__mN_Xsec.end(); it++){

    double mZR = it->first;
    vector< pair<double, double> > mN_Xsec = it->second;

    sort(mN_Xsec.begin(), mN_Xsec.end());

    cout << "This mZR = " << mZR << endl;
    const int n_this_mN = mN_Xsec.size();
    double x_mN[n_this_mN], y_Xsec[n_this_mN];

    for(unsigned int i=0; i<mN_Xsec.size(); i++){
      double mN = mN_Xsec.at(i).first;
      double Xsec = mN_Xsec.at(i).second;
      cout << mN << "\t" << Xsec << endl;
      x_mN[i] = mN;
      y_Xsec[i] = Xsec;
    }

    TGraph *gr = new TGraph(n_this_mN, x_mN,y_Xsec);
    gr->SetLineWidth(2);
    gr->SetMarkerStyle(counter);
    gr->SetMarkerColor(colors.at(counter));
    gr->SetLineColor(colors.at(counter));
    gr->Draw("lsame");

    TString alias = "m_{Z'} = "+TString::Itoa(mZR,10)+" GeV";
    lg->AddEntry(gr, alias, "l");

    counter++;

  }

  lg->Draw();

  c1->SaveAs(plotpath+"/Xsec.pdf");
  c1->Close();

}
