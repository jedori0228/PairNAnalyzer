#ifndef LRSMSignalInfo_h
#define LRSMSignalInfo_h

class LRSMSignalInfo{
public :

  double mass_WR, mass_Z, mass_N;
  TString prod_channel;
  TString lep_channel;
  TString generator;
  TString FileName;

  void SetNames();
  TString filename, legendalias, texname;

  TString GetFileName();
  TString GetLegendAlias();
  TString GetTEXName();
  LRSMSignalInfo();

  bool operator==(LRSMSignalInfo b);

};


LRSMSignalInfo::LRSMSignalInfo(){ }

void LRSMSignalInfo::SetNames(){

  if(generator=="aMCNLO"){
    if(prod_channel=="pair"){
      filename = "HNPairToJJJJ_"+lep_channel+"_ZP"+TString::Itoa(mass_Z,10)+"_N"+TString::Itoa(mass_N,10)+"_WR"+TString::Itoa(mass_WR,10);
      legendalias = "m_{Z'} = "+TString::Itoa(mass_Z,10)+" GeV, m_{N} = "+TString::Itoa(mass_N,10);
      texname = "SignalPair"+lep_channel+"Z"+TString::Itoa(mass_Z,10)+"N"+TString::Itoa(mass_N,10);
    }
  }

}


TString LRSMSignalInfo::GetFileName(){
  return filename;
}

TString LRSMSignalInfo::GetLegendAlias(){
  return legendalias;
}

TString LRSMSignalInfo::GetTEXName(){
  return texname;
}

bool LRSMSignalInfo::operator== (LRSMSignalInfo b){

  if( this->prod_channel!=b.prod_channel ) return false;
  if( this->lep_channel!=b.lep_channel ) return false;
  if( this->generator!=b.generator ) return false;
  if( this->mass_WR!=b.mass_WR ) return false;
  if( this->mass_Z!=b.mass_Z ) return false;
  if( this->mass_N!=b.mass_N ) return false;

  return true;

}

#endif
