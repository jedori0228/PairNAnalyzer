#ifndef CutInfo_h
#define CutInfo_h

class CutInfo{
public :

  TString var;
  TString cutdir;
  double cutvalue;

  CutInfo();
  CutInfo(TString a, TString b, double c);
  void Print();

};


CutInfo::CutInfo() : var(""), cutdir(""), cutvalue(-999) { }

CutInfo::CutInfo(TString a, TString b, double c){

  var = a;
  cutdir = b;
  cutvalue = c;

}

void CutInfo::Print(){
  cout << "[CutInfo::PrintCutInfo] "<<var<<"\t"<<cutdir<<"\t"<<cutvalue<<endl;
}


#endif
