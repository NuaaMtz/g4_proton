/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:35:59
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 02:58:53
 * @FilePath: /g4_proton/src/RunAction.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
// #include "B1Run.hh"
#include "g4root_defs.hh" // 添加头文件

#include "G4AccumulableManager.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "g4root.hh"
#include <G4Types.hh>

RunAction::RunAction() : G4UserRunAction(), fCounts(0) {
  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fCounts);

  // 定义root文件的数据结构
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  analysisManager->CreateH1("Counts","Counts of F18", 100, 0., 800);
  analysisManager->FinishNtuple();
}

RunAction::~RunAction() { delete G4Root::G4AnalysisManager::Instance(); }

void RunAction::BeginOfRunAction(const G4Run *run) {
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();

  // 打开root文件
  auto analysisManager = G4Root::G4AnalysisManager::Instance();
  G4int runNum = run->GetRunID();
  std::stringstream strRunID;
  strRunID << runNum;
  analysisManager->OpenFile("../rt/output_target" + strRunID.str() +
                            ".root"); // 每个beam都有自己的编号
}

void RunAction::EndOfRunAction(const G4Run *run) {
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0)
    return;

  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4int Counts = fCounts.GetValue();
  G4cout << " 总计数: " << Counts << G4endl;

  // 填充Ntuple（每个线程都要填充）
  auto analysisManager = G4Root::G4AnalysisManager::Instance();
  analysisManager->FillH1(0, Counts);


  if (IsMaster()) { // 只在主线程写文件
    analysisManager->Write();
    analysisManager->CloseFile();
  }
}

void RunAction::AddCounts(G4int counts) { fCounts += counts; }
