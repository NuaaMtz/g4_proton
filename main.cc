/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-17 16:43:30
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:38:23
 * @FilePath: /g4_proton/main.cc
 * @Description: 主函数，runmanager管理模拟，UI管理可视化
 */
//#include "ActionInitilization.hh"
#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "include/PhysicalList.hh"
#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "iostream"
int main(int argc, char **argv) {
  std::cout << "Hello World!" << std::endl;

  G4RunManager *runManager = new G4MTRunManager();

  G4int verboseLevel = 0;
  G4RunManager::GetRunManager()->SetVerboseLevel(verboseLevel);

  // 探测器追踪
  DetectorConstruction *detectorConstrution = new DetectorConstruction();
  runManager->SetUserInitialization(detectorConstrution );
  //runManager->SetUserInitialization(new PhysicalList());// 不启用自定义物理列表
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(physicsList);
  runManager->SetUserInitialization(new ActionInitialization());

  // 粒子可视化
  G4UIExecutive *ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }
  G4VisExecutive *visManager = new G4VisExecutive(); //* initialize vis manager
  visManager->Initialize();
  G4UImanager *uiManager =
      G4UImanager::GetUIpointer(); // get ui manager from vis manager
  if (ui) {
    uiManager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
  } else {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uiManager->ApplyCommand(command + fileName);
  }
  // manage memory

  return 0;
}