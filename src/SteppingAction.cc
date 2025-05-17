/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-04-01 10:16:24
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 01:53:31
 * @FilePath: /B1/src/B1SteppingAction.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */


#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

    

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{

}
    

SteppingAction::~SteppingAction()
{}

    

void SteppingAction::UserSteppingAction(const G4Step* step)
{

      
      if (step->GetTrack()->GetDefinition()->GetParticleName() == "F18") {
        fEventAction->AddCounts(1);  
      }
  
}

    

