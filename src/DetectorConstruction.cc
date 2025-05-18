/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:19:08
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:20:36
 * @FilePath: /g4_proton/src/DetectorConstruction.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "DetectorConstruction.hh"
DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume *DetectorConstruction::Construct() {
  // 定义世界
  double xWorld = 10 * cm;
  double yWorld = 10 * cm;
  double zWorld = 10 * cm;
  // 定义材料
  G4Material *worldMat;
  G4double low_pressure_density = 1.e-25 * g / cm3;  // density
  G4double low_pressure_temperature = 2.73 * kelvin; // low temperature
  G4double low_pressure_pressure = 3.e-18 * pascal;  // low push
  G4Material *vacuum = new G4Material(
      "Vacuum", 1, 1.008 * g / mole, low_pressure_density, kStateGas,
      low_pressure_temperature, low_pressure_pressure);
  worldMat = vacuum;
  G4Box *solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
  G4LogicalVolume *logicalWorld =
      new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
  G4VPhysicalVolume *phyWorld = new G4PVPlacement(
      0, G4ThreeVector(0, 0, 0), logicalWorld, "phyWorld", 0, false, 0, true);

  // 定义球形重氧水
  G4double r = 1 * cm;
  G4NistManager *nist = G4NistManager::Instance();
  
  // 手动定义重水 D2O
  G4Element* elD = nist->FindOrBuildElement("D");
  if (!elD) {
    elD = new G4Element("Deuterium", "D", 1, 2.014 * g/mole);
  }
  G4Element* elO = nist->FindOrBuildElement("O");
  if (!elO) {
    G4Exception("DetectorConstruction::Construct", "MyCode0003", FatalException, "Element O (Oxygen) not found!");
  }
  G4Material * water = new G4Material("D2O", 1.1056 * g/cm3, 2);
  water->AddElement(elD, 2);
  water->AddElement(elO, 1);
  
  G4Orb *solidWater = new G4Orb("solidWater", r);
  G4LogicalVolume *logicalWater =
      new G4LogicalVolume(solidWater, water, "logicalWater");
  G4VPhysicalVolume *phyWater =
      new G4PVPlacement(0, G4ThreeVector(2 * cm, 0, 0), logicalWater, "phyWater",
                        logicalWorld, false, 0, true);

  return phyWorld;
}