// Origin: C.Perez V.Canoa (2016)

#ifndef tpcActionInitialization_h
#define tpcActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class tpcActionInitialization : public G4VUserActionInitialization {
 public:
  tpcActionInitialization();
  virtual ~tpcActionInitialization();
  virtual void BuildForMaster() const;
  virtual void Build() const;
};

#endif
