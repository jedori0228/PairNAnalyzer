#define DileptonNtuple_cxx
#include "DileptonNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void DileptonNtuple::Loop(){

  Long64_t nentries = fChain->GetEntriesFast();
  //nentries = 1;

  hist_for_error = new TH1D("hist_for_error", "", 1, 0., 1.);
  hist_for_error_up = new TH1D("hist_for_error_up", "", 1, 0., 1.);

  for(Long64_t jentry=0; jentry<nentries;jentry++){
    GetEntry(jentry);

    if(!Pass()) continue;

    unweighted_yield += 1;
    weighted_yield += weight;

    hist_for_error->Fill(0. ,weight);
    hist_for_error_up->Fill(0., weight+weight_err);

    FillPlotHistogram();

/*
    if(ReadPdfSystematic){

      //vector<float>   *PdfWeights;
      //vector<float>   *ScaleWeights;

      //hist_Pdf_Replica = NULL;
      //hist_Pdf_Alpha = NULL;
      //hist_Pdf_Scale = NULL;

      //cout << "PdfWeights->size() = " << PdfWeights->size() << endl;
      //cout << "ScaleWeights->size() = " << ScaleWeights->size() << endl;

      if(PdfWeights->size()==0 || ScaleWeights->size()==0) continue;

      if(PdfWeights->size()==102){
        //==== Replica
        //==== at(0)~at(99)
        for(unsigned int i=0; i<100; i++){
          hist_Pdf_Replica->Fill(i, weight*(fabs(PdfWeights->at(i))));
        }

        //==== AlphaS
        //==== at(100), at(101)
        for(unsigned int i=0; i<2; i++){
          hist_Pdf_Alpha->Fill(i, weight*(fabs(PdfWeights->at(100+i))));
        }

        //==== Scale
        for(unsigned int i=0; i<6; i++){
          hist_Pdf_Scale->Fill(i, weight*(fabs(ScaleWeights->at(i))));
        }

      }

      else if(PdfWeights->size()==108){
        //==== Replica
        //==== at(0) : central
        //==== at(1)~at(100)
        for(unsigned int i=0; i<100; i++){
          hist_Pdf_Replica->Fill(i, weight*(fabs(PdfWeights->at(i+1))));
        }

        //==== AlphaS
        //==== at(101)~at(107)
        for(unsigned int i=0; i<7; i++){
          hist_Pdf_Alpha->Fill(i, weight*(fabs(PdfWeights->at(101+i))));
        }

        //==== Scale
        for(unsigned int i=0; i<6; i++){
          hist_Pdf_Scale->Fill(i, weight*(fabs(ScaleWeights->at(i))));
        }
      }

      else if(PdfWeights->size()==101){

        //==== Replica
        //==== at(0) : central
        //==== at(1)~at(100)
        for(unsigned int i=0; i<100; i++){
          hist_Pdf_Replica->Fill(i, weight*(fabs(PdfWeights->at(i+1))));
        }

        //==== AlphaS
        //==== no alphaS saved...
        int n_PdfWeights = PdfWeights->size();
        //==== n_PdfWeights-2
        //==== n_PdfWeights-1
        for(unsigned int i=0; i<2; i++){
          hist_Pdf_Alpha->Fill(i, weight*(fabs(PdfWeights->at(n_PdfWeights-2+i))));
        }

        //==== Scale
        for(unsigned int i=0; i<6; i++){
          hist_Pdf_Scale->Fill(i, weight*(fabs(ScaleWeights->at(i))));
        }

      }
      else{
        //==== Replica
        for(unsigned int i=0; i<100; i++){
          hist_Pdf_Replica->Fill(i, weight*(fabs(PdfWeights->at(i))));
        }

        //==== AlphaS
        int n_PdfWeights = PdfWeights->size();
        //==== n_PdfWeights-2
        //==== n_PdfWeights-1
        for(unsigned int i=0; i<2; i++){
          hist_Pdf_Alpha->Fill(i, weight*(fabs(PdfWeights->at(n_PdfWeights-2+i))));
        }

        //==== Scale
        for(unsigned int i=0; i<6; i++){
          hist_Pdf_Scale->Fill(i, weight*(fabs(ScaleWeights->at(i))));
        }
      }

    }
*/

  }

}























