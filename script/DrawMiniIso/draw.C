#include "canvas_margin.h"

double GetR(double rmin, double rmax, double scale){

  return max( rmin, min(rmax,scale) );

}

void draw(){

  gStyle->SetOptStat(0);

  double r_min = 0.05;
  double r_max = 0.20;
  double kt_scale = 10.;

  double x_max = 500.;
  double dx = 5.;
  const int n_x = x_max/dx;

  double x[n_x];
  double y_min[n_x];
  double y_max[n_x];
  double y_scale[n_x];
  double y_final[n_x];

  for(int i=0; i<n_x; i++){

    x[i] = (i+1)*dx;
    y_min[i] = r_min;
    y_max[i] = r_max;
    y_scale[i] = kt_scale/x[i];
    y_final[i] = GetR(y_min[i], y_max[i], y_scale[i]);

  }

  TGraph *gr_min = new TGraph(n_x, x, y_min);
  TGraph *gr_max = new TGraph(n_x, x, y_max);
  TGraph *gr_scale = new TGraph(n_x, x, y_scale);
  TGraph *gr_final = new TGraph(n_x, x, y_final);

  gr_min->SetLineColor(kBlue);
  gr_max->SetLineColor(kRed);
  gr_scale->SetLineColor(kViolet);
  gr_final->SetLineColor(kBlack);

  gr_min->SetLineWidth(2);
  gr_max->SetLineWidth(2);
  gr_scale->SetLineWidth(2);
  gr_final->SetLineWidth(3);

  gr_min->SetLineStyle(2);
  gr_max->SetLineStyle(2);
  gr_scale->SetLineStyle(2);

  TCanvas *c1 = new TCanvas("c1", "", 600, 600);
  canvas_margin(c1);
  c1->cd();

  TH1D *dummy = new TH1D("dummy", "", 1000, 0., 1000.);
  hist_axis(dummy);
  dummy->Draw("hist");
  dummy->GetXaxis()->SetRangeUser(0,500);
  dummy->GetYaxis()->SetRangeUser(0,0.5);

  gr_min->Draw("lsame");
  gr_max->Draw("lsame");
  gr_scale->Draw("lsame");
  gr_final->Draw("lsame");

  c1->SaveAs("R.pdf");
  c1->Close();

}
