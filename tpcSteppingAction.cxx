// Origin: C.Perez V.Canoa (2016)

#include "tpcSteppingAction.h"
#include "G4Step.hh"
#include "G4Track.hh"

tpcSteppingAction::tpcSteppingAction() {}

tpcSteppingAction::~tpcSteppingAction() {}

void tpcSteppingAction::UserSteppingAction(const G4Step *theStep) {
  G4Track *theTrack = theStep->GetTrack();
  if(theTrack->GetTrackStatus()!=fAlive) {return;}
  // condition to kill
  //theTrack->SetTrackStatus(fStopAndKill);
}
