#include "LHENtuple.cc"

void run(){

  LHENtuple m("PairProduction_MuMu_ZR2000_N100_WR5000_LO.root");
  m.Loop();

  TFile *out = new TFile("hists.root","RECREATE");
  out->cd();
  for(map< TString, TH1* >::iterator it=m.maphist.begin(); it!=m.maphist.end(); it++){
    it->second->Write();
  }
  out->Close();

}
