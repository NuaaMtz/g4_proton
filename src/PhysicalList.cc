

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
