// Origin: C.Perez V.Canoa (2016)

#ifndef tpcHit_h
#define tpcHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class tpcHit : public G4VHit {
 public:
  tpcHit();
  tpcHit(const tpcHit&);
  virtual ~tpcHit();

  const tpcHit& operator=(const tpcHit&);
  G4int operator==(const tpcHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);
  virtual void Draw();
  virtual void Print();
  void SetEdep(G4double val) {fEdep=val;};
  void SetX(G4double val) {fX=val;}
  void SetY(G4double val) {fY=val;}
  void SetZ(G4double val) {fZ=val;}
  void SetXYZ(G4ThreeVector);
  G4double GetEdep() const {return fEdep;}
  G4double GetX() const {return fX;}
  G4double GetY() const {return fY;}
  G4double GetZ() const {return fZ;}

 private:
  G4double fEdep;
  G4double fX;
  G4double fY;
  G4double fZ;
};

typedef G4THitsCollection<tpcHit> TrackerHitsCollection;

extern G4ThreadLocal G4Allocator<tpcHit>* TrackerHitAllocator;

inline void* tpcHit::operator new(size_t) {
  if(!TrackerHitAllocator)
    TrackerHitAllocator = new G4Allocator<tpcHit>;
  return (void *) TrackerHitAllocator->MallocSingle();
}

inline void tpcHit::operator delete(void *hit) {
  TrackerHitAllocator->FreeSingle((tpcHit*) hit);
}

#endif
