// Origin: C.Perez V.Canoa (2016)

#ifndef tpcSteppingAction_h
#define tpcSteppingAction_h 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

class tpcSteppingAction : public G4UserSteppingAction {
 public:
  tpcSteppingAction();
  virtual ~tpcSteppingAction();
  virtual void UserSteppingAction(const G4Step*);
};

#endif
