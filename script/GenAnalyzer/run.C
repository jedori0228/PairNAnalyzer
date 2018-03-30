#include "LHENtuple.cc"

void run(){

  LHENtuple m("rootfiles/PairProduction_MuMu_ZR2500_N400_WR5000_LO.root");
  m.Loop();

  TFile *out = new TFile("hists.root","RECREATE");
  out->cd();
  for(map< TString, TH1* >::iterator it=m.maphist.begin(); it!=m.maphist.end(); it++){
    it->second->Write();
  }
  out->Close();

}
