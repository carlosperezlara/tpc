// Origin: C.Perez V.Canoa (2016)

#ifndef tpcEventAction_h
#define tpcEventAction_h 1

#include <vector>
#include "G4UserEventAction.hh"
#include "globals.hh"

class tpcEventAction : public G4UserEventAction {
 public:
  tpcEventAction();
  virtual ~tpcEventAction();
  virtual void BeginOfEventAction(const G4Event* );
  virtual void EndOfEventAction(const G4Event* );
  std::vector<G4double>& GetXs() { return fXs; }
  std::vector<G4double>& GetYs() { return fYs; }
  std::vector<G4double>& GetZs() { return fZs; }
  std::vector<G4double>& GetEdeps() { return fEdeps; }
  void ClearVectors(){
    fXs.clear();
    fYs.clear();
    fZs.clear();
    fEdeps.clear();
  };
private:
  std::vector<G4double> fXs;
  std::vector<G4double> fYs;
  std::vector<G4double> fZs;
  std::vector<G4double> fEdeps;
  G4int fHCID;
};

#endif
