/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:35:59
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:41:49
 * @FilePath: /g4_proton/src/RunAction.cc
 * @Description: 运行类，负责统计事件数和产额
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
#include <G4ios.hh>

RunAction::RunAction() : G4UserRunAction(), fCounts(0) {
  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fCounts);
  fCounts = 0;
  // 定义root文件的数据结构
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  analysisManager->CreateH1("Counts", "Counts of F18", 100, 0., 1000);
  analysisManager->CreateH1("Energy", "Energy of gun", 10, 0., 10);
  analysisManager->CreateH1("Beam", "Beam of gun", 1000, 0., 10000);

  analysisManager->CreateNtuple("tree", "产额tree");
  analysisManager->CreateNtupleIColumn("Counts");
  analysisManager->CreateNtupleDColumn("Energy");
  analysisManager->CreateNtupleIColumn("Beam");
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

  // 获取PrimaryGeneratorAction
  auto pga = static_cast<const PrimaryGeneratorAction *>(
      G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  if (pga) {
    G4GeneralParticleSource *gps = pga->GetGPS();
    if (gps) {
      primaryParticleEnergy =
          gps->GetParticleEnergy() / CLHEP::MeV; // 单位MeV
                                                 // 记录总束流强度
      primaryParticleBeam =
          gps->GetNumberOfParticles() * run->GetNumberOfEvent();
    }
  }
  auto analysisManager = G4Root::G4AnalysisManager::Instance();
  // 填充Ntuple（每个线程都要填充）
  if (!G4Threading::IsMasterThread()) {

    analysisManager->FillH1(0, Counts);
    analysisManager->FillH1(1, primaryParticleEnergy);
    analysisManager->FillH1(2, primaryParticleBeam);
    G4cout << "Counts: " << Counts << G4endl;
    G4cout << "Energy: " << primaryParticleEnergy << G4endl;
    G4cout << "Beam: " << primaryParticleBeam << G4endl;

    analysisManager->FillNtupleIColumn(0, Counts);
    analysisManager->FillNtupleDColumn(1, primaryParticleEnergy);
    analysisManager->FillNtupleIColumn(2, primaryParticleBeam);
    analysisManager->AddNtupleRow();
  }

  // 主线程只负责合并和写文件

  analysisManager->Write();
  analysisManager->CloseFile();
}

void RunAction::AddCounts(G4int counts) { fCounts += counts; }
