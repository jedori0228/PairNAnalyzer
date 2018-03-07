#include "canvas_margin.h"

void draw(){

//==== Powheg
vector<double> vec_mZR_Powheg = {
1000, 1000, 1000, 1000, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 500, 500, 750, 750, 750, 
};
vector<double> vec_mN_Powheg = {
100, 200, 300, 400, 100, 200, 300, 400, 500, 600, 700, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 100, 1100, 1200, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 100, 1100, 1200, 1300, 1400, 200, 300, 400, 500, 600, 700, 800, 1000, 100, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 200, 300, 400, 500, 600, 700, 800, 100, 200, 100, 200, 300, 
};
vector<double> vec_Xsec_Powheg = {
8.502e-01, 7.037e-01, 4.675e-01, 2.014e-01, 1.367e-01, 1.248e-01, 1.060e-01, 8.402e-02, 5.794e-02, 3.018e-02, 7.009e-03, 3.178e-02, 2.985e-02, 2.739e-02, 2.421e-02, 2.043e-02, 1.594e-02, 1.139e-02, 6.766e-03, 2.645e-03, 1.872e-03, 9.153e-03, 9.271e-04, 2.236e-04, 8.723e-03, 8.171e-03, 7.463e-03, 6.748e-03, 5.881e-03, 4.917e-03, 3.936e-03, 2.883e-03, 1.096e-03, 3.000e-03, 8.372e-04, 5.733e-04, 3.301e-04, 1.264e-04, 2.843e-03, 2.690e-03, 2.518e-03, 2.335e-03, 2.108e-03, 1.882e-03, 1.650e-03, 2.063e-04, 4.174e-04, 1.835e-04, 1.603e-04, 1.365e-04, 1.115e-04, 8.812e-05, 6.510e-05, 4.365e-05, 2.453e-05, 9.557e-06, 3.805e-04, 3.562e-04, 3.307e-04, 3.126e-04, 2.935e-04, 2.723e-04, 2.491e-04, 1.059e+01, 3.027e+00, 2.603e+00, 1.783e+00, 6.503e-01, 
};

//==== MG_NLO
vector<double> vec_mZR_MG_NLO = {
500, 500, 750, 750, 750, 1000, 1000, 1000, 1000, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 
};
vector<double> vec_mN_MG_NLO = {
100, 200, 100, 200, 300, 100, 200, 300, 400, 100, 200, 300, 400, 500, 600, 700, 100, 200, 300, 400, 500, 600, 700, 800, 900, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 
};
vector<double> vec_Xsec_MG_NLO = {
14.5500000, 4.2620000, 3.6520000, 2.5030000, 0.9201000, 1.2090000, 0.9949000, 0.6696000, 0.2879000, 0.2092000, 0.1916000, 0.1649000, 0.1299000, 0.0894900, 0.0471000, 0.0108600, 0.0497600, 0.0469600, 0.0430000, 0.0381200, 0.0321400, 0.0254000, 0.0180900, 0.0107900, 0.0042160, 0.0138500, 0.0132200, 0.0124600, 0.0114400, 0.0103300, 0.0090020, 0.0075630, 0.0060430, 0.0044480, 0.0028810, 0.0014400, 0.0003358, 0.0042800, 0.0040610, 0.0038290, 0.0035880, 0.0033330, 0.0030400, 0.0027110, 0.0023620, 0.0019940, 0.0016080, 0.0012190, 0.0008341, 0.0004795, 0.0001837, 0.0005023, 0.0004540, 0.0004212, 0.0003897, 0.0003619, 0.0003393, 0.0003130, 0.0002890, 0.0002640, 0.0002369, 0.0002114, 0.0001836, 0.0001560, 0.0001285, 0.0001011, 0.0000748, 0.0000503, 0.0000284, 0.0000108, 
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
    kRed, kOrange, kGreen, kBlue, kViolet, kGray, kBlack, kCyan
  };

  for(unsigned int i=0; i<vec_mZR_Powheg.size(); i++){

    double mZR = vec_mZR_Powheg.at(i);
    double mN = vec_mN_Powheg.at(i);
    double Xsec = vec_Xsec_Powheg.at(i);

    map__mZR__mN_Xsec[mZR].push_back( make_pair(mN, Xsec) );

  }

  TCanvas *c1_mN = new TCanvas("c1_mN", "", 600, 600);
  canvas_margin(c1_mN);
  TH1D *dummy_mN = new TH1D("dummy_mN", "", 10000, 0., 10000.);
  hist_axis(dummy_mN);
  dummy_mN->Draw("hist");
  dummy_mN->GetXaxis()->SetRangeUser(90., 3000.);
  dummy_mN->GetYaxis()->SetRangeUser(1e-6, 20.);
  dummy_mN->GetXaxis()->SetTitle("m_{N} (GeV)");
  dummy_mN->GetYaxis()->SetTitle("#sigma(pp#rightarrowZ'#rightarrowNN#rightarrow#mu#mujjjj) (pb)");
  c1_mN->SetLogx();
  c1_mN->SetLogy();

  TCanvas *c1_mNOVERmZR = new TCanvas("c1_mNOVERmZR", "", 600, 600);
  canvas_margin(c1_mNOVERmZR);
  TH1D *dummy_mNOVERmZR = new TH1D("dummy_mNOVERmZR", "", 100, 0., 1.);
  hist_axis(dummy_mNOVERmZR);
  dummy_mNOVERmZR->Draw("hist");
  dummy_mNOVERmZR->GetXaxis()->SetRangeUser(0., 0.5);
  dummy_mNOVERmZR->GetYaxis()->SetRangeUser(0, 10);
  dummy_mNOVERmZR->GetXaxis()->SetTitle("m_{N}/m_{Z'}");
  dummy_mNOVERmZR->GetYaxis()->SetTitle("Norm. #sigma(pp#rightarrowZ'#rightarrowNN#rightarrow#mu#mujjjj)");

  TLegend *lg = new TLegend(0.6, 0.65, 0.95, 0.95);
  lg->SetBorderSize(0);
  lg->SetFillStyle(0);

  int counter = 0;
  for(map< double, vector< pair<double, double>  > >::iterator it=map__mZR__mN_Xsec.begin(); it!=map__mZR__mN_Xsec.end(); it++){

    double mZR = it->first;
    vector< pair<double, double> > mN_Xsec = it->second;

    sort(mN_Xsec.begin(), mN_Xsec.end());

    //cout << "This mZR = " << mZR << endl;
    const int n_this_mN = mN_Xsec.size();
    double x_mN[n_this_mN], y_Xsec[n_this_mN];
    double x_mNOVERmZR[n_this_mN], y_NormXsec[n_this_mN];

    double this_norm_mNOVERmZR = 0.4;
    double this_norm_xsec = 1.;

    for(unsigned int i=0; i<mN_Xsec.size(); i++){
      double mN = mN_Xsec.at(i).first;
      double Xsec = mN_Xsec.at(i).second;
      //cout << mN << "\t" << Xsec << endl;
      x_mN[i] = mN;
      y_Xsec[i] = Xsec;
      x_mNOVERmZR[i] = mN/mZR;
      if(x_mNOVERmZR[i]==this_norm_mNOVERmZR) this_norm_xsec=Xsec;
    }
    for(unsigned int i=0; i<mN_Xsec.size(); i++){
      y_NormXsec[i] = y_Xsec[i]/this_norm_xsec;
    }

    c1_mN->cd();
    TGraph *gr_mN = new TGraph(n_this_mN, x_mN,y_Xsec);
    gr_mN->SetLineWidth(2);
    gr_mN->SetMarkerStyle(20);
    gr_mN->SetMarkerSize(1);
    gr_mN->SetMarkerColor(colors.at(counter));
    gr_mN->SetLineColor(colors.at(counter));
    gr_mN->Draw("lpsame");

    c1_mNOVERmZR->cd();
    TGraph *gr_mNOVERmZR = new TGraph(n_this_mN, x_mNOVERmZR,y_NormXsec);
    gr_mNOVERmZR->SetLineWidth(2);
    gr_mNOVERmZR->SetMarkerStyle(20);
    gr_mNOVERmZR->SetMarkerSize(1);
    gr_mNOVERmZR->SetMarkerColor(colors.at(counter));
    gr_mNOVERmZR->SetLineColor(colors.at(counter));
    gr_mNOVERmZR->Draw("lpsame");

    TString alias = "m_{Z'} = "+TString::Itoa(mZR,10)+" GeV";

    lg->AddEntry(gr_mN, alias, "lp");

    counter++;

  }

  c1_mN->cd();
  lg->Draw();
  c1_mN->SaveAs(plotpath+"/Xsec.pdf");
  c1_mN->Close();

  c1_mNOVERmZR->cd();
  lg->Draw();
  c1_mNOVERmZR->SaveAs(plotpath+"/Xsec_mNOVERmZR.pdf");
  c1_mNOVERmZR->Close();

}
