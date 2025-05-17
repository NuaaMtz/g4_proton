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
