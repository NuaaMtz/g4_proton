/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:22:12
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:33:41
 * @FilePath: /g4_proton/include/B1PrimaryGeneratorAction.hh
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "G4GeneralParticleSource.hh"
#include "G4GenericMessenger.hh"
class PrimaryGeneratorMessenger;
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();
  virtual void GeneratePrimaries(G4Event *);

  G4GeneralParticleSource *GetGPS() const { return fParticleGun; }

  G4int n_particle;
  double energy;

private:
  G4GeneralParticleSource *fParticleGun; // G4 particle gun
};

#endif
