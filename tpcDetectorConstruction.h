// Origin: C.Perez V.Canoa (2016)

#ifndef tpcDetectorConstruction_h
#define tpcDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"
#include "G4UserLimits.hh"

class G4VPhysicalVolume;
class G4Material;
class G4GlobalMagFieldMessenger;

class tpcDetectorConstruction : public G4VUserDetectorConstruction {
 public:
  tpcDetectorConstruction();
  virtual ~tpcDetectorConstruction();
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  void SetMaxStep(G4double val) {if ((fStepLimit)&&(val>0)) fStepLimit->SetMaxAllowedStep(val);}
  void SetCheckOverlaps(G4bool val) {fCheckOverlaps = val;}

 private:
  G4UserLimits *fStepLimit;
  G4bool fCheckOverlaps;
  static G4ThreadLocal G4GlobalMagFieldMessenger *fMagFieldMessenger; 
};

#endif
