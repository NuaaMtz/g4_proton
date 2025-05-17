/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:29:57
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 01:32:15
 * @FilePath: /g4_proton/src/PhysicalList.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "PhysicalList.hh"

PhysicalList::PhysicalList()
    : G4VModularPhysicsList()
{
    SetVerboseLevel(0);

    // Register electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics_option4());
    
    RegisterPhysics(new G4OpticalPhysics());

    // Register decay physics
    RegisterPhysics(new G4DecayPhysics());

    RegisterPhysics(new G4RadioactiveDecayPhysics());
    
    // high energy
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP());
}
PhysicalList::~PhysicalList()
{

    // physical list defined by geant4 would be delete by runaction
}
