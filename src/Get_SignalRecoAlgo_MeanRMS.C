#include "canvas_margin.h"
#include "mylib.h"

void Get_SignalRecoAlgo_MeanRMS(){

  TString bkgdsample_prompt = "DYJets";
  TString bkgdsample_fake = "TT_powheg";

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/SignalRecoAlgo/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalRecoAlgo_MeanRMS/";

  if( !gSystem->mkdir(base_plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << base_plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //===============
  //==== Low Mass
  //===============

  //==== Zp mass

  vector<int> masses = {500, 1000, 1500, 2000, 2500, 4000};
/*
  for(unsigned int i=0; i<masses.size(); i++){

    int mZP = masses.at(i);
    vector<int> hnmasses = GetHNMassRange(mZP);

    cout << "mZP = " << mZP << endl;
    for(unsigned int j=0; j<hnmasses.size(); j++){
      cout << hnmasses.at(j) << ", ";
    }
    cout << endl;
  }
*/

  vector<TString> channels = {
    "MuMu",
    //"ElEl",
  };

  vector<Color_t> colors = {
kRed, kOrange, kGreen, kBlue, kViolet, kBlack, kCyan
};

  double x_1[2], y_1[2];
  x_1[0] = 0;  y_1[0] = 0;
  x_1[1] = 9000;  y_1[1] = 9000;
  TGraph *g1 = new TGraph(2, x_1, y_1);

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    vector<TString> vars, xtitles;

    vector<TString> common_vars = {
      "N_Mass",
      //"Z_Mass",
    };
    vector<TString> common_xtitels = {
      "m_{N,RECO} (GeV)",
      //"m_{Z',RECO} (GeV)",
    };

    for(unsigned int l=0; l<=9; l++){

      TString this_Algo = "Algo_"+TString::Itoa(l,10);

      for(unsigned int k=0; k<common_vars.size(); k++){

        vars.push_back( this_Algo+"_"+common_vars.at(k) );
        xtitles.push_back( common_xtitels.at(k) );

      }

    }

    for(unsigned int l=0; l<vars.size(); l++){

      TString var = vars.at(l);

      TCanvas *c1 = new TCanvas("c1", "", 2000, 1000);
      canvas_margin(c1);
      c1->SetRightMargin( 0.25 );
      c1->SetLeftMargin( 0.09 );

      c1->Draw();
      c1->cd();

      int n_rebin;
      double x_max;
      if(var.Contains("N_Mass")){
        x_max = 2500.;
        n_rebin = 20;
      }
      if(var.Contains("Z_Mass")){
        x_max = 6000.;
        n_rebin = 100;
      }

      TH1D *hist_dummy = new TH1D("hist_dummy", "", int(x_max), 0., x_max);
      hist_dummy->Draw("hist");
      hist_axis(hist_dummy);

      hist_dummy->GetYaxis()->SetLabelSize(0.04);
      hist_dummy->GetYaxis()->SetTitleSize(0.06);
      hist_dummy->GetYaxis()->SetTitleOffset(0.70);

      hist_dummy->Rebin(n_rebin);
      //hist_dummy->GetYaxis()->SetTitle("a.u.");
      hist_dummy->GetYaxis()->SetRangeUser(0,3000);
      hist_dummy->GetXaxis()->SetTitle(xtitles.at(l));

      g1->Draw("lsame");

      TLegend *lg = new TLegend(0.77, 0.15, 0.98, 0.95);
      lg->SetBorderSize(0);
      lg->SetFillStyle(0);

      for(unsigned j=0; j<masses.size(); j++){

        int mZP = masses.at(j);
        //cout << "Z = " << mZP << endl;
        vector<int> hnmasses = GetHNMassRange(mZP,true);

        const int n_hnmass = hnmasses.size();
        double x_hnmass[n_hnmass];
        double y_mean[n_hnmass], y_RMS[n_hnmass];

        for(unsigned int k=0; k<hnmasses.size(); k++){
          int hnmass = hnmasses.at(k);
          //cout << "  mN = " << hnmass << endl;
          TString filename = "ExampleAnalyzer_HNpair_"+channel+"_WR5000_Zp"+TString::Itoa(mZP,10)+"_HN"+TString::Itoa(hnmass,10)+"_official_cat_v8-0-7.root";
          TFile *file = new TFile(base_filepath+filename);
          TH1D *hist = (TH1D *)file->Get("Hists/"+vars.at(l));

          if(!hist){
            file->Close();
            continue;
          }

          //hist->GetXaxis()->SetRangeUser(hnmass*0.5,hnmass*1.5);

          x_hnmass[k] = hnmass;
          y_mean[k] = hist->GetMean();
          y_RMS[k] = hist->GetRMS();

          double chi2min = 99999;
          double x_left=0, x_right=0;
          double Mean=0, RMS=0;

          for(int aaa=1;aaa<=10;aaa++){

            double this_x_left = (1.-0.10*double(aaa))*hnmass;

            for(int bbb=1; bbb<=10; bbb++){

              double this_x_right = (1+0.20*double(bbb))*hnmass;

              //cout << this_x_left << "\t" << this_x_right << endl;

              TCanvas *c_temp = new TCanvas("c_temp", "", 500, 500);
              c_temp->cd();
              TFitResultPtr fitresl = hist->Fit("gaus", "Q", "", this_x_left, this_x_right);
              TF1 *fit = hist->GetFunction("gaus");
              double chi2n = fit->GetChisquare()/fit->GetNDF();

              if(chi2n<chi2min){
                x_left = this_x_left;
                x_right = this_x_right;
                Mean = fit->GetParameter(1);
                RMS = fit->GetParameter(2);
                chi2min = chi2n;

              }

              c_temp->Close();

            }

          }
/*
          cout << "=================" << endl;
          cout << "("<<x_left<<","<<x_right<<")"<<endl;
          cout << "Mean = " << Mean << endl;
          cout << "RMS = " << RMS << endl;
*/

          y_mean[k] = Mean;;
          y_RMS[k] = RMS;

          file->Close();

        } //END loop HN mass

        c1->cd();
        TGraph *gr_mean = new TGraph(n_hnmass,x_hnmass,y_mean);
        gr_mean->SetLineWidth(2);
        gr_mean->SetLineColor(colors.at(j));
        gr_mean->Draw("lsame");

        TString alias = "m_{Z'} = "+TString::Itoa(mZP,10)+" GeV";
        lg->AddEntry(gr_mean, alias, "l");

      } // END loop Z' mass

      lg->Draw();

      c1->SaveAs(base_plotpath+"/HN"+channel+"_"+vars.at(l)+".pdf");
      c1->Close();

    } // END loop vars




  }

}




