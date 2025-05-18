/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:34:53
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:40:38
 * @FilePath: /g4_proton/src/ActionInitialization.cc
 * @Description: 按照执行顺序管理行为
 */


#include "ActionInitialization.hh"

// #include "EventAction.hh"
// #include "SteppingAction.hh"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
  RunAction *runAction = new RunAction;
  SetUserAction(runAction);
}

void ActionInitialization::Build() const {
  SetUserAction(new PrimaryGeneratorAction);

  RunAction *runAction = new RunAction;
  SetUserAction(runAction);

  EventAction *eventAction = new EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new SteppingAction(eventAction));

  // step->event->runaction(the end)
}
