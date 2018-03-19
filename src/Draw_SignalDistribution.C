#include "canvas_margin.h"
#include "mylib.h"

void Draw_SignalDistribution(){

  TString bkgdsample_prompt = "DYJets";
  TString bkgdsample_fake = "TT_powheg";

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/SignalDistribution/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/SignalDistribution/";

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
    "ElEl",
  };

  vector<Color_t> colors = {
kRed, kOrange, kGreen, kBlue, kViolet, kBlack, kCyan
};

  TFile *file_bkg_prompt = new TFile(base_filepath+"/PairNAnalyzer_SK"+bkgdsample_prompt+"_cat_v8-0-7.root");
  TFile *file_bkg_fake = new TFile(base_filepath+"/PairNAnalyzer_SK"+bkgdsample_fake+"_cat_v8-0-7.root");

  for(unsigned int i=0; i<channels.size(); i++){

    TString channel = channels.at(i);

    vector<TString> vars, xtitles;

    if(channel=="MuMu"){
      vars = {
        "Muon_Size", "Muon_IsolationPass",
        "Muon_Pt", "Muon_Eta", "Muon_RelIso04", "Muon_RelMiniIso", "Muon_validHits", "Muon_validPixHits", "Muon_validStations", "Muon_GlobalChi2", "Muon_PtRatio", "Muon_PtRel",
        "Muon_0_Pt", "Muon_0_Eta", "Muon_0_RelIso04", "Muon_0_RelMiniIso", "Muon_0_validHits", "Muon_0_validPixHits", "Muon_0_validStations", "Muon_0_GlobalChi2", "Muon_0_PtRatio", "Muon_0_PtRel",
        "Muon_1_Pt", "Muon_1_Eta", "Muon_1_RelIso04", "Muon_1_RelMiniIso", "Muon_1_validHits", "Muon_1_validPixHits", "Muon_1_validStations", "Muon_1_GlobalChi2", "Muon_1_PtRatio", "Muon_1_PtRel",

        "FatJet_Size",
        "FatJet_PrunedMass",
        "FatJet_SoftDropMass",

        "FatJet_0_PrunedMass", "FatJet_0_Tau21", "FatJet_0_Tau31", "FatJet_0_Tau32",
        "FatJet_0_SoftDropMass", "FatJet_0_PuppiTau21", "FatJet_0_PuppiTau31", "FatJet_0_PuppiTau32",

        "Jet_0_Pt",
      };

      xtitles = {
        "# of Muon", "",
        "Muon p_{T} (GeV)", "Muon #eta", "Muon RelIso04", "Muon RelMiniIso", "Muon Valid Hits", "Muon Valid Pixel Hits", "Muon Valid Muon Stations", "Muon Global #chi^{2}", "Muon p_{T}^{ratio}", "Muon p_{T}^{rel}",
        "Leading Muon p_{T} (GeV)", "Leading Muon #eta", "Leading Muon RelIso04", "Leading Muon RelMiniIso", "Leading Muon Valid Hits", "Leading Muon Valid Pixel Hits", "Leading Muon Valid Muon Stations", "Leading Muon Global #chi^{2}", "Leading Muon p_{T}^{ratio}", "Leading Muon p_{T}^{rel}",
        "Subleading Muon p_{T} (GeV)", "Subleading Muon #eta", "Subleading Muon RelIso04", "Subleading Muon RelMiniIso", "Subleading Muon Valid Hits", "Subleading Muon Valid Pixel Hits", "Subleading Muon Valid Muon Stations", "Subleading Muon Global #chi^{2}", "Subleading Muon p_{T}^{ratio}", "Subleading Muon p_{T}^{rel}",

        "# of AK8Jet",
        "AK8Jet PrunedMass (GeV)",
        "AK8Jet SoftDropMass (GeV)",

        "Leading AK8Jet PrunedMass (GeV)", "Leading AK8Jet #tau_{21}", "Leading AK8Jet #tau_{31}", "Leading AK8Jet #tau_{32}",
        "Leading AK8Jet SoftDropMass (GeV)", "Leading AK8Jet Puppi #tau_{21}", "Leading AK8Jet Puppi #tau_{31}", "Leading AK8Jet Puppi #tau_{32}",

        "Leading AK4Jet Pt (GeV)",
      };
    }
    if(channel=="ElEl"){
      vars = {
        "Electron_Size", "Electron_IsolationPass", "Electron_GsfCtfScPixChargeConsistency", "Electron_PassesConvVeto", "Electron_MVA_InnerBarrel", "Electron_MVA_OuterBarrel", "Electron_MVA_EndCap", "Electron_MissingHits",
        "Electron_ZZMVA_InnerBarrel", "Electron_ZZMVA_OuterBarrel", "Electron_ZZMVA_EndCap",
        "Electron_Pt", "Electron_Eta", "Electron_RelMiniIso", "Electron_PtRatio", "Electron_PtRel",

        "Electron_0_Pt", "Electron_0_Eta", "Electron_0_RelMiniIso", "Electron_0_PtRatio", "Electron_0_PtRel", "Electron_0_MissingHits", "Electron_0_MVA_InnerBarrel", "Electron_0_MVA_OuterBarrel", "Electron_0_MVA_EndCap", "Electron_0_ZZMVA_InnerBarrel", "Electron_0_ZZMVA_OuterBarrel", "Electron_0_ZZMVA_EndCap",
        "Electron_1_Pt", "Electron_1_Eta", "Electron_1_RelMiniIso", "Electron_1_PtRatio", "Electron_1_PtRel", "Electron_1_MissingHits", "Electron_1_MVA_InnerBarrel", "Electron_1_MVA_OuterBarrel", "Electron_1_MVA_EndCap", "Electron_1_ZZMVA_InnerBarrel", "Electron_1_ZZMVA_OuterBarrel", "Electron_1_ZZMVA_EndCap",

        "FatJet_Size",
        "FatJet_PrunedMass",
        "FatJet_SoftDropMass",

        "FatJet_0_PrunedMass", "FatJet_0_Tau21", "FatJet_0_Tau31", "FatJet_0_Tau32",
        "FatJet_0_SoftDropMass", "FatJet_0_PuppiTau21", "FatJet_0_PuppiTau31", "FatJet_0_PuppiTau32",

        "Jet_0_Pt",
      };

      xtitles = {
        "# of Electron", "", "Electron Pass Three Charge", "Electron Pass Conv. Veto", "Electron MVA, Inner Barrel",  "Electron MVA, Outer Barrel", "Electron MVA, Endcap", "Electron Missing Hits",
        "Electron ZZMVA, Inner Barrel",  "Electron ZZMVA, Outer Barrel", "Electron ZZMVA, Endcap",
        "Electron p_{T} (GeV)", "Electron #eta", "Electron RelMiniIso", "Electron p_{T}^{ratio}", "Electron p_{T}^{rel}",

        "Leading Electron p_{T} (GeV)", "Leading Electron #eta", "Leading Electron RelMiniIso", "Leading Electron p_{T}^{ratio}", "Leading Electron p_{T}^{rel}", "Leading Electron Missing Hits", "Leading Electron MVA, Inner Barrel",  "Leading Electron MVA, Outer Barrel", "Leading Electron MVA, Endcap", "Leading Electron ZZMVA, Inner Barrel",  "Leading Electron ZZMVA, Outer Barrel", "Leading Electron ZZMVA, Endcap",
        "Subleading Electron p_{T} (GeV)", "Subleading Electron #eta", "Subleading Electron RelMiniIso", "Subleading Electron p_{T}^{ratio}", "Subleading Electron p_{T}^{rel}", "subleading Electron Missing Hits", "Subleading Electron MVA, Inner Barrel",  "Subleading Electron MVA, Outer Barrel", "Subleading Electron MVA, Endcap", "Subleading Electron ZZMVA, Inner Barrel",  "Subleading Electron ZZMVA, Outer Barrel", "Subleading Electron ZZMVA, Endcap",

        "# of AK8Jet",
        "AK8Jet PrunedMass (GeV)",
        "AK8Jet SoftDropMass (GeV)",

        "Leading AK8Jet PrunedMass (GeV)", "Leading AK8Jet #tau_{21}", "Leading AK8Jet #tau_{31}", "Leading AK8Jet #tau_{32}",
        "Leading AK8Jet SoftDropMass (GeV)", "Leading AK8Jet Puppi #tau_{21}", "Leading AK8Jet Puppi #tau_{31}", "Leading AK8Jet Puppi #tau_{32}",

        "Leading AK4Jet Pt (GeV)",
      };
    }

    //==== Event Selection
    vector<TString> common_vars = {
      "MergeJetToClosestN_N", "MergeJetToClosestN_n_Merged_FatJet", "MergeJetToClosestN_n_Merged_Jet", "MergeJetToClosestN_Z",
      "MinimumMDiff_N", "MinimumMDiff_n_Merged_FatJet", "MinimumMDiff_n_Merged_Jet", "MinimumMDiff_Z",
    };
    vector<TString> common_xtitels = {
      "m_{N,RECO} (GeV)", "# of AK8 Jets Used", "# of AK4 Jets Used", "m_{Z',RECO} (GeV)",
      "m_{N,RECO} (GeV)", "# of AK8 Jets Used", "# of AK4 Jets Used", "m_{Z',RECO} (GeV)",
    };

    for(unsigned int l=0; l<common_vars.size(); l++){
      vars.push_back( common_vars.at(l) );
      xtitles.push_back( common_xtitels.at(l) );
    }

/*
    //==== Quick
    vars = {
      "MergeJetToClosestN_N", "MergeJetToClosestN_n_Merged_FatJet", "MergeJetToClosestN_n_Merged_Jet",  "MergeJetToClosestN_Z",
      "MinimumMDiff_N", "MinimumMDiff_n_Merged_FatJet", "MinimumMDiff_n_Merged_Jet", "MinimumMDiff_Z",
    };
    xtitles = {
      "m_{N,RECO} (GeV)", "# of AK8 Jets Used", "# of AK4 Jets Used", "m_{Z',RECO} (GeV)",
      "m_{N,RECO} (GeV)", "# of AK8 Jets Used", "# of AK4 Jets Used", "m_{Z',RECO} (GeV)",
    };
*/

    for(unsigned int l=0; l<vars.size(); l++){

      double old_width = 600;
      double new_width = 750;
      double height = 600;

      bool MakeWideCanvas = false;

      if(vars.at(l).Contains("MergeJetToClosestN_N")||vars.at(l).Contains("MinimumMDiff_N")||vars.at(l).Contains("MergeJetToClosestN_Z")||vars.at(l).Contains("MinimumMDiff_Z")){
        MakeWideCanvas = true;
        new_width = 2000;
        height = 1000;
      }

      TCanvas *c1 = new TCanvas("c1", "", new_width, height);
      canvas_margin(c1);

      double right_margin = (0.05*old_width+new_width-old_width)/new_width;
      double left_margin = 0.16*(old_width/new_width);
      if(MakeWideCanvas){
        c1->SetLeftMargin( 0.30 );
        right_margin = 0.25;
        left_margin = 0.09;
      }

      c1->SetRightMargin( right_margin );
      c1->SetLeftMargin( left_margin );

      //cout << right_margin << endl;

      c1->Draw();
      c1->cd();

      int n_rebin = 1;
      double x_max = 1000.;
      double x_min = 0.;
      if(vars.at(l).Contains("Pt")){
        x_min = 10.;
        x_max = 2000.;
        n_rebin = 10;
        if(vars.at(l).Contains("PtRatio")){
          x_min = 0.;
          x_max = 1.5;
          n_rebin = 5;
        }
        if(vars.at(l).Contains("PtRel")){
          x_min = 0.;
          x_max = 50;
          n_rebin = 1;
        }
      }
      if(vars.at(l).Contains("Mass")){
        x_max = 700.;
        n_rebin = 10;
      }
      if(vars.at(l).Contains("MergeJetToClosestN_N")||vars.at(l).Contains("MinimumMDiff_N")){
        x_max = 2000.;
        n_rebin = 20;
      }
      if(vars.at(l).Contains("MergeJetToClosestN_Z")||vars.at(l).Contains("MinimumMDiff_Z")){
        x_max = 6000.;
        n_rebin = 100;
      }
      if(vars.at(l).Contains("Tau")){
        x_max = 1.5;
        n_rebin = 5;
      }
      if(vars.at(l).Contains("Size")){
        x_max = 5.;
        n_rebin = 1;
        if(vars.at(l).Contains("FatJet")){
          x_max = 10.;
          n_rebin = 1;
        }
      }
      if(vars.at(l).Contains("Eta")){
        x_max = 3.;
        n_rebin = 3;
      }
      if(vars.at(l).Contains("Iso")){
        x_max = 1.;
        n_rebin = 1;
      }
      if(vars.at(l).Contains("valid")){
        x_max = 30.;
        n_rebin = 1;
        if(vars.at(l).Contains("validHits")){
          x_max = 80.;
          n_rebin = 1;
        }
      }
      if(vars.at(l).Contains("GlobalChi2")){
        x_max = 30.;
        n_rebin = 1;
      }
      if(vars.at(l).Contains("Eta")){
        x_min = -3.;
      }
      if(vars.at(l).Contains("MVA")){
        x_min = -1.;
        x_max = 1.;
        n_rebin = 5;
      }
      if(vars.at(l).Contains("MissingHits")){
        x_max = 10.;
        n_rebin = 1;
      }
      if(vars.at(l).Contains("MergeJetToClosestN_n_Merged")||vars.at(l).Contains("MinimumMDiff_n_Merged")){
        x_max = 5.;
        n_rebin = 1;
      }





      bool PassOrFail = false;
      if(vars.at(l).Contains("GsfCtfScPixChargeConsistency") || vars.at(l).Contains("PassesConvVeto") ){
        PassOrFail = true;
        x_max = 2.;
        n_rebin = 1;
      }

      bool CheckIsoPass = false;
      if(vars.at(l).Contains("IsolationPass")){
        CheckIsoPass = true;
        x_max = 10.;
        n_rebin = 1;
      }

      int n_bin = (x_max-x_min)*100.; // 0.01
      if(CheckIsoPass) n_bin = 10;
      if(PassOrFail) n_bin = 2;

      //cout << vars.at(l) << " : x_min = " << x_min << ", x_max = " << x_max << ", rebin = " << n_rebin << endl;

      TH1D *hist_dummy = new TH1D("hist_dummy", "", n_bin, x_min, x_max);
      hist_dummy->Draw("hist");
      hist_axis(hist_dummy);

      hist_dummy->GetYaxis()->SetLabelSize(0.04);
      hist_dummy->GetYaxis()->SetTitleSize(0.06);
      hist_dummy->GetYaxis()->SetTitleOffset(0.92);
      if(MakeWideCanvas){
        hist_dummy->GetYaxis()->SetTitleOffset(0.70);
      }

      hist_dummy->GetYaxis()->SetRangeUser(0., 1.1);

      bool XAxisLog = false;
      if(vars.at(l).Contains("Pt")){
        XAxisLog = true;
        if(!vars.at(l).Contains("PtRatio") && !vars.at(l).Contains("PtRel")){
          c1->SetLogx();
        }
      }
      bool YAxisLog = false;
      if(vars.at(l).Contains("Iso")&&vars.at(l).Contains("Rel")){
        YAxisLog = true;
        hist_dummy->GetYaxis()->SetRangeUser(0.001, 2.);
        hist_dummy->GetXaxis()->SetRangeUser(0.001, 2.);
        c1->SetLogy();
      }

      if(vars.at(l).Contains("DeltaR")){
        hist_dummy->GetXaxis()->SetRangeUser(0., 5.0);
        n_rebin = 1;
      }

      hist_dummy->Rebin(n_rebin);
      hist_dummy->GetYaxis()->SetTitle("Events");
      hist_dummy->GetXaxis()->SetTitle(xtitles.at(l));


      if(CheckIsoPass){

        hist_dummy->GetXaxis()->SetRangeUser(0, 8);
        if(channel=="ElEl") hist_dummy->GetXaxis()->SetRangeUser(0,9);

        hist_dummy->GetYaxis()->SetTitle("Isolation Efficiency");
        hist_dummy->GetXaxis()->SetBinLabel(1, "None");
        hist_dummy->GetXaxis()->SetBinLabel(2, "RelIso<0.15");
        hist_dummy->GetXaxis()->SetBinLabel(3, "MiniRelIso<0.15");
        hist_dummy->GetXaxis()->SetBinLabel(4, "MiniRelIso<0.40");
        hist_dummy->GetXaxis()->SetBinLabel(5, "MultiIso Loose");
        hist_dummy->GetXaxis()->SetBinLabel(6, "MiniRelIso<0.16");
        if(channel=="ElEl") hist_dummy->GetXaxis()->SetBinLabel(6, "MiniRelIso<0.12");
        hist_dummy->GetXaxis()->SetBinLabel(7, "MultiIso Tight");
        hist_dummy->GetXaxis()->SetBinLabel(8, "SUSY");
        if(channel=="ElEl") hist_dummy->GetXaxis()->SetBinLabel(9, "HeepID");


      }
      if(PassOrFail){
        hist_dummy->GetXaxis()->SetBinLabel(1, "Fail");
        hist_dummy->GetXaxis()->SetBinLabel(2, "Pass");
      }

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

      for(unsigned j=0; j<masses.size(); j++){

        int mZP = masses.at(j);
        //cout << "Z = " << mZP << endl;
        vector<int> hnmasses = GetHNMassRange(mZP);
        for(unsigned int k=0; k<hnmasses.size(); k++){
          int hnmass = hnmasses.at(k);
          //cout << "  mN = " << hnmass << endl;
          TString filename = "PairNAnalyzer_HNpair_"+channel+"_WR5000_Zp"+TString::Itoa(mZP,10)+"_HN"+TString::Itoa(hnmass,10)+"_official_cat_v8-0-7.root";
          TFile *file = new TFile(base_filepath+filename);
          TH1D *hist = (TH1D *)file->Get(vars.at(l));

          if(!hist){
            file->Close();
            continue;
          }

          hist->Rebin(n_rebin);
          hist->SetLineColor(colors.at(j));
          hist->SetLineWidth(2);
          hist->SetLineStyle(k+1);
          double this_scale = hist->GetEntries();

          if(CheckIsoPass) this_scale = hist->GetBinContent(1);
          else if(PassOrFail) this_scale = hist->GetEntries();
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
      if(YAxisLog) y_max_scale = 2.;
      hist_dummy->GetYaxis()->SetRangeUser(0.001, y_max_scale*this_ymax); //FIXME use getymin?

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




