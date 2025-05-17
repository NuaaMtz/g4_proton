

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction(RunAction *runAction)
    : G4UserEventAction(), fRunAction(runAction), fCounts(0) {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *) {  }

void EventAction::EndOfEventAction(const G4Event *) {
  // accumulate statistics in run action
}
