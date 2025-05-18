/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-04-01 10:16:24
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:50:09
 * @FilePath: /B1/src/B1SteppingAction.cc
 * @Description: 步类，负责统计粒子产额
 */

#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"

#include "G4Event.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"

SteppingAction::SteppingAction(EventAction *eventAction)
    : G4UserSteppingAction(), fEventAction(eventAction) {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step *step) {
    // auto track = step->GetTrack();
    // if (track->GetDefinition()->GetParticleName() == "F18"
    //     && track->GetCurrentStepNumber() == 1
    //     && track->GetParentID() != 0) { // ID为0的是初级粒子
    //   fEventAction->AddCounts(1);
    // }
  
  // 第二种方法
  auto track = step->GetTrack();
  auto def = track->GetDefinition();
  if (def->GetAtomicNumber() == 9 && def->GetAtomicMass() == 18 &&
      track->GetCurrentStepNumber() == 1 && track->GetParentID() != 0) {
    fEventAction->AddCounts(1);
  }
}
