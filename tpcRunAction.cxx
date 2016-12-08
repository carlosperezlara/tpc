// Origin: C.Perez V.Canoa (2016)

#include "Randomize.hh"
#include "time.h"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "tpcRunAction.h"
#include "tpcEventAction.h"
#include "tpcAnalysis.h"
#include "tpcRun.h"

tpcRunAction::tpcRunAction() : G4UserRunAction() {
  G4RunManager::GetRunManager()->SetPrintProgress(1000);
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(4);
}

tpcRunAction::~tpcRunAction() {
  delete G4AnalysisManager::Instance();
}

void tpcRunAction::BeginOfRunAction(const G4Run* /*run*/) {
  //G4cout << "tpcRunAction::BeginOfRunAction[" << G4endl;
  G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  G4RunManager::GetRunManager()->SetRandomNumberStoreDir("random/");
  long seeds[2];
  time_t systime = time(NULL);
  seeds[0] = (long) systime;
  seeds[1] = (long) (systime*G4UniformRand());
  G4Random::setTheSeeds(seeds);
  G4Random::showEngineStatus();
 
  G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
  const tpcEventAction *constEventAction = static_cast<const tpcEventAction*> (G4RunManager::GetRunManager()->GetUserEventAction());
  tpcEventAction *eventAction = const_cast<tpcEventAction*> (constEventAction);

  eventAction->ClearVectors();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFileName("OutFileTPC");
  analysisManager->CreateNtuple("Hits", "Hits");
  analysisManager->CreateNtupleDColumn("x",eventAction->GetXs()); // column Id = 0
  analysisManager->CreateNtupleDColumn("y",eventAction->GetYs()); // column Id = 1
  analysisManager->CreateNtupleDColumn("z",eventAction->GetZs()); // column Id = 2
  analysisManager->CreateNtupleDColumn("edep",eventAction->GetEdeps()); // column Id = 2
  analysisManager->FinishNtuple();
  analysisManager->OpenFile();
  //G4cout << "tpcRunAction::BeginOfRunAction]" << G4endl;
}

void tpcRunAction::EndOfRunAction(const G4Run* /*run*/) {
  //G4cout << "tpcRunAction::EndOfRunAction[" << G4endl;
  G4Random::showEngineStatus();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
  //G4cout << "tpcRunAction::EndOfRunAction]" << G4endl;
}

G4Run* tpcRunAction::GenerateRun() {
  return new tpcRun;
}
