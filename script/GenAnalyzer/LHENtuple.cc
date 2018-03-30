#define LHENtuple_cxx
#include "LHENtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void LHENtuple::Loop()
{
  Long64_t nentries = fChain->GetEntriesFast();
  nentries=2000;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    GetEntry(jentry);

    // GenParticle N[2], Lepton[2], LeadingJet[2], SubleadingJet[2];

/*
    for(int i=0; i<Particle_size; i++){
      cout << Particle_PID[i] << "\t" << Particle_Mother1[i] << endl;
    }
*/

    int index_first_N = 0;
    if(Particle_size==10) index_first_N = 2;
    else if(Particle_size==11) index_first_N = 3;
    else continue;

    for(int i=0; i<2; i++){

      N[i].SetPxPyPzE(Particle_Px[index_first_N+i], Particle_Py[index_first_N+i], Particle_Pz[index_first_N+i], Particle_E[index_first_N+i]);
      Lepton[i].SetPxPyPzE(Particle_Px[index_first_N+2+i*3], Particle_Py[index_first_N+2+i*3], Particle_Pz[index_first_N+2+i*3], Particle_E[index_first_N+2+i*3]);
      Jet1[i].SetPxPyPzE(Particle_Px[index_first_N+3+i*3], Particle_Py[index_first_N+3+i*3], Particle_Pz[index_first_N+3+i*3], Particle_E[index_first_N+3+i*3]);
      Jet2[i].SetPxPyPzE(Particle_Px[index_first_N+4+i*3], Particle_Py[index_first_N+4+i*3], Particle_Pz[index_first_N+4+i*3], Particle_E[index_first_N+4+i*3]);

      FillHist("hist_mN", N[i].M(), 1., 20, 90., 110.);

      FillHist("Pair__DeltaR_Lepton_Jet", Lepton[i].DeltaR( Jet1[i] ), 1, 600, 0., 6.);
      FillHist("Pair__DeltaR_Lepton_Jet", Lepton[i].DeltaR( Jet2[i] ), 1, 600, 0., 6.);
      FillHist("Pair__DeltaR_Lepton_Jet1Jet2", Lepton[i].DeltaR( Jet1[i]+Jet2[i] ), 1, 600, 0., 6.);
      FillHist("Pair__DeltaR_Jet1_Jet2", Jet1[i].DeltaR( Jet2[i] ), 1, 600, 0., 6.);

    }

    FillHist("DeltaR_Leptons", Lepton[0].DeltaR( Lepton[1] ), 1, 600, 0., 6.);
    FillHist("DeltaPhi_Leptons", Lepton[0].DeltaPhi( Lepton[1] ), 1, 600, 0., 6.);


  }


}
