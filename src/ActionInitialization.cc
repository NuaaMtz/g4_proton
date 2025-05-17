

#include "ActionInitialization.hh"

// #include "EventAction.hh"
// #include "SteppingAction.hh"



ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}


ActionInitialization::~ActionInitialization()
{}



void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
}


void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);

  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
  
   EventAction* eventAction = new EventAction(runAction);
  SetUserAction(eventAction);
  
  // SetUserAction(new B1SteppingAction(eventAction));

  // step->event->runaction(the end)
}  


