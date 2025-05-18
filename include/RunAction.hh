/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:36:03
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:41:59
 * @FilePath: /g4_proton/include/B1RunAction.hh
 * @Description: 行为类
 */


#include <G4Types.hh>

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "iostream"



class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddCounts (G4int counts); 
    G4double primaryParticleEnergy,
             primaryParticleBeam;

  private:
    G4Accumulable<G4int> fCounts;
   
};

#endif

