/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-18 01:19:08
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-18 14:53:11
 * @FilePath: /g4_proton/src/DetectorConstruction.cc
 * @Description:  在(2cm,0,0)处放置一个半径为1cm的球形富集氧-18的重水
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

  // 定义球形富集氧-18的重水 D2(18O)
  G4double r = 1 * cm;
  G4NistManager *nist = G4NistManager::Instance();

  // 氘
  G4Element* elD = nist->FindOrBuildElement("D");
  if (!elD) {
    elD = new G4Element("Deuterium", "D", 1, 2.014 * g/mole);
  }

  // 氧-18同位素
  G4Isotope* isoO18 = new G4Isotope("O18", 8, 18, 17.99916 * g/mole);
  // 富集氧-18元素（纯度100%，如需90%可自行调整）
  G4Element* elO18 = new G4Element("Oxygen18", "O18", 1);
  elO18->AddIsotope(isoO18, 100.*perCent);

  // 构建D2O（全部用O-18）
  G4Material* water = new G4Material("D2O18", 1.1056 * g/cm3, 2);
  water->AddElement(elD, 2);
  water->AddElement(elO18, 1);

  G4Orb *solidWater = new G4Orb("solidWater", r);
  G4LogicalVolume *logicalWater =
      new G4LogicalVolume(solidWater, water, "logicalWater");
  new G4PVPlacement(0, G4ThreeVector(2 * cm, 0, 0), logicalWater, "phyWater",
                        logicalWorld, false, 0, true);

  return phyWorld;
}

// 来自GPT

/*
靶材类型：使用 重水（D₂O） 作为靶材，其中需富集 氧-18（¹⁸O）。
重水中的氧-18在质子轰击下发生 (p,n)核反应（质子俘获，释放中子），生成氟-18。
富集度：天然水中氧-18含量极低（约0.2%），因此需使用 富集氧-18的重水（如纯度≥90%）
以提高产率。例如，1毫升富集氧-18的重水可生产超过370吉贝可的氟-18。

*/

/*
能量范围：质子能量需达到 3-16 MeV，通常选择 10-16 MeV 的质子束以实现高效反应。
例如，日本住友HM-10HC型回旋加速器使用10 MeV质子束轰击重水靶材。
束流强度：需稳定且高能的质子束流，通常通过医用回旋加速器产生。束流强度直接影响氟-18的产率
，例如每微安小时（μA·h）可产生约2.22 GBq的氟-18。
*/