#include "RunNtupleBase.h"

void RunNtupleBase::Run(){

  //========================
  //==== CutRangeInfo Loop
  //========================

  vector<CutInfo> OptimizedCutInfo;
  double final_data(0.);
  double final_cf(0.), final_cf_err(0.), final_cf_syst(0.), final_cf_stat(0.);
  double final_fake(0.), final_fake_err(0.), final_fake_syst(0.), final_fake_stat(0.);
  double final_prompt(0.), final_prompt_err(0.), final_prompt_syst(0.), final_prompt_stat(0.);
  vector<double> final_signal, final_signal_eff, final_signal_eff_preselection, final_signal_err, final_signal_stat;
  for(unsigned int i=0; i<signals.size(); i++){
    final_signal.push_back(0.);
    final_signal_eff.push_back(0.);
    final_signal_eff_preselection.push_back(0.);
    final_signal_err.push_back(0.);
    final_signal_stat.push_back(0.);
  }

  while( !cutrangeinfo.isEnd() ){

    //==================
    //==== Sample Loop
    //==================

    double data_unweighted_yield(0.), data_weighted_yield(0.);
    double chargeflip_unweighted_yield(0.), chargeflip_weighted_yield(0.), chargeflip_weighted_yield_stat(0.);
    double chargeflip_lowstaterr(0.);
    double fake_unweighted_yield(0.), fake_weighted_yield(0.), fake_weighted_yield_stat(0.);
    double prompt_unweighted_yield(0.), prompt_weighted_yield(0.);

    TH1D *hist_prompt_total = new TH1D("hist_prompt_total", "", 1, 0., 1.); // Use TH1D::Add, to use GetBinError
    //==== MCSF up/down
    TH1D *hist_prompt_total_up = new TH1D("hist_prompt_total_up", "", 1, 0., 1.); // Just fill content, and only use GetBinContent
    
    vector<double> signal_unweighted_yield, signal_weighted_yield, signal_weighted_yield_stat;

    bool SignalEffLow = false;

    int ii_bkgd = -1;

    BookPlotHist(samples.size());

    for(unsigned int ii=0; ii<samples.size(); ii++){

      TString sample = samples.at(ii);
      bool issig = IsSignalCATSamaple(sample);

      if(!issig && !sample.Contains("data")) ii_bkgd++;

      Color_t color = kBlack;
      if(DrawBinnedYieldPlot) color = map_sample_string_to_legendinfo[find_MCsector(ii_bkgd)].second;

      bool ImRunningMCBkgd = false;

      TString                     filename = filename_prefix+"_SK"+     sample      +"_dilep_"+filename_suffix;
      if(sample=="data")          filename = filename_prefix+"_data_"+DataPD+"_"              +filename_suffix;
      else if(sample=="chargeflip")    filename = filename_prefix+"_SKchargeflip_"+DataPD+"_dilep_"+filename_suffix;
      else if(sample.Contains("fake")) filename = filename_prefix+"_SK"+sample+"_"+DataPD+"_dilep_"+filename_suffix;
      else if(issig)   filename = "/Signal/"+filename_prefix+"_"      +sample           +"_"+filename_suffix;
      else ImRunningMCBkgd = true;

      TString this_treename = "Ntp_"+channel+"_"+treeskim;
      bool DoPdfSystematic = false;
      if(RunSystematic){

        //==== If data or data-driven, use central ntuple
        if(sample.Contains("data") || sample.Contains("fake") || sample.Contains("chargeflip") ){
          this_treename = "Ntp_"+channel_for_jetres+"_"+treeskim;
        }

        //==== If Signal, read PdfWeights
        if(issig){
          DoPdfSystematic = true;
        }
      }
      DileptonNtuple m(filepath+filename, this_treename, DoPdfSystematic);

      if(! (m.TreeExist) ){

        cout << sample << "\t" << "No Tree : " << "Ntp_"+channel+"_"+treeskim << endl;
        if(issig){
          signal_unweighted_yield.push_back(0.);
          signal_weighted_yield.push_back(0.);
          signal_weighted_yield_stat.push_back(0.);

          SignalEffLow = true;
        }

        if(MakeShapeFile){
          hist_shapes.at(ii)->SetName(sample);
        }

        continue;

      }
      m.DoDebug = DoDebug;

      if(MakeShapeFile){
        m.DrawPlot = true;
        m.plot_var = shape_var;
        m.plot_name = sample;
        m.plot_x_min = shape_x_min;
        m.plot_x_max = shape_x_max;
        m.plot_nbin = shape_nbin;

        m.MakePlotHistogram();
      }

      //==== Fill CutInfo
      vector<CutInfo> cis;
      cutrangeinfo.FillCurrentCutInfoVector(cis);
      for(unsigned int iii=0;iii<cis.size();iii++) m.SetCutVariablesToUse(cis.at(iii));

      //==== Run
      m.Loop();

      if(MakeShapeFile){

        TDirectory *origDir = gDirectory;

        TDirectory *tempDir1 = pdfsyst.MakeTempDir();
        tempDir1->cd();

        hist_shapes.at(ii) = (TH1D *)m.hist_plot->Clone();
        yield_shapes.at(ii) = m.weighted_yield;

        origDir->cd();

        continue;
      }

      if(DrawBinnedYieldPlot){
        if(!issig && !sample.Contains("data")){
          TDirectory *origDir = gDirectory;
          TDirectory *tempDir1 = pdfsyst.MakeTempDir();
          tempDir1->cd();

          TH1D *histtmp = (TH1D *)m.hist_for_error->Clone();
          //cout << sample << "\t" << color << endl;
          histtmp->SetLineColor(color);
          histtmp->SetFillColor(color);
          histtmp->SetName(sample);
          MC_stacked->Add(histtmp);
          origDir->cd();
        }
      }

/*
      if(DoPdfSystematic){
        TDirectory *origDir = gDirectory;

        TDirectory *tempDir1 = pdfsyst.MakeTempDir();
        tempDir1->cd();
        pdfsyst.hist_Pdf_Replica = (TH1D *)m.hist_Pdf_Replica->Clone();
        pdfsyst.hist_Pdf_Alpha = (TH1D *)m.hist_Pdf_Alpha->Clone();
        pdfsyst.hist_Pdf_Scale = (TH1D *)m.hist_Pdf_Scale->Clone();

        origDir->cd();

      }
*/

      //==== If negative weighted yield, return.. Cut Too Tight
      if( m.weighted_yield < 0 ){
        if(issig){
          signal_unweighted_yield.push_back(0.);
          signal_weighted_yield.push_back(0.);
          signal_weighted_yield_stat.push_back(0.);
          SignalEffLow = true;
        }
        continue;
      }

      //==== Sum yield
      if(MakeYieldTable && issig){
        prompt_unweighted_yield += m.unweighted_yield;
        prompt_weighted_yield += m.weighted_yield;

        hist_prompt_total->Add( m.hist_for_error );
        hist_prompt_total_up->Fill(0., m.weighted_yield);

        signal_unweighted_yield.push_back( m.unweighted_yield );
        signal_weighted_yield.push_back( m.weighted_yield );
        signal_weighted_yield_stat.push_back( m.hist_for_error->GetBinError(1) );
      }
      else if(issig){
        signal_unweighted_yield.push_back( m.unweighted_yield );
        signal_weighted_yield.push_back( m.weighted_yield );
        signal_weighted_yield_stat.push_back( m.hist_for_error->GetBinError(1) );

        double eff_preselection = m.weighted_yield/signal_yield_preselection.at(ii);
        if(PrintYield) cout << "SignalEff@Preselection : " << sample << "\t" << eff_preselection << "\t" << m.unweighted_yield << endl;

        //==== If signal efficiency is lower than targer, finish the sample loop
        if(eff_preselection < MinEffPresel){
          SignalEffLow = true;
          break;
        }
      }
      else if(sample=="chargeflip"){
        chargeflip_unweighted_yield = m.unweighted_yield;
        chargeflip_weighted_yield = m.weighted_yield;

        chargeflip_weighted_yield_stat = m.hist_for_error->GetBinError(1);
        chargeflip_lowstaterr = m.hist_for_error_up->GetBinContent(1) - m.hist_for_error->GetBinContent(1);
        //double cf_propagation = m.hist_for_error_up->GetBinContent(1) - m.hist_for_error->GetBinContent(1);
        //chargeflip_weighted_yield_stat = sqrt( chargeflip_weighted_yield_stat*chargeflip_weighted_yield_stat + cf_propagation*cf_propagation );
      }
      else if(sample.Contains("fake")){
        fake_unweighted_yield = m.unweighted_yield;
        fake_weighted_yield = m.weighted_yield;

        fake_weighted_yield_stat = m.hist_for_error->GetBinError(1);
        //double fr_propagation = m.hist_for_error_up->GetBinContent(1) - m.hist_for_error->GetBinContent(1);
        //fake_weighted_yield_stat = sqrt( fake_weighted_yield_stat*fake_weighted_yield_stat + fr_propagation*fr_propagation );
      }
      else if(sample=="data"){
        data_unweighted_yield = m.unweighted_yield;
        data_weighted_yield = m.weighted_yield;
      }
      else{
        prompt_unweighted_yield += m.unweighted_yield;

        prompt_weighted_yield += m.weighted_yield * analysisInputs.MCNormSF[sample];
        hist_prompt_total->Add( m.hist_for_error );
        hist_prompt_total_up->Fill(0., m.weighted_yield * (analysisInputs.MCNormSF[sample]+analysisInputs.MCNormSF_uncert[sample]));
        //cout << sample << "\t" << analysisInputs.MCNormSF[sample] << "\t" << analysisInputs.MCNormSF_uncert[sample] << endl;
        
      }

      //==== Print this samples yield for Debugging
      if(PrintYield){
        if(sample=="data"){
          if(!ShowData) cout << sample << "\t" << "BLIND" << endl;
        }
        else{
          cout << sample << "\t" << m.weighted_yield << "\t" << m.hist_for_error->GetBinContent(1) << "\t" << m.hist_for_error->GetBinError(1) << "\t" << m.unweighted_yield << endl;
        }
      }

    } // END sample loop

    if(MakeShapeFile) break;

    //==== If SignalEffLow, go to next CutInfo.
    //==== XXX DON'T FORGET TO RESET MEMORY XXX
    if(SignalEffLow){
      cutrangeinfo.Next();
      delete hist_prompt_total;
      delete hist_prompt_total_up;
      continue;
    }

    //==== Stat. + Syst.
    double chargeflip_weighted_yield_syst = chargeflip_weighted_yield * uncert_cf;
    chargeflip_weighted_yield_syst = sqrt(chargeflip_weighted_yield_syst*chargeflip_weighted_yield_syst+chargeflip_lowstaterr*chargeflip_lowstaterr);
    double chargeflip_weighted_yield_err = sqrt( chargeflip_weighted_yield_stat*chargeflip_weighted_yield_stat + chargeflip_weighted_yield_syst*chargeflip_weighted_yield_syst );
    if(PrintYield){
      cout << "chargeflip_weighted_yield = " << chargeflip_weighted_yield << endl;
      cout << "  chargeflip_weighted_yield_stat = " << chargeflip_weighted_yield_stat << endl;
      cout << "  chargeflip_weighted_yield_syst = " << chargeflip_weighted_yield_syst << endl;
      cout << "  => chargeflip_weighted_yield_err = " << chargeflip_weighted_yield_err << endl;
    }

    double fake_weighted_yield_syst = fake_weighted_yield * uncert_fake;
    double fake_weighted_yield_err = sqrt( fake_weighted_yield_stat*fake_weighted_yield_stat + fake_weighted_yield_syst*fake_weighted_yield_syst );
    if(PrintYield){
      cout << "fake_weighted_yield = " << fake_weighted_yield << endl;
      cout << "  fake_weighted_yield_stat = " << fake_weighted_yield_stat << endl;
      cout << "  fake_weighted_yield_syst = " << fake_weighted_yield_syst << endl;
      cout << "  => fake_weighted_yield_err = " << fake_weighted_yield_err << endl;
    }

    double prompt_weighted_yield_stat = hist_prompt_total->GetBinError(1);
    double prompt_weighted_yield_syst_lumi = prompt_weighted_yield * uncert_lumi;
    double prompt_weighted_yield_syst_MCSF = hist_prompt_total_up->GetBinContent(1) - hist_prompt_total->GetBinContent(1);
    double prompt_weighted_yield_err = sqrt( prompt_weighted_yield_stat*prompt_weighted_yield_stat + prompt_weighted_yield_syst_lumi*prompt_weighted_yield_syst_lumi + prompt_weighted_yield_syst_MCSF*prompt_weighted_yield_syst_MCSF );
    if(PrintYield){
      cout << "prompt_weighted_yield = " << prompt_weighted_yield << endl;
      cout << "  prompt_weighted_yield_stat = " << prompt_weighted_yield_stat << endl;
      cout << "  prompt_weighted_yield_syst_lumi = " << prompt_weighted_yield_syst_lumi << endl;
      cout << "  prompt_weighted_yield_syst_MCSF = " << prompt_weighted_yield_syst_MCSF << endl;
      cout << "  => prompt_weighted_yield_err = " << prompt_weighted_yield_err << endl;
    }

    double total_bkg = prompt_weighted_yield+chargeflip_weighted_yield+fake_weighted_yield;
    double total_bkg_err_2 = chargeflip_weighted_yield_err*chargeflip_weighted_yield_err+fake_weighted_yield_err*fake_weighted_yield_err+prompt_weighted_yield_err*prompt_weighted_yield_err;

    delete hist_prompt_total;
    delete hist_prompt_total_up;

    //==== Force Punzi to require
    //==== 1) Minimum Total Bkgd
    //if( (total_bkg < 0.5) || (data_weighted_yield < 1) )

/*
    if( (total_bkg < 0.01) ){
      cutrangeinfo.Next();
      continue;
    }
*/

    //==== Signals
    bool ToUpdate = true;
    vector<double> sig_eff, punzis;
    for(unsigned int ii=0; ii<signals.size(); ii++){
      double eff_nocut = signal_weighted_yield.at(ii)/signal_yield_nocut.at(ii);
      double this_punzi = PunziFunction(eff_nocut, total_bkg, total_bkg_err_2);
      if(DoDebug) cout << signals.at(ii) << "\t" << signal_weighted_yield.at(ii) << "\t" << this_punzi << "\t" << signal_unweighted_yield.at(ii) << endl;

      sig_eff.push_back( eff_nocut );
      punzis.push_back( this_punzi );

      if(this_punzi < MaxPunzis.at(ii)){
        ToUpdate = false;
      }

    }

    if(ToUpdate){

      OptimizedCutInfo = cutrangeinfo.GetCurrentCutInfo();

      for(unsigned int iii=0; iii<signals.size(); iii++){
        final_signal.at(iii) = signal_weighted_yield.at(iii);
        final_signal_eff.at(iii) = signal_unweighted_yield.at(iii)/signal_yield_nocut.at(iii);

        double signal_lumi = signal_weighted_yield.at(iii)*uncert_lumi;
        double signal_stat = signal_weighted_yield_stat.at(iii);
        final_signal_err.at(iii) = sqrt(signal_lumi*signal_lumi+signal_stat*signal_stat);
        final_signal_stat.at(iii) = signal_stat;

        double eff_presel;
        if(signal_yield_preselection.at(iii)==0) eff_presel = 0;
        else eff_presel = signal_weighted_yield.at(iii)/signal_yield_preselection.at(iii);
        final_signal_eff_preselection.at(iii) = eff_presel;
        MaxPunzis.at(iii) = punzis.at(iii);

      }

      final_cf = chargeflip_weighted_yield;
      final_cf_err = chargeflip_weighted_yield_err;
      final_cf_syst = chargeflip_weighted_yield_syst;
      final_cf_stat = chargeflip_weighted_yield_stat;

      final_fake = fake_weighted_yield;
      final_fake_err = fake_weighted_yield_err;
      final_fake_syst = fake_weighted_yield_syst;
      final_fake_stat = fake_weighted_yield_stat;

      final_prompt = prompt_weighted_yield;
      final_prompt_err = prompt_weighted_yield_err;
      final_prompt_syst = prompt_weighted_yield_syst_MCSF;
      final_prompt_stat = prompt_weighted_yield_stat;

      final_data = data_unweighted_yield;

    }

    cutrangeinfo.Next();

  } //END CutRangeInfo loop

  y_observed = final_data;

  fake_bkgs = final_fake;
  fake_bkgs_err = final_fake_err;
  fake_bkgs_syst = final_fake_syst;
  fake_bkgs_stat = final_fake_stat;

  prompt_bkgs = final_prompt;
  prompt_bkgs_err = final_prompt_err;
  prompt_bkgs_syst = final_prompt_syst;
  prompt_bkgs_stat = final_prompt_stat;

  cf_bkgs = final_cf;
  cf_bkgs_err = final_cf_err;
  cf_bkgs_syst = final_cf_syst;
  cf_bkgs_stat = final_cf_stat;

  total_bkgs = final_cf+final_fake+final_prompt;
  total_bkgs_err = sqrt(final_fake_err*final_fake_err+final_prompt_err*final_prompt_err+final_cf_err*final_cf_err);


  signal_rate.clear();
  for(unsigned int i=0; i<signals.size(); i++){
    signal_rate.push_back( final_signal.at(i) );
    signal_err.push_back( final_signal_err.at(i) );
    signal_stat.push_back( final_signal_stat.at(i) );
    signal_eff.push_back( final_signal_eff.at(i) );
  }

}













