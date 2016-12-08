// Origin: C.Perez V.Canoa (2016)

#ifndef tpcSD_h
#define tpcSD_h 1

#include <vector>
#include "G4VSensitiveDetector.hh"
#include "tpcHit.h"

class G4Step;
class G4HCofThisEvent;

class tpcSD : public G4VSensitiveDetector {
 public:
  tpcSD(const G4String& name, const G4String& hitsCollectionName);
  virtual ~tpcSD();
  
  virtual void   Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);
  
 private:
  TrackerHitsCollection* fHitsCollection;
};

#endif
