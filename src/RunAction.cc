/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:35:59
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 01:40:19
 * @FilePath: /g4_proton/src/RunAction.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
// #include "B1Run.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction(),
  fCounts(0)
{ 

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fCounts);


}



RunAction::~RunAction()
{}


void RunAction::BeginOfRunAction(const G4Run*)
{ 
 // 初始化
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

}

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4double Counts  = fCounts.GetValue();
  G4cout
   << " 总计数: " << Counts << G4endl;
}



void RunAction::AddCounts (G4int counts)
{
  fCounts+= counts;
 
}


