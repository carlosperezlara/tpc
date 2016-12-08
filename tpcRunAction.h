// Origin: C.Perez V.Canoa (2016)

#ifndef tpcRunAction_h
#define tpcRunAction_h 1

#include <vector>
#include "G4UserRunAction.hh"

class G4Run;

class tpcRunAction : public G4UserRunAction {
 public:
  tpcRunAction();
  virtual ~tpcRunAction();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
  virtual G4Run* GenerateRun();
};

#endif
