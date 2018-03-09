#ifndef GenParticle_h
#define GenParticle_h

#include "TLorentzVector.h"

class GenParticle : public TLorentzVector {
  public :
  void SetPID(int pid);
  int PID();

  GenParticle();
  virtual ~GenParticle();

  private:
  int j_pid;
  
};

GenParticle::GenParticle() : TLorentzVector(), j_pid(0)
{

}

GenParticle::~GenParticle()
{

}

void GenParticle::SetPID(int pid){
  j_pid = pid;
}

int GenParticle::PID(){
  return j_pid;
}

#endif
