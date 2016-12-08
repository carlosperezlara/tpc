// Origin: C.Perez V.Canoa (2016)

#include "tpcPrimaryGeneratorAction.h"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"

tpcPrimaryGeneratorAction::tpcPrimaryGeneratorAction() :
  G4VUserPrimaryGeneratorAction() {
  G4int nofParticles = 1;
  fParticleGun = new G4GeneralParticleSource();
  fParticleGun->SetNumberOfParticles(nofParticles);
}

tpcPrimaryGeneratorAction::~tpcPrimaryGeneratorAction() {
  delete fParticleGun;
}

void tpcPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
