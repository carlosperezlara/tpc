// Origin: C.Perez V.Canoa (2016)

#ifndef tpcRUN_HH
#define tpcRUN_HH

#include "G4Run.hh"

class G4Event;

class tpcRun : public G4Run {
public:
  tpcRun();
  virtual ~tpcRun() {};

  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);
  
private:
};
#endif
