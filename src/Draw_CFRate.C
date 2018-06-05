#include "canvas_margin.h"
#include "mylib.h"

void Draw_CFRate(){

  setTDRStyle();

  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  TString base_filepath = WORKING_DIR+"/rootfiles/"+dataset+"/CalcCFRate/";
  TString base_plotpath = ENV_PLOT_PATH+"/"+dataset+"/CalcCFRate/";

  if( !gSystem->mkdir(base_plotpath, kTRUE) ){
    cout
    << "###################################################" << endl
    << "Directoy " << base_plotpath << " is created" << endl
    << "###################################################" << endl
    << endl;
  }

  //==== Samples

  vector<TString> samples = {
    "ZToLL", "DYJets",
  };
  vector<TString> alias = {
    "DY (Binned)", "DY (Inclusive)",
  };
  vector<Color_t> sample_colors = {
    kRed, kYellow+2,
  };

  //==== Variables

  vector<TString> vars = {
    "Pt", "InvPt", "GenPt", "InvGenPt",
    "Eta",
    "RelIso", "MiniRelIso",
    "dXY", "dXYSig", "dZ", "dZSig", "IP3D", "IP3DSig",
    "Chi2", "MVANoIso",
  };
  vector<TString> xtitles = {
    "p_{T,RECO} (GeV)", "1/p_{T,RECO} (GeV^{-1})", "p_{T,GEN} (GeV)", "1/p_{T,GEN} (GeV^{-1})",
    "#eta", 
    "RelIso", "MiniRelIso",
    "|dXY| (cm)", "|dXYSig|", "|dZ| (cm)", "|dZSig|", "IP3D (cm)", "IP3DSig",
    "#chi^{2}", "MVA (No iso)",
  };
  vector<int> rebins = {
    50, 50, 50, 50,
    5,
    1, 1,
    10, 1, 10, 1, 10, 1,
    1, 5,
  };
  vector<double> x_maxs = {
    2000., 0.1, 2000., 0.1,
    3.,
    1.0, 1.0,
    0.5, 10, 0.5, 10, 0.5, 10,
    50, 1,
  };



  vector<TString> LeptonFlavours = {
    "Electron", "Muon"
  };

  for(unsigned int it_leptonflv=0; it_leptonflv<LeptonFlavours.size(); it_leptonflv++){

    TString Lepton = LeptonFlavours.at(it_leptonflv);

    //==== MC Fake Rate

    vector<TString> IDs = {
      "SUSYTight", "SUSYLoose",
    };

    for(unsigned int it_id=0; it_id<IDs.size(); it_id++){

      TString ID = IDs.at(it_id);

      TString this_dirname = base_plotpath+"/"+Lepton+"_"+ID+"/";
      gSystem->mkdir(this_dirname, kTRUE);

      for(unsigned int it_var=0; it_var<vars.size(); it_var++){

        TString var = vars.at(it_var);

        //==== For all samples in one plot
        TCanvas *c_CF_all = new TCanvas("c_CF_all", "", 600, 600);
        canvas_margin(c_CF_all);

        double x_max = x_maxs.at(it_var);
        double x_min = 0;
        if(var.Contains("Eta")) x_min = -3.;
        if(var.Contains("MVANoIso")) x_min = -1.;
        double dx = 0.001;
        if(var.Contains("Pt")&&!var.Contains("Inv")) dx = 1.;
        dx *= double(rebins.at(it_var));

        //cout << var << "\t" << int((x_max-x_min)/dx) << endl;

        TH1D *dummy_all = new TH1D("dummy_all", "", int((x_max-x_min)/dx), x_min, x_max);
        hist_axis(dummy_all);
        double y_max_all = 0.1;
        if(Lepton=="Muon") y_max_all = 0.01;
        dummy_all->GetYaxis()->SetRangeUser(0,y_max_all);
        dummy_all->GetYaxis()->SetTitle("CF rate");
        //c_CF_all->SetLogx();
        dummy_all->GetXaxis()->SetTitle(xtitles.at(it_var));
        dummy_all->Draw("hist");

        TLegend *lg = new TLegend(0.4, 0.6, 0.95, 0.95);
        lg->SetBorderSize(0);
        lg->SetFillStyle(0);

        bool IsCFFilled = false;

        for(unsigned int it_sample=0; it_sample<samples.size(); it_sample++){

          TString sample = samples.at(it_sample);

          TFile *file_MC = new TFile(base_filepath+"/CalcCFRate_"+sample+".root");

          TH1D *hist_Den = (TH1D *)file_MC->Get(Lepton+"_"+ID+"/"+Lepton+"_"+ID+"_Den_"+var);
          TH1D *hist_Num = (TH1D *)file_MC->Get(Lepton+"_"+ID+"/"+Lepton+"_"+ID+"_Num_"+var);

          if(!hist_Den) continue;

          IsCFFilled = true;

          if(var.Contains("Pt")&&!var.Contains("Inv")){

            double pt2array[9+1] = {0, 50, 100, 150, 200, 300, 500, 1000, 1500, 2000};

            hist_Den = (TH1D *)hist_Den->Rebin(9, "hnew1", pt2array);
            hist_Num = (TH1D *)hist_Num->Rebin(9, "hnew1", pt2array);

          }
          else{
            hist_Den->Rebin(rebins.at(it_var));
            hist_Num->Rebin(rebins.at(it_var));
          }

          //==== Den/Num distributions

          TCanvas *c_Dist = new TCanvas("c_Dist", "", 600, 600);
          canvas_margin(c_Dist);
          c_Dist->cd();

          TH1D *dummy = new TH1D("dummy", "", int((x_max-x_min)/dx), x_min, x_max);
          hist_axis(dummy);
          dummy->GetYaxis()->SetRangeUser(0,1.0);
          dummy->GetYaxis()->SetTitle("CF rate");
          //c_Dist->SetLogx();
          dummy->GetXaxis()->SetTitle(xtitles.at(it_var));
          dummy->Draw("hist");

          hist_Den->SetLineColor(kBlue);
          hist_Num->SetLineColor(kRed);

          hist_Den->Draw("histsame");
          hist_Num->Draw("histsame");

          double y_max = max( GetMaximum(hist_Den), GetMaximum(hist_Num) )*1.2;
          dummy->GetYaxis()->SetRangeUser(0, y_max);

          c_Dist->SaveAs(this_dirname+"/Dist_"+sample+"_"+var+".pdf");
          c_Dist->SaveAs(this_dirname+"/Dist_"+sample+"_"+var+".png");

          c_Dist->Close();

          //==== Fake Rate

          TEfficiency *Eff_CF = new TEfficiency(*hist_Num, *hist_Den);
          TGraphAsymmErrors *gr_CF = Eff_CF->CreateGraph();
          gr_CF->SetMarkerSize(0);
          gr_CF->SetLineWidth(3);
          gr_CF->Draw("lsame");

/*
          TCanvas *c_CF = new TCanvas("c_CF", "", 600, 600);
          canvas_margin(c_CF);
          c_CF->cd();
          dummy->Draw("hist");
          dummy->GetYaxis()->SetRangeUser(0,1.0);
          c_CF->SaveAs(this_dirname+"/1D_CF_"+sample+"_"+var+".pdf");
          c_CF->SaveAs(this_dirname+"/1D_CF_"+sample+"_"+var+".png");
          c_CF->Close();
*/

          c_CF_all->cd();
          gr_CF->Draw("lsame");
          gr_CF->SetLineColor(sample_colors.at(it_sample));
          lg->AddEntry(gr_CF, alias.at(it_sample), "l");

        } // END Loop sample

        if(!IsCFFilled){
          c_CF_all->Close();
          continue;
        }

        c_CF_all->cd();
        lg->Draw();

        c_CF_all->SaveAs(this_dirname+"/1D_CF_AllSamples_"+var+".pdf");
        c_CF_all->SaveAs(this_dirname+"/1D_CF_AllSamples_"+var+".png");

        c_CF_all->Close();

      } // END Loop variable

    } // END Loop ID


  }

}
