// Origin: C.Perez V.Canoa (2016)

#include "G4Event.hh"
#include "G4SDManager.hh"

#include "tpcRun.h"
#include "tpcHit.h"

tpcRun::tpcRun() : G4Run() {
}

void tpcRun::RecordEvent(const G4Event* evt) {
  //G4cout << "tpcRun::RecordEvent[" << G4endl;
  G4Run::RecordEvent(evt);
  /*
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();
  G4int id = sdManager->GetCollectionID("TPCMiniHits");
  G4HCofThisEvent* hce = evt->GetHCofThisEvent();
  const TrackerHitsCollection* tpcHC = static_cast<const TrackerHitsCollection*>( hce->GetHC(id) );
  for(size_t i=0; i!=tpcHC->GetSize(); ++i) {
    tpcHit* hit = (*tpcHC)[i];
    // got them!
  }
  */
  //G4cout << "tpcRun::RecordEvent]" << G4endl;
}

void tpcRun::Merge(const G4Run*) {
}
