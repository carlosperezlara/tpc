// Origin: C.Perez V.Canoa (2016)

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "tpcDetectorConstruction.h"
#include "tpcSD.h"

G4ThreadLocal 
G4GlobalMagFieldMessenger* tpcDetectorConstruction::fMagFieldMessenger = 0;

tpcDetectorConstruction::tpcDetectorConstruction() :
  G4VUserDetectorConstruction(),
  fStepLimit(NULL),
  fCheckOverlaps(false) {
}

tpcDetectorConstruction::~tpcDetectorConstruction() {
  delete fStepLimit;
}

G4VPhysicalVolume* tpcDetectorConstruction::Construct() {
  G4NistManager* mManager = G4NistManager::Instance();
  G4Material *gas = mManager->FindOrBuildMaterial("G4_Ar");
  //G4Material *cu  = mManager->FindOrBuildMaterial("G4_Cu");
  G4Material *air = mManager->FindOrBuildMaterial("G4_AIR");

  G4double rMin = 30*cm;
  G4double rMax = 78*cm;
  G4double zHalf = 100*cm;
  G4double ang0 = 0*deg;
  G4double ang2Pi = 360*deg;

  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(2.2*zHalf); // 20% bigger than TPC
  G4cout << "Computed tolerance = "
         << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
         << " mm" << G4endl;

  //===> WORLD
  G4Tubs *shWorld = new G4Tubs("world",0,1.2*rMax,2.2*zHalf,ang0,ang2Pi);
  G4LogicalVolume* lvWorld = new G4LogicalVolume(shWorld,air,"World");
  lvWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
  G4VPhysicalVolume* pvWorld = new G4PVPlacement(0, G4ThreeVector(), lvWorld, "World", 
						 0, false, 0, fCheckOverlaps);

  //===> TPC
  G4VisAttributes *yellow = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  G4LogicalVolume *lvTPC[100];
  for(int i=0; i!=100; ++i) {
    G4double rIn = rMin+(i+0)*(rMax-rMin)/100;
    G4double rOu = rMin+(i+1)*(rMax-rMin)/100;
    G4Tubs *shTPC = new G4Tubs("shTPC",rIn,rOu,2*zHalf,ang0,ang2Pi);
    lvTPC[i] = new G4LogicalVolume(shTPC,gas,"lvTPC",0,0,0);
    lvTPC[i]->SetVisAttributes(yellow);
    new G4PVPlacement(0, G4ThreeVector(), lvTPC[i],
		      "TPC", lvWorld, false, i, fCheckOverlaps);
  }

  return pvWorld; // convention
}

void tpcDetectorConstruction::ConstructSDandField() {
  G4String sTPC = "TPCSIM/Hits";
  tpcSD *aTPC = new tpcSD(sTPC,"TPCMiniHits");
  SetSensitiveDetector("lvTPC",aTPC,true);

  fMagFieldMessenger = new G4GlobalMagFieldMessenger( G4ThreeVector(0,0,1) );
  fMagFieldMessenger->SetVerboseLevel(1);
  G4AutoDelete::Register(fMagFieldMessenger);
}
