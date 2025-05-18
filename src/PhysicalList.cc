/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:29:57
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:35:45
 * @FilePath: /g4_proton/src/PhysicalList.cc
 * @Description: 物理列表类，注册了如下物理过程：
    * 1. 电磁过程
    * 2. 光学过程
    * 3. 衰变过程
    * 4. 放射性衰变
    * 5. 高能物理过程
    * 6. 中子物理过程
    * 7. 其他物理过程
    在主函数中可以选择其他的物理过程
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
