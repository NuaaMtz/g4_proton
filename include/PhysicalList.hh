/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:29:52
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:35:23
 * @FilePath: /g4_proton/include/PhysicalList.hh
 * @Description:物理列表类
 */


#ifndef PHYSICALLIST_HH
#define PHYSICALLIST_HH
#include "G4VModularPhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4HadronPhysicsINCLXX.hh"

#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"

class PhysicalList : public G4VModularPhysicsList
{
public:
    PhysicalList();
    virtual ~PhysicalList();
};

#endif
