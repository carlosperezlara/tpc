// Origin: C.Perez V.Canoa (2016)

#ifndef tpcPrimaryGeneratorAction_h
#define tpcPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

class tpcPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  tpcPrimaryGeneratorAction();    
  virtual ~tpcPrimaryGeneratorAction();
  virtual void GeneratePrimaries(G4Event*);
  G4GeneralParticleSource* GetParticleGun() {return fParticleGun;}
  void SetRandomFlag(G4bool);
  
private:
  G4GeneralParticleSource* fParticleGun;
};

#endif
