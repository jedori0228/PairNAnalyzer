#ifndef CutRangeInfo_h
#define CutRangeInfo_h

#include "CutInfo.h"

class CutRangeInfo{
public :

  map< TString, vector<CutInfo> > map_varANDdir_to_cutinfo;
  map< TString, int >             map_varANDdir_to_iterator;
  bool k_end, DoDebug, DoPrint;

  CutRangeInfo();
  void MakeCutInfo(TString var, TString cutdir, double start, double end, double nx);
  void Print();
  void PrintCurrent();
  void ReadCutCard(TString filepath);
  void FillCurrentCutInfoVector(vector<CutInfo>& vec);
  vector<CutInfo> GetCurrentCutInfo();
  void Next();

  inline bool isEnd() { return k_end; };
  Long64_t CurrentIteration;
  Long64_t TotalIteration;


};

CutRangeInfo::CutRangeInfo() :
k_end(false), DoDebug(false), DoPrint(true)
{

  map_varANDdir_to_cutinfo.clear();

}

void CutRangeInfo::MakeCutInfo(TString var, TString cutdir, double start, double end, double nx){

  map_varANDdir_to_cutinfo[var+"_"+cutdir].clear();
  map_varANDdir_to_iterator[var+"_"+cutdir] = 0;

  if(cutdir.Contains("<")){

    //==== pt < 10, 20, 30, 40
    //==== this case, we should start from right
    //==== start should be larger then end
    //==== if not, change
    if(start<end){
      double tmp = start;
      start = end;
      end = tmp;
    }

  }
  if(cutdir.Contains(">")){

    //==== pt > 10, 20, 30, 40
    //==== this case, we should start from left
    //==== start should be smaller then end
    //==== if not, change
    if(start>end){
      double tmp = start;
      start = end;
      end = tmp;
    }

  }

  if(nx==0) nx = 1;
  double dx = (end-start)/nx;

  for(int i=0; i<=nx; i++){

    double this_cutvalue = start+i*dx;

    CutInfo tmp_cutinfo(var, cutdir, this_cutvalue);
    map_varANDdir_to_cutinfo[var+"_"+cutdir].push_back( tmp_cutinfo );

    if(start==end) break;

  }


}

void CutRangeInfo::FillCurrentCutInfoVector(vector<CutInfo>& vec){

  vec.clear();

  for(map< TString, vector<CutInfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    vec.push_back( (it->second).at( map_varANDdir_to_iterator[it->first] ) );

  }

}

void CutRangeInfo::Next(){

  CurrentIteration++;

  if(DoDebug) cout << "[CutRangeInfo::Next] called" << endl; 

  map< TString, vector<CutInfo> >::iterator it = map_varANDdir_to_cutinfo.begin();

  if(it == map_varANDdir_to_cutinfo.end()){
    k_end = true;
    return;
  }

  bool DONE = false;  

  while( !DONE ){

    TString this_varANDdir = it->first;
    vector<CutInfo> this_cutinfo = it->second;
    int this_iterator = map_varANDdir_to_iterator[this_varANDdir];

    if(DoDebug){
      cout << "[CutRangeInfo::Next] "<<this_varANDdir<<"\t"<<this_iterator<<"\t"<<this_cutinfo.size()<<endl;
    }

    //==== Last iterator of this cut
    if( this_iterator == this_cutinfo.size()-1 ){
      if(DoDebug) cout << "[CutRangeInfo::Next] This cutinfo is finished its loop. Going back to fisrt value" << endl;
      map_varANDdir_to_iterator[this_varANDdir] = 0;
      it++;

      //==== If this was the last cut, this is the end of all loop
      if(it==map_varANDdir_to_cutinfo.end()){
        k_end = true;
        if(DoDebug) cout << "[CutRangeInfo::Next] Loop ENDED" << endl;
        break;
      }

    }
    //==== If not, just increase iterator by 1
    else{
      if(DoDebug) cout << "[CutRangeInfo::Next] Okay, increasing this varialbe. DONE=true" << endl;
      map_varANDdir_to_iterator[this_varANDdir]++;
      DONE = true;
    }

  }

}

void CutRangeInfo::Print(){

  for(map< TString, vector<CutInfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    cout << "[CutRangeInfo::PrintCutRangeInfo] "<<it->first<<endl;
    for(unsigned int i=0; i<(it->second).size(); i++){
      it->second.at(i).Print();
    }


  }

}

vector<CutInfo> CutRangeInfo::GetCurrentCutInfo(){

  vector<CutInfo> out;

  for(map< TString, vector<CutInfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    out.push_back( it->second.at( map_varANDdir_to_iterator[it->first] ) );

  }

  return out;

}

void CutRangeInfo::PrintCurrent(){

  for(map< TString, vector<CutInfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){

    it->second.at( map_varANDdir_to_iterator[it->first] ).Print();

  }

}

void CutRangeInfo::ReadCutCard(TString filepath){

  if(DoPrint) cout << "[CutRangeInfo::ReadCutCard] Get Cutcard from " << filepath << endl;

  string elline;
  ifstream in(filepath);
  while(getline(in,elline)){
    std::istringstream is( elline );

    TString var;
    TString cutdir;
    double start;
    double end;
    double nx;

    is >> var;
    is >> cutdir;
    is >> start;
    is >> end;
    is >> nx;

    if(var.Contains("#")){
      continue;
    }

    MakeCutInfo(var, cutdir, start, end, nx);

  }

  //==== Then, set iteration info based on cutcard
  CurrentIteration = 1;
  TotalIteration = 1;
  for(map< TString, vector<CutInfo> >::iterator it=map_varANDdir_to_cutinfo.begin(); it!=map_varANDdir_to_cutinfo.end(); it++){
    TotalIteration *= (it->second).size();
  }



}







#endif



















