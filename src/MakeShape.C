#include "RunNtupleBase.C"
#include "canvas_margin.h"
#include "LRSMSignalInfo.h"

void MakeShape(int x=0){

  TString ShapeVariable = "M_N";

  TFile *outfile = new TFile("test.root","RECREATE");

  TString channel = "MuMu";
  if(x==1) channel = "ElEl";
  if(x==2) channel = "MuEl";

  map< TString, vector<TString> > map_sample_string_to_list;
  map< TString, pair<TString, Color_t> > map_sample_string_to_legendinfo;
  vector<int> MCsector_first_index;
  map_sample_string_to_list["DY"] = {"DYJets_10to50", "DYJets"};
  map_sample_string_to_list["WJets"] = {"WJets"};
  map_sample_string_to_list["VV_excl"] = {
    //"WZTo3LNu_mllmin01",
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
  };
  map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ", "WW"};
  map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"};
  map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  map_sample_string_to_list["ttbar"] = {"TT_powheg"};
  map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  map_sample_string_to_list["top"] = {"ttW", "ttZ", "ttH_nonbb"};
  map_sample_string_to_list["top_tt"] = {"TT_powheg", "ttW", "ttZ", "ttH_nonbb"};
  map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted"};
  //map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG"};
  map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  map_sample_string_to_list["QCD"] = {"QCD_MuEnriched"};
  map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  map_sample_string_to_list["fake_Dijet_LooseBJet"] = {"fake_Dijet_LooseBJet"};
  map_sample_string_to_list["chargeflip"] = {"chargeflip"};
  map_sample_string_to_list["prompt"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted", "WZTo3LNu_powheg", "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ", "WWW", "WWZ", "WZZ", "ZZZ", "ttW", "ttZ", "ttH_nonbb", "WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};

  map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  map_sample_string_to_legendinfo["VV_excl"] = make_pair("diboson", kSpring-1);
  map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
  map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  map_sample_string_to_legendinfo["top_tt"] = make_pair("top", kRed);
  map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);
  map_sample_string_to_legendinfo["QCD"] = make_pair("QCD", 870);
  map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["fake_Dijet_LooseBJet"] = make_pair("Misid. lepton background", 870);
  map_sample_string_to_legendinfo["chargeflip"] = make_pair("Mismeas. charge background", kYellow);
  map_sample_string_to_legendinfo["prompt"] = make_pair("Prompt background", kSpring-1);

  vector<TString> samples_to_use = {"VVV", "ttV", "VV_incl", "ttbar", "DY", "WJets"};
  if(channel=="ElEl") samples_to_use = {"VVV", "ttV", "VV_incl", "ttbar", "DY", "WJets"};

  vector<TString> bkglist;
  for(unsigned int i=0; i<samples_to_use.size(); i++){
    MCsector_first_index.push_back( bkglist.size() );
    bkglist.insert(bkglist.end(),
                   map_sample_string_to_list[samples_to_use.at(i)].begin(),
                   map_sample_string_to_list[samples_to_use.at(i)].end()
                   );
  }
  //bkglist.push_back("data"); //FIXME data later
  cout << "We will use :" << endl;
  for(unsigned int i=0; i<bkglist.size(); i++) cout << " " << bkglist[i] << endl;

  //==== Get Envrionment Variables

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  bool DoDebug = false;

  vector<TString> WhichRegions = {
    "HTge300_SS",
  };
  vector<TString> TreeDirNames = {
    "",
  };
  
  for(unsigned int it_region=0; it_region<WhichRegions.size(); it_region++){

    TString WhichRegion = WhichRegions.at(it_region);
    TString TreeDirName = TreeDirNames.at(it_region);
    TString CutCarDirName = "";
    TString DataPD = "";
    TString ChannelName = "";

    if(channel=="ElEl"){
      DataPD = "DoubleEG";
      ChannelName = "DiElectron";
    }
    else if(channel=="MuMu"){
      DataPD = "SingleMuon";
      ChannelName = "DiMuon";
    }
    else if(channel=="MuEl"){
      DataPD = "MuonEG";
      ChannelName = "EMu";
    }

    CutCarDirName = WhichRegion;

    cout << "#### " << WhichRegion << " ####" << endl;
    cout << "#### " << TreeDirName << " ####" << endl;
    cout << "#### " << CutCarDirName << " ####" << endl;
    cout << "#### " << DataPD << " ####" << endl;
    cout << "#### " << ChannelName << " ####" << endl;

    vector<double> zmasses = {500, 1000, 3000};

    //==== Declare Object

    RunNtupleBase m;
    m.DoDebug = DoDebug;
    m.DrawBinnedYieldPlot = false;
    m.MakeYieldTable = false;

    m.MakeShapeFile = true;
    m.shape_var = ShapeVariable;
    m.shape_x_min = 0.;
    m.shape_x_max = 2000.;
    m.shape_nbin = 50;

    //==== Skim selection for tree (tree name : Ntp_<skim>)

    m.treeskim = "Preselection";

    //==== Plotting

    m.map_sample_string_to_list = map_sample_string_to_list;
    m.map_sample_string_to_legendinfo = map_sample_string_to_legendinfo;
    m.MCsector_first_index = MCsector_first_index;
    m.onlybkgd = bkglist;
    m.samples_to_use = samples_to_use;

    //==== Dataset/channel

    m.DataPD = DataPD;
    m.channel = ChannelName;

    //==== Filename info

    m.filename_prefix = "PairNAnalyzer";
    m.filename_suffix = "cat_"+catversion+".root";

    //==== Input/Output

    m.filepath = WORKING_DIR+"/rootfiles/"+dataset+"/Ntuple/"+TreeDirName+"/";

    //==== Signal Info

    for(int aaa=0; aaa<zmasses.size(); aaa++){

      double this_zmass = zmasses.at(aaa);

      LRSMSignalInfo lrsminfo;
      lrsminfo.prod_channel="pair";
      lrsminfo.lep_channel="MuMu";
      lrsminfo.generator="pythia";
      lrsminfo.mass_WR = 5000;
      lrsminfo.mass_Z = this_zmass;
      vector<int> nmasses = GetHNMassRange(lrsminfo.mass_Z);

      for(int bbb=0;bbb<nmasses.size(); bbb++){

        lrsminfo.mass_N = nmasses.at(bbb);
        lrsminfo.SetNames();
        m.signals.push_back(lrsminfo.GetCATFileName());

      }

    }

    m.MinEffPresel = 0.;
    m.FillSignalInfo();
    m.AddSamplesToList( m.signals );

    //==== Backgrounds

    m.AddSamplesToList( bkglist );

    if(DoDebug) m.PrintSampleList();

    //==== Fill MCNorm SF

    m.analysisInputs.DoPrint = false;
    m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.samples);

    //==== Get Systematics

    m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");
    m.SetSourceSystematics();

    //==== Set CutCard

    m.SetCutCard(WORKING_DIR+"/data/"+dataset+"/CutOpCard/"+CutCarDirName+".txt");

    m.Run();

    outfile->cd();
    cout << "size = " << m.hist_shapes.size() << endl;
    for(unsigned int aaa=0; aaa<m.hist_shapes.size(); aaa++){
      m.hist_shapes.at(aaa)->Write();

      //FIXME
      TString this_name = m.hist_shapes.at(aaa)->GetName();
      cout << this_name << "\t" << m.hist_shapes.at(aaa)->Integral() << endl;
      if(this_name.Contains("TT_powheg")){
        TH1D *temp_data = (TH1D *)m.hist_shapes.at(aaa)->Clone();
        temp_data->SetName("data_obs");
        temp_data->Write();
      }

    }
    //cout << m.hist_shapes.size() << endl;

    //==== FIXME HOTFIX
    for(unsigned int aaa=0; aaa<m.hist_shapes.size(); aaa++){

      TH1D *this_up = (TH1D *)m.hist_shapes.at(aaa)->Clone();
      for(int bbb=1; bbb<=this_up->GetXaxis()->GetNbins(); bbb++){
        this_up->SetBinContent(bbb, this_up->GetBinContent(bbb)+this_up->GetBinError(bbb));
      }
      TString this_name = this_up->GetName();
      this_up->SetName( this_name+"_StatUp" );
      this_up->Write();

    }
    for(unsigned int aaa=0; aaa<m.hist_shapes.size(); aaa++){

      TH1D *this_up = (TH1D *)m.hist_shapes.at(aaa)->Clone();
      for(int bbb=1; bbb<=this_up->GetXaxis()->GetNbins(); bbb++){
        this_up->SetBinContent(bbb, this_up->GetBinContent(bbb)-this_up->GetBinError(bbb));
      }
      TString this_name = this_up->GetName();
      this_up->SetName( this_name+"_StatDown" );
      this_up->Write();
    }

    outfile->Close();
    

/*
    delete hist_bkgd;
    delete hist_empty;
    delete hist_obs;
    for(unsigned int i=0; i<zmasses.size(); i++){
      delete hist_sigs.at(i);
    }
*/

  } // END Loop Region

}

