// Origin: C.Perez V.Canoa (2016)

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "Randomize.hh"
#include "time.h"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "tpcDetectorConstruction.h"
#include "tpcActionInitialization.h"

int main(int argc,char** argv) {
  G4UIExecutive* ui = 0;
  if( argc==1 ) ui = new G4UIExecutive(argc, argv);
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);
  G4RunManager* runManager = new G4RunManager;
  runManager->SetUserInitialization(new tpcDetectorConstruction());
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);
  runManager->SetUserInitialization(new tpcActionInitialization());
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  if( !ui ) { // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  } else { // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if( ui->IsGUI() ) UImanager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
  }
  delete visManager;
  delete runManager;
}
