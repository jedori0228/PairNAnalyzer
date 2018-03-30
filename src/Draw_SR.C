#include "Plotter.cc"
#include <fstream>

void Draw_SR(int XXX=0){

  bool ScaleMC = false;

  //==============
  //==== get env
  //==============
  
  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString catversion = getenv("CATVERSION");
  TString dataset = getenv("CATANVERSION");
  TString ENV_PLOT_PATH = getenv("PLOT_PATH");

  //====================
  //==== decalre class
  //====================
  
  Plotter m;
  m.DoDebug = false;
  
  //=====================
  //==== set data class
  //=====================
  
  m.data_class = dataset+"/Regions/";
  
  //================================
  //==== set prefixes and suffixes
  //================================
  
  m.filename_prefix = "PairNAnalyzer";
  m.filename_suffix = "_cat_"+catversion+".root";
  
  //=========================
  //==== set sample mapping
  //=========================
  
  m.map_sample_string_to_list["DY"] = {"DYJets_10to50", "DYJets"};
  m.map_sample_string_to_list["WJets"] = {"WJets"};
  m.map_sample_string_to_list["VV_excl"] = {
    //"WZTo3LNu_mllmin01",
    "WZTo3LNu_powheg",
    "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ",
  };
  m.map_sample_string_to_list["VV_incl"] = {"WZ", "ZZ", "WW"};
  m.map_sample_string_to_list["WZ_excl"] = {"WZTo3LNu_powheg"};
  m.map_sample_string_to_list["ZZ_excl"] = {"ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau"};
  m.map_sample_string_to_list["VVV"] = {"WWW", "WWZ", "WZZ", "ZZZ"};
  m.map_sample_string_to_list["ttbar"] = {"TT_powheg"};
  m.map_sample_string_to_list["ttbar_ll"] = {"TTLL_powheg"};
  m.map_sample_string_to_list["ttV"] = {"ttW", "ttZ", "ttH_nonbb"}; //FIXME ttH into ttV
  m.map_sample_string_to_list["ttH"] = {"ttH_nonbb"};
  m.map_sample_string_to_list["top"] = {"ttW", "ttZ", "ttH_nonbb"};
  m.map_sample_string_to_list["top_tt"] = {"TT_powheg", "ttW", "ttZ", "ttH_nonbb"};
  m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted"};
  //m.map_sample_string_to_list["Xgamma"] = {"TG", "TTG", "ZGto2LG"};
  m.map_sample_string_to_list["WW_double"] = {"WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};
  m.map_sample_string_to_list["QCD"] = {"QCD_MuEnriched"};
  m.map_sample_string_to_list["ttV_lep"] = {"ttWToLNu", "ttZToLL_M-1to10"};
  m.map_sample_string_to_list["fake_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY"] = {"fake_sfed_HighdXY"};
  m.map_sample_string_to_list["fake_sfed_HighdXY_UsePtCone"] = {"fake_sfed_HighdXY_UsePtCone"};
  m.map_sample_string_to_list["fake_DiMuon_HighdXY"] = {"fake_HighdXY"};
  m.map_sample_string_to_list["fake_Dijet"] = {"fake_Dijet"};
  m.map_sample_string_to_list["fake_Dijet_LooseBJet"] = {"fake_Dijet_LooseBJet"};
  m.map_sample_string_to_list["chargeflip"] = {"chargeflip"};
  m.map_sample_string_to_list["prompt"] = {"TG", "TTG", "ZGto2LG", "WGtoLNuG_weighted", "WZTo3LNu_powheg", "ZZTo4L_powheg", "ggZZto2e2mu", "ggZZto2e2nu", "ggZZto2e2tau", "ggZZto2mu2nu", "ggZZto2mu2tau", "ggZZto4e", "ggZZto4mu", "ggZZto4tau", "ggHtoZZ", "WWW", "WWZ", "WZZ", "ZZZ", "ttW", "ttZ", "ttH_nonbb", "WWTo2L2Nu_DS", "WpWpEWK", "WpWpQCD"};

  m.map_sample_string_to_legendinfo["DY"] = make_pair("DY", kYellow);
  m.map_sample_string_to_legendinfo["WJets"] = make_pair("WJets", kGreen);
  m.map_sample_string_to_legendinfo["VV_excl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["VV_incl"] = make_pair("diboson", kSpring-1);
  m.map_sample_string_to_legendinfo["WZ_excl"] = make_pair("WZ", kGreen);
  m.map_sample_string_to_legendinfo["ZZ_excl"] = make_pair("ZZ", kRed-7);
  m.map_sample_string_to_legendinfo["VVV"] = make_pair("triboson", kSpring+10);
  m.map_sample_string_to_legendinfo["ttbar"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttbar_ll"] = make_pair("ttbar", kRed);
  m.map_sample_string_to_legendinfo["ttV"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["ttH"] = make_pair("ttH", kOrange);
  m.map_sample_string_to_legendinfo["top"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["top_tt"] = make_pair("top", kRed);
  m.map_sample_string_to_legendinfo["Xgamma"] = make_pair("X + #gamma", kSpring-7);
  m.map_sample_string_to_legendinfo["WW_double"] = make_pair("DoubleWW", 74);
  m.map_sample_string_to_legendinfo["ttV_lep"] = make_pair("ttV", kOrange);
  m.map_sample_string_to_legendinfo["QCD"] = make_pair("QCD", 870);
  m.map_sample_string_to_legendinfo["fake_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_sfed_HighdXY_UsePtCone"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_DiMuon_HighdXY"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_Dijet"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["fake_Dijet_LooseBJet"] = make_pair("Misid. lepton background", 870);
  m.map_sample_string_to_legendinfo["chargeflip"] = make_pair("Mismeas. charge background", kYellow);
  m.map_sample_string_to_legendinfo["prompt"] = make_pair("Prompt background", kSpring-1);
  
  //===============================
  //==== set and make sample list
  //===============================

  //==== _Di<Lepton>_<JetSel>_<ifOffZ>_<charge>

  //==== SS
  if(XXX==0){
    m.samples_to_use = {"VVV", "VV", "ttbar", "DY", "WJets"};

    m.histname_suffix = {

      "_DiMuon_SS",

    };
  }
  //==== OS
  if(XXX==1){
    m.samples_to_use = {"VVV", "VV", "WJets", "ttbar", "DY"};

    m.histname_suffix = {

      "_DiMuon_AllCharge",

    };
  }

  //============================
  //==== set variables to draw
  //============================
  
  m.histname = {
    "Njets", "Njets_nolepveto", "Nfwdjets", "Nbjets", "Nbjets_nolepveto", "Nbfwdjets",
    "Nleptons",
     //==== Lepton
    "m_ll",
    "leadingLepton_Pt", "leadingLepton_Eta", "leadingLepton_Type",
    "secondLepton_Pt", "secondLepton_Eta", "secondLepton_Type",
    //==== AK4 Jet
    "leadingJet_Pt", "leadingJet_Eta",
    "secondJet_Pt", "secondJet_Eta",
    "leadingForwardJet_Pt", "leadingForwardJet_Eta",
    "secondForwardJet_Pt", "secondForwardJet_Eta",
    "leadingNoLepVetoJet_Pt", "leadingNoLepVetoJet_Eta",
    "secondNoLepVetoJet_Pt", "secondNoLepVetoJet_Eta",
    "PFMET", "PFMET_phi", "HT", "ST",
    "MET2overST",
    "Nvtx", "DeltaRl1l2", "Nevents",
    //==== Fatjet
    "Nfatjets",
    //==== PairN
    "N_Mass", "Z_Mass",
  };

  m.x_title = {
    "# of jets", "# of No-LeptonVeto jets", "# of forward jets", "# of b-jets", "# of No-LeptonVeto b-jets", "# of forward b-jets",
    "# of leptons",
    //==== Lepton
    "m(ll) (GeV)",
    "Leading Lepton p_{T} (GeV)", "Leading Lepton #eta", "Leading Lepton Type",
    "Subleading Lepton p_{T} (GeV)", "Subleading Lepton #eta", "Subleading Lepton Type",
    //==== AK4 Jet
    "Leading Jet p_{T} (GeV)", "Leading Jet #eta",
    "Subleading Jet p_{T} (GeV)", "Subleading Jet #eta",
    "Leading Forward Jet p_{T} (GeV)", "Leading Forward Jet #eta",
    "Subleading Forward Jet p_{T} (GeV)", "Subleading Forward Jet #eta",
    "Leading No-LeptonVeto Jet p_{T} (GeV)", "Leading No-LeptonVeto Jet #eta",
    "Subleading No-LeptonVeto Jet p_{T} (GeV)", "Subleading No-LeptonVeto Jet #eta",
    "#slash{E}_{T}^{miss} (GeV)", "#phi of #slash{E}_{T}^{miss}", "H_{T} (GeV)", "S_{T} (GeV)",
    "#slash{E}_{T}^{miss}^{2}/S_{T} (GeV)",
    "# of vertices", "#DeltaR(l_{1},l_{2})", "onebin",
    //==== Fatjet
    "# of Fatjet",
    //==== PairN
    "m_{N,RECO} (GeV)", "m_{Z',RECO} (GeV)",
  };

  m.units = {
    "int", "int", "int", "int", "int", "int",
    "int",
    //==== Lepton
    "GeV",
    "GeV", "", "int",
    "GeV", "", "int",
    //==== AK4 Jet
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "",
    "GeV", "", "GeV", "GeV",
    "GeV",
    "int", "", "int",
    //==== Fatjet
    "int",
    //==== PairN
    "GeV","GeV",
  };

  //==== TEST
  if(XXX==-1){
    m.samples_to_use = {"chargeflip", "Xgamma", "fake_Dijet", "VV_excl", "VVV", "top", "WW_double"};

    m.histname_suffix = {"_DiMuon_Preselection_SS"};
    m.PrimaryDataset = {"DoubleMuon"};
    m.LeptonChannels = {21};
    m.RegionType = {0};
    m.UseLogy = {-1};
    m.histname = {"m_lljj_lljjWclosest"};
    m.x_title = {"m(lljj_{W}) (GeV)"};
    m.units = {"GeV"};

  }

  for(unsigned int i=0; i<m.histname_suffix.size(); i++){

    //==== PD
    if(m.histname_suffix.at(i).Contains("DiMuon")){
      m.PrimaryDataset.push_back("DoubleMuon");
      m.LeptonChannels.push_back(21);
    }
    else if(m.histname_suffix.at(i).Contains("DiElectron")){
      m.PrimaryDataset.push_back("DoubleEG");
      m.LeptonChannels.push_back(22);
    }
    else if(m.histname_suffix.at(i).Contains("EMu")){
      m.PrimaryDataset.push_back("MuonEG");
      m.LeptonChannels.push_back(23);
    }
    else if(m.histname_suffix.at(i).Contains("DiLepton")){
      m.PrimaryDataset.push_back("DiLepton");
      m.LeptonChannels.push_back(20);
    }
    else{
      cout << "ERROR : PD not correct" << endl;
      return;
    }

    if(m.histname_suffix.at(i).Contains("Preselection")){
      m.RegionType.push_back(1);
    }
    else if(m.histname_suffix.at(i).Contains("Low")){
      if(m.histname_suffix.at(i).Contains("TwoJet_NoFatJet")) m.RegionType.push_back(21);
      else if(m.histname_suffix.at(i).Contains("OneJet_NoFatJet")) m.RegionType.push_back(22);
      else m.RegionType.push_back(20);
    }
    else if(m.histname_suffix.at(i).Contains("High")){
      if(m.histname_suffix.at(i).Contains("TwoJet_NoFatJet")) m.RegionType.push_back(31);
      else if(m.histname_suffix.at(i).Contains("OneFatJet")) m.RegionType.push_back(32);
      else m.RegionType.push_back(30);
    }
    else{
      m.RegionType.push_back(0);
    }

    //==== Log plot boolean
    if(XXX==0) m.UseLogy.push_back(-1);
    else if(XXX==1) m.UseLogy.push_back(1);
    else m.UseLogy.push_back(-1);

    if(ScaleMC) m.ApplyMCNormSF.push_back(true);
    else m.ApplyMCNormSF.push_back(false);

    //if(m.histname_suffix.at(i).Contains("Preselection")) m.drawdata.push_back(true);
    //else m.drawdata.push_back(false);

    //m.drawdata.push_back(false);

    m.drawdata.push_back(true);

    //if(m.histname_suffix.at(i).Contains("DiLepton")) m.drawratio.push_back(false);
    //else m.drawratio.push_back(true);

    m.drawratio.push_back(true);

  }


/*
  //==== FIXME test
  m.histname = {"m_lljj_lljjWclosest", "m_llj"};
  m.x_title = {"m(l^{#pm}l^{#pm}W_{jet}) (GeV)", "m(l^{#pm}l^{#pm}W_{jet}) (GeV)"};
  m.units = {"GeV", "GeV"};
*/

  cout << "m.histname.size() = " <<  m.histname.size() << endl;
  cout << "m.x_title.size() = " << m.x_title.size() << endl;
  cout << "m.units.size() = " << m.units.size() << endl;
  if(m.histname.size()==m.x_title.size() && m.x_title.size()==m.units.size()){
    cout << "--> OKAY" << endl;
  }
  else{
    cout << "--> WRONG" << endl;
    return;
  }
  cout << "Histname\tXTitle\tUnit" << endl;
  for(unsigned int i=0; i<m.histname.size(); i++){
    cout << m.histname.at(i) << "\t" << m.x_title.at(i) << "\t" << m.units.at(i) << endl;
  }

  //====================
  //==== make bkg list
  //====================

  m.make_bkglist();

  //=====================
  //==== Fill MCNorm SF
  //=====================

  m.analysisInputs.SetMCSF(WORKING_DIR+"/data/"+dataset+"/MCSF.txt", m.bkglist);

  //======================
  //==== Get Systematics
  //======================

  m.analysisInputs.SetCalculatedSysts(WORKING_DIR+"/data/"+dataset+"/Syst.txt");

  //=============================
  //==== set signal mass points
  //=============================

  if(XXX==0 || XXX==1){
  //==== general AN

    vector<double> zmasses = {500, 1000, 3000};
    vector<Color_t> colors_zmass = {kGreen, kViolet, kGray};
    for(int i=0; i<zmasses.size(); i++){

      double this_zmass = zmasses.at(i);
      Color_t this_color = colors_zmass.at(i);

      LRSMSignalInfo lrsminfo;
      lrsminfo.prod_channel="pair";
      lrsminfo.lep_channel="MuMu";
      lrsminfo.generator="pythia";
      lrsminfo.mass_WR = 5000;
      lrsminfo.mass_Z = this_zmass;
      vector<int> nmasses = GetHNMassRange(lrsminfo.mass_Z);

      for(int j=0;j<nmasses.size(); j++){

        lrsminfo.mass_N = nmasses.at(j);
        lrsminfo.SetNames();

        m.signal_LRSMinfo.push_back(lrsminfo);
        m.signal_color.push_back(this_color);
        m.signal_style.push_back(j+1);
        m.signal_draw.push_back(true);
      }

    }
  }

  //=====================================
  //==== set signal mass for each class
  //=====================================

  for(unsigned int i=0; i<m.signal_LRSMinfo.size(); i++){
    LRSMSignalInfo this_lrsm = m.signal_LRSMinfo.at(i);

    m.map_class_to_LRSMSignalInfo[Plotter::inclusive].push_back( this_lrsm );
  }
  m.AllSignalClasses = {Plotter::inclusive};

  //=============
  //==== rebins
  //=============
  
  //==== script to generate rebins
  ofstream skeleton_rebins("./data/SR_rebins.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_rebins
      //<< "m.rebins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_rebins.close();

  m.SetRebins(WORKING_DIR+"/data/"+dataset+"/SR_rebins.txt");

  //=============
  //==== y_maxs
  //=============
  
  //==== script to generate rebins
  ofstream skeleton_y_maxs("./data/SR_yaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_y_maxs
      //<< "  m.y_maxs[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<endl;
    }
  }
  skeleton_y_maxs.close();


  //==== default max
  m.default_y_max = 20.;
  m.default_y_min = 0.;

  m.SetYAxis(WORKING_DIR+"/data/"+dataset+"/SR_yaxis.txt"); 

  //=============
  //==== x_mins
  //=============


  //==== script to generate rebins
  ofstream skeleton_x_mins("./data/SR_xaxis.txt", ios::trunc);
  for(unsigned int i=0; i<m.histname_suffix.size(); i++){
    for(unsigned int j=0; j<m.histname.size(); j++){
      skeleton_x_mins
      //<< "  m.x_mins[make_pair(\""+m.histname_suffix.at(i)+"\", \""+m.histname.at(j)+"\")] = 1;" << endl;
      <<m.histname_suffix.at(i)<<"\t"<<m.histname.at(j)<<"\t"<<-999<<"\t"<<-999<<endl;
    }
  }
  skeleton_x_mins.close();



  m.SetXAxis(WORKING_DIR+"/data/"+dataset+"/SR_xaxis.txt");

  //===============
  //==== k-factor
  //===============
  
  m.k_factor = 1;
  
  //=================================
  //==== mixing at generation level
  //=================================
  
  m.log_of_generation_mixing = 1.;
  
  //===============================
  //==== prepare plot directories
  //===============================
  
  m.plotpath = ENV_PLOT_PATH+"/"+m.data_class+"/SR/";
  m.make_plot_directory();
  
  //==========================
  //==== finally, draw plots
  //==========================
  
  m.draw_hist();
  
}






