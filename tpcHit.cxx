// Origin: C.Perez V.Canoa (2016)

#include <iomanip>
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "tpcHit.h"

G4ThreadLocal G4Allocator<tpcHit>* TrackerHitAllocator=0;

tpcHit::tpcHit() :
  G4VHit(),
  fEdep(0),
  fX(0),
  fY(0),
  fZ(0) {
}

tpcHit::~tpcHit() {
}

tpcHit::tpcHit(const tpcHit& right)
  : G4VHit() {
  fEdep = right.fEdep;
  fX = right.fEdep;
  fY = right.fEdep;
  fZ = right.fEdep;
}

const tpcHit& tpcHit::operator=(const tpcHit& right) {
  fEdep = right.fEdep;
  fX = right.fEdep;
  fY = right.fEdep;
  fZ = right.fEdep;
  return *this;
}

G4int tpcHit::operator==(const tpcHit& right) const {
  return ( this == &right ) ? 1 : 0;
}

void tpcHit::SetXYZ(G4ThreeVector val) {
  fX = val.getX();
  fY = val.getY();
  fZ = val.getZ();
}

void tpcHit::Draw() {
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager) {
    G4Circle circle(G4ThreeVector(fX,fY,fZ));
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void tpcHit::Print() {
  G4cout
    << "Edep: "
    << std::setw(7) << G4BestUnit(fEdep,"Energy")
    << " Position: "
    << std::setw(7) << G4BestUnit(fX,"Length") << " "
    << std::setw(7) << G4BestUnit(fY,"Length") << " "
    << std::setw(7) << G4BestUnit(fZ,"Length")
    << G4endl;
}
