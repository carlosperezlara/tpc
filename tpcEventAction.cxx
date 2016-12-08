// Origin: C.Perez V.Canoa (2016)

#include <vector>
#include "Randomize.hh"
#include "time.h"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "tpcEventAction.h"
#include "tpcHit.h"
#include "tpcAnalysis.h"
#include "tpcRunAction.h"
#include "tpcDetectorConstruction.h"

tpcEventAction::tpcEventAction() :
  G4UserEventAction(), fHCID(-1) {
  G4RunManager::GetRunManager()->SetPrintProgress(1);
}

tpcEventAction::~tpcEventAction() {
}

void tpcEventAction::BeginOfEventAction(const G4Event*) {
  ClearVectors();
  G4SDManager *sdManager = G4SDManager::GetSDMpointer();
  fHCID = sdManager->GetCollectionID("TPCMiniHits");
  //fCCID = sdManager->GetCollectionID("TPCMiniClouds");
}

void tpcEventAction::EndOfEventAction(const G4Event* event) {
  G4HCofThisEvent *hce = event->GetHCofThisEvent();
  G4PrimaryVertex *primaryVertex = event->GetPrimaryVertex();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  TrackerHitsCollection *hc = static_cast<TrackerHitsCollection*>(hce->GetHC(fHCID));
  //TPCCellsCollection *cc = static_cast<TPCCellsCollection*>(hce->GetHC(fCCID));
  G4int nhit = hc->entries();
  for(G4int i=0; i!=nhit; ++i) {
    tpcHit *hit = (*hc)[i];
    fEdeps.push_back( hit->GetEdep()/keV );
    fXs.push_back( hit->GetX()/cm );
    fYs.push_back( hit->GetY()/cm );
    fZs.push_back( hit->GetZ()/cm );
  }
  analysisManager->AddNtupleRow();

}  
