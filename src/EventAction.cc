

#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction(RunAction *runAction)
    : G4UserEventAction(), fRunAction(runAction), fCounts(0) {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *) { 
  fCounts = 0; // Reset the counts at the beginning of each event
 }

void EventAction::EndOfEventAction(const G4Event *) {
  // accumulate statistics in run action
  fRunAction->AddCounts(fCounts);
}
