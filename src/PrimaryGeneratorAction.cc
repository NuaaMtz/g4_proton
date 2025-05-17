/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:22:56
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 02:45:34
 * @FilePath: /g4_proton/src/PrimaryGeneratorAction.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "PrimaryGeneratorAction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0) {
  G4int n_particle = 10000;
  fParticleGun = new G4ParticleGun(n_particle);

  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "proton";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
  // 设置发射位置为原点
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
  // 设置动量方向为x轴正方向
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
  // 设置粒子能量
  fParticleGun->SetParticleEnergy(6. * MeV);

  // 生成主事件
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
