// Origin: C.Perez V.Canoa (2016)

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "tpcSD.h"
#include "tpcHit.h"

tpcSD::tpcSD(const G4String& name,
			     const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL) {
  collectionName.insert(hitsCollectionName);
}

tpcSD::~tpcSD() {
}

void tpcSD::Initialize(G4HCofThisEvent* hce) {
  fHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}

G4bool tpcSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
  //G4cout << "tpcSD::ProcessHits[" << G4endl;
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return false;
  tpcHit* newHit = new tpcHit();
  //newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetEdep(edep);
  newHit->SetXYZ(aStep->GetPostStepPoint()->GetPosition());
  fHitsCollection->insert( newHit );
  //G4cout << "tpcSD::ProcessHits]" << G4endl;
  return true;
}

void tpcSD::EndOfEvent(G4HCofThisEvent*) {
  if ( verboseLevel>1 ) { 
     G4int nofHits = fHitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits 
            << " hits in the TPC: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}
