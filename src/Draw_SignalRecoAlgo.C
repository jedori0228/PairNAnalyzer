#include "canvas_margin.h"
#include "mylib.h"

void Draw_SignalRecoAlgo(){

  TString bkgdsample_prompt = "DYJets";
  TString bkgdsample_fake = "TT_powheg";

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/SignalRecoAlgo/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalRecoAlgo/";

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

  TFile *file_bkg_prompt = new TFile(base_filepath+"/ExampleAnalyzer_SK"+bkgdsample_prompt+"_cat_v8-0-7.root");
  TFile *file_bkg_fake = new TFile(base_filepath+"/ExampleAnalyzer_SK"+bkgdsample_fake+"_cat_v8-0-7.root");

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    vector<TString> vars, xtitles;

    vector<TString> common_vars = {
      "N_Mass", "Z_Mass",
    };
    vector<TString> common_xtitels = {
      "m_{N,RECO} (GeV)", "m_{Z',RECO} (GeV)",
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
      hist_dummy->GetYaxis()->SetTitle("a.u.");
      hist_dummy->GetXaxis()->SetTitle(xtitles.at(l));


      TLegend *lg = new TLegend(0.77, 0.15, 0.98, 0.95);
      lg->SetBorderSize(0);
      lg->SetFillStyle(0);

      double this_ymax = -999;

      //==== Background
/*
      TH1D *hist_bkg_prompt = (TH1D *)file_bkg_prompt->Get(vars.at(l));
      if(hist_bkg_prompt){
        hist_bkg_prompt->Rebin(n_rebin);
        if(CheckIsoPass) hist_bkg_prompt->Scale(1./hist_bkg_prompt->GetBinContent(1));
        else if(PassOrFail) hist_bkg_prompt->Scale(1./hist_bkg_prompt->GetEntries());
        else hist_bkg_prompt->Scale(1./hist_bkg_prompt->GetEntries());
        hist_bkg_prompt->SetFillColorAlpha(kCyan,0.50);
        hist_bkg_prompt->SetLineWidth(0);
        hist_bkg_prompt->SetLineColor(0);
        hist_bkg_prompt->Draw("histsame");
        lg->AddEntry(hist_bkg_prompt, bkgdsample_prompt+" (Prompt)", "f");
        this_ymax = max(this_ymax,GetMaximum(hist_bkg_prompt));
      }
*/
/*
      TH1D *hist_bkg_fake = (TH1D *)file_bkg_fake->Get(vars.at(l));
      if(hist_bkg_fake){
        hist_bkg_fake->Rebin(n_rebin);
        if(CheckIsoPass) hist_bkg_fake->Scale(1./hist_bkg_fake->GetBinContent(1));
        else if(PassOrFail) hist_bkg_fake->Scale(1./hist_bkg_fake->GetEntries());
        else hist_bkg_fake->Scale(1./hist_bkg_fake->GetEntries());
        hist_bkg_fake->SetFillColorAlpha(kGray,0.50);
        hist_bkg_fake->SetLineWidth(0);
        hist_bkg_fake->SetLineColor(0);
        hist_bkg_fake->Draw("histsame");
        lg->AddEntry(hist_bkg_fake, bkgdsample_fake+" (Fake)", "f");
        this_ymax = max(this_ymax,GetMaximum(hist_bkg_fake));
      }
*/

      for(unsigned j=0; j<masses.size(); j++){

        int mZP = masses.at(j);
        //cout << "Z = " << mZP << endl;
        vector<int> hnmasses = GetHNMassRange(mZP);
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

          hist->Rebin(n_rebin);
          hist->SetLineColor(colors.at(j));
          hist->SetLineWidth(2);
          hist->SetLineStyle(k+1);
          double this_scale = hist->GetEntries();

          hist->Scale(1./this_scale);
          
          hist->Draw("histsame");
          //cout << "  mN = " << hnmass << endl;

          this_ymax = max(this_ymax,GetMaximum(hist));

          TString alias = "m_{Z'} = "+TString::Itoa(mZP,10)+" GeV, m_{N} = "+TString::Itoa(hnmass,10);
          lg->AddEntry(hist, alias, "l");

          file->Close();

        }

      }

      TLatex latex_CMSPriliminary, latex_Lumi;
      latex_CMSPriliminary.SetNDC();
      latex_Lumi.SetNDC();
      latex_CMSPriliminary.SetTextSize(0.035);
      //latex_CMSPriliminary.DrawLatex(0.15, 0.96, "#font[62]{CMS} #font[42]{#it{#scale[0.8]{Preliminary}}}");
      latex_Lumi.SetTextSize(0.035);
      //latex_Lumi.DrawLatex(0.7, 0.96, "35.9 fb^{-1} (13 TeV)");

      lg->Draw();

      hist_dummy->Draw("axissame");

      double y_max_scale = 1.2;
      hist_dummy->GetYaxis()->SetRangeUser(0., 0.5);

      c1->SaveAs(base_plotpath+"/HN"+channel+"_"+vars.at(l)+".pdf");

      if(vars.at(l).Contains("MergeJetToClosestN_N")||vars.at(l).Contains("MinimumMDiff_N")){
        hist_dummy->GetXaxis()->SetRangeUser(0,550);
        c1->SaveAs(base_plotpath+"/HN"+channel+"_"+vars.at(l)+"_0_550.pdf");
        hist_dummy->GetXaxis()->SetRangeUser(550,1050);
        c1->SaveAs(base_plotpath+"/HN"+channel+"_"+vars.at(l)+"_550_1050.pdf");
        hist_dummy->GetXaxis()->SetRangeUser(1050,1550);
        c1->SaveAs(base_plotpath+"/HN"+channel+"_"+vars.at(l)+"_1050_1550.pdf");
        hist_dummy->GetXaxis()->SetRangeUser(1550,2050);
        c1->SaveAs(base_plotpath+"/HN"+channel+"_"+vars.at(l)+"_1550_2050.pdf");
      }

      c1->Close();

    }




  }

}




