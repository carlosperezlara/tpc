// Origin: C.Perez V.Canoa (2016)

#include "tpcActionInitialization.h"
#include "tpcPrimaryGeneratorAction.h"
#include "tpcSteppingAction.h"
#include "tpcRunAction.h"
#include "tpcEventAction.h"

tpcActionInitialization::tpcActionInitialization() :
  G4VUserActionInitialization() {
}

tpcActionInitialization::~tpcActionInitialization() {
}

void tpcActionInitialization::BuildForMaster() const {
  SetUserAction(new tpcRunAction);
}

void tpcActionInitialization::Build() const {
  SetUserAction(new tpcPrimaryGeneratorAction);
  SetUserAction(new tpcSteppingAction);
  SetUserAction(new tpcRunAction);
  SetUserAction(new tpcEventAction);
}  
