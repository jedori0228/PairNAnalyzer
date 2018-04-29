#include "canvas_margin.h"
#include "mylib.h"
#include "LRSMSignalInfo.h"

void Draw_SimpleCutEfficiency(){

  TString region = "DiMuon_AllCharge";

  setTDRStyle();
  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Regions/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SimpleCutEfficiency/";

  if( !gSystem->mkdir(base_plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << base_plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //==== Get Bkgd files first

  vector<TString> bkgds = {"TT_powheg"};
  vector<TFile *> files_bkgd;
  for(unsigned int i=0; i<bkgds.size(); i++){
    TFile *file = new TFile(base_filepath+"PairNAnalyzer_SK"+bkgds.at(i)+"_dilep_cat_v8-0-7.root");
    files_bkgd.push_back(file);
  }

  //==== Zp mass

  vector<int> masses = {500, 750, 1500, 2000, 2500, 4000};

  vector<TString> channels = {
    "MuMu",
    //"ElEl",
  };

  vector<Color_t> colors = {
kRed, kOrange, kGreen, kBlue, kViolet, kBlack, kCyan
};

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    vector<TString> vars = {
      "HT", "ST", "secondLepton_Pt",
    };
    vector<TString> xtitles = {
      "H_{T} (GeV)", "S_{T} (GeV)", "Subleading Lepton p_{T} (GeV)",
    };
    vector<TString> dirs = {
      ">", ">", ">",
    };

    for(unsigned int l=0; l<vars.size(); l++){

      TString var = vars.at(l);
      TString dir = dirs.at(l);

      cout << endl;
      cout << "##### " << var << " " << dir << "CUT #####" << endl;
      cout << endl;

      //==== Make Bkgd
      TH1D *hist_bkgd = NULL;
      for(unsigned int aa=0; aa<files_bkgd.size(); aa++){
        TH1D *this_hist_bkgd = (TH1D *)files_bkgd.at(aa)->Get(region+"/"+vars.at(l)+"_"+region);
        if(hist_bkgd){
          hist_bkgd->Add(this_hist_bkgd);
        }
        else{
          hist_bkgd = (TH1D *)this_hist_bkgd->Clone();
        }
      }

      TCanvas* c1 = new TCanvas("c1", "", 1000, 1600);
      c1->Draw();
      c1->cd();

      TPad *c1_up;
      TPad *c1_down;
      c1_up = new TPad("c1", "", 0, 0.5, 1, 1);
      c1_down = new TPad("c1_down", "", 0, 0, 1, 0.5);

      canvas_margin_twoplots(c1, c1_up, c1_down);

      c1_up->Draw();
      c1_down->Draw();
      c1_up->cd();

      double x_max=10000;

      TH1D *hist_dummy = new TH1D("hist_dummy", "", int(x_max), 0., x_max);
      hist_dummy->Draw("hist");
      hist_dummy->GetXaxis()->SetRangeUser(0., 2000.);

      //hist_dummy->GetYaxis()->SetTitle("a.u.");
      hist_dummy->GetYaxis()->SetRangeUser(0,1.0);
      hist_dummy->GetXaxis()->SetTitle(xtitles.at(l));

      TH1D *hist_dummy_bottom = (TH1D *)hist_dummy->Clone();
      hist_dummy_bottom->GetYaxis()->SetRangeUser(0,1.0);
      c1_down->cd();
      hist_dummy_bottom->Draw("hist");
      double y_max_punzi=-999;

      hist_axis_twoplots(hist_dummy,hist_dummy_bottom);

      TLegend *lg = new TLegend(0.77, 0.15, 0.98, 0.95);
      lg->SetBorderSize(0);
      lg->SetFillStyle(0);

      for(unsigned j=0; j<masses.size(); j++){

        int mZP = masses.at(j);
        //cout << "Z = " << mZP << endl;
        vector<int> hnmasses = GetHNMassRange(mZP,true);

        const int n_hnmass = hnmasses.size();

        LRSMSignalInfo lrsminfo;
        lrsminfo.prod_channel="pair";
        lrsminfo.lep_channel=channel;
        lrsminfo.generator="pythia";
        lrsminfo.mass_WR = 5000;
        lrsminfo.mass_Z = mZP;

        for(unsigned int k=0; k<hnmasses.size(); k++){
          int hnmass = hnmasses.at(k);
          //cout << "  mN = " << hnmass << endl;

          lrsminfo.mass_N = hnmass;
          lrsminfo.SetNames();

          TString filename = "PairNAnalyzer_"+lrsminfo.GetCATFileName()+"_cat_v8-0-7.root";
          //TString filename = "PairNAnalyzer_HNpair_"+channel+"_WR5000_Zp"+TString::Itoa(mZP,10)+"_HN"+TString::Itoa(hnmass,10)+"_official_cat_v8-0-7.root";
          TFile *file = new TFile(base_filepath+"/Signal/"+filename);
          TH1D *hist_den = (TH1D *)file->Get("SignalNevent");
          TH1D *hist = (TH1D *)file->Get(region+"/"+vars.at(l)+"_"+region);

          if(!hist){
            file->Close();
            continue;
          }

          hist->SetLineColor(colors.at(j));
          hist->SetLineStyle(k+1);

          //==== Calculate Efficiency..
          TH1D *hist_eff = (TH1D *)hist->Clone();
          TH1D *hist_punzi = (TH1D *)hist->Clone();
          double den = hist_den->GetBinContent(1);
          double this_punzi_max = -999;
          double this_punzi_max_xvalue;
          for(int it_bin=1; it_bin<=hist->GetXaxis()->GetNbins(); it_bin++){
            double this_eff = -999;
            double this_bkgd = -999;
            if(dir=="<"){
              this_eff = hist->Integral(0,it_bin);
              this_bkgd = hist_bkgd->Integral(0,it_bin);
            }
            else{
              this_eff = hist->Integral(it_bin,hist->GetXaxis()->GetNbins()+1);
              this_bkgd = hist_bkgd->Integral(it_bin,hist->GetXaxis()->GetNbins()+1);
            }

            this_eff = this_eff/den;
            double this_punzi = this_eff/(1+sqrt(this_bkgd));

            hist_eff->SetBinContent(it_bin,this_eff);
            hist_punzi->SetBinContent(it_bin,this_punzi);

            if(var=="ST" && it_bin==1){
              cout << lrsminfo.GetLegendAlias() << "\t" << this_eff << endl;
            }

            if(this_punzi_max<this_punzi){
              this_punzi_max = this_punzi;
              this_punzi_max_xvalue = hist->GetXaxis()->GetBinCenter(it_bin);
            }

          }

          c1_up->cd();
          hist_eff->Draw("histsame");
          c1_down->cd();
          hist_punzi->Draw("histsame");

          //cout << lrsminfo.GetLegendAlias() << "\t" << this_punzi_max_xvalue << "\t" << this_punzi_max << endl;

          y_max_punzi = max(y_max_punzi,(hist_punzi->GetMaximum())*1.1);

          file->Close();

        } //END loop HN mass

        c1->cd();

        TString alias = "m_{Z'} = "+TString::Itoa(mZP,10)+" GeV";
        //lg->AddEntry(gr_mean, alias, "l");

      } // END loop Z' mass

      //lg->Draw();

      hist_dummy_bottom->GetYaxis()->SetRangeUser(0,y_max_punzi);

      c1->SaveAs(base_plotpath+"/HN"+channel+"_"+vars.at(l)+".pdf");
      c1->Close();

    } // END loop vars




  }

}




