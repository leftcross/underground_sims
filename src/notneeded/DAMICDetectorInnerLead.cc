#include "DAMICDetectorInnerLead.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MultiUnion.hh"
#include "G4Transform3D.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>


G4LogicalVolume* GetConstructionAncientLead1()
{
  G4double cylRin = 15.748*mm;
  G4double cylRout = 91.948*mm;
  G4double cylH = 25.4*mm;
  G4double angle0 = 0;
  G4double angle180 = M_PI;

  G4Tubs* cylLead = new G4Tubs("CylLead", cylRin, cylRout, cylH/2, angle0, angle180);

  G4Material* Lead = G4Material::GetMaterial("G4_Pb");
  G4LogicalVolume * ancientLead1 = new G4LogicalVolume(cylLead, Lead,"AncientLead1");

  return ancientLead1;


}


G4LogicalVolume* GetConstructionAncientLead2()
{
  G4double cylRin = 15.748*mm;
  G4double cylRout = 91.948*mm;
  G4double cylH = 25.4*mm;
  G4double angle0 = 0;
  G4double angle180 = M_PI;
  G4double rmBoxX = 6.223*mm;
  G4double rmBoxY = 31.75*mm;
  G4double rmBoxZ = 25.4*mm;

  G4Tubs* cylLead = new G4Tubs("CylLead", cylRin, cylRout, cylH/2, angle0, angle180);
  G4Box * rmBox = new G4Box ("rmBox", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix * rotBox = new G4RotationMatrix;
  rotBox->rotateZ(M_PI/4);
  G4double rmBoxVecX = cylRout * cos(M_PI/4);
  G4double rmBoxVecY = cylRout * sin(M_PI/4);
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxVecX, rmBoxVecY, 0);
  G4Transform3D rmBoxTr = G4Transform3D(*rotBox, rmBoxVec);

  G4SubtractionSolid* ancientLead2Final = new G4SubtractionSolid("AncientLead2Final", cylLead, rmBox, rmBoxTr);

  G4Material* Lead = G4Material::GetMaterial("G4_Pb");
  G4LogicalVolume * ancientLead2 = new G4LogicalVolume(ancientLead2Final, Lead,"AncientLead2");

  return ancientLead2;

}

G4LogicalVolume* GetConstructionBoxMountingPlate()
{
  G4double rmCylROut = 127/2*mm;
  //  G4double rmCylRIn = 28.575/2*mm;
  G4double rmCylH = 6.35*mm;
  G4double cylRIn = 28.575/2*mm;
  G4double cylROut = 185.166/2*mm;
  G4double cylH = 9.652*mm;
  G4double rmBoxX = 9.525*mm;
  G4double rmBoxY = 30.48*mm;
  G4double rmBoxZ = 9.652*mm;
  G4double angle0 = 0;
  G4double angle360 = 2*M_PI+1;

  G4Tubs* rmCyl = new G4Tubs("RmCyl", 0, rmCylROut, rmCylH, angle0, angle360);
  G4Tubs* cyl = new G4Tubs("Cyl", cylRIn, cylROut, cylH/2, angle0, angle360);
  G4Box* rmBox = new G4Box("RmBox", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix *rot0 = new G4RotationMatrix;
  G4double rmCylZ = cylH/2;
  G4double rmBoxXVec = cylROut;
  G4ThreeVector rmCylVec = G4ThreeVector(0,0,rmCylZ);
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxXVec,0,0);
  G4Transform3D rmCylTr = G4Transform3D(*rot0, rmCylVec);
  G4Transform3D rmBoxTr = G4Transform3D(*rot0, rmBoxVec);

  G4SubtractionSolid* boxMountPlate = new G4SubtractionSolid("BoxMountPlate", cyl, rmCyl, rmCylTr);
  G4SubtractionSolid* boxMountPlateFinal = new G4SubtractionSolid("BoxMountPlateFinal", boxMountPlate, rmBox, rmBoxTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * boxMountingPlate = new G4LogicalVolume(boxMountPlateFinal, Copper,"BoxMountingPlate");

  return boxMountingPlate;
}

G4LogicalVolume* GetConstructionGoodLead()
{
  G4double cylRIn = 31.75/2*mm;
  G4double cylROut = 184.15/2*mm;
  G4double cylH = 50.8*mm;
  G4double rmBoxX = 9.525*mm;
  G4double rmBoxY = 30.48*mm;
  G4double rmBoxZ = 50.8*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;

  G4Tubs * cylGood = new G4Tubs("CylGood", cylRIn, cylROut, cylH/2, angle0, angle360);
  G4Box* rmBoxGood = new G4Box("RmBoxGood", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix * rot0 = new G4RotationMatrix;
  G4double rmBoxXVec = -cylROut;
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxXVec, 0, 0);
  G4Transform3D rmBoxTr = G4Transform3D(*rot0, rmBoxVec);

  G4SubtractionSolid * goodLeadFinal = new G4SubtractionSolid("GoodLeadFinal", cylGood, rmBoxGood, rmBoxTr);

  G4Material* Lead = G4Material::GetMaterial("G4_Pb");
  G4LogicalVolume * goodLead = new G4LogicalVolume(goodLeadFinal, Lead,"GoodLead");

  return goodLead;
}

G4LogicalVolume* GetConstructionSpacerPlate()
{
  G4double cylRIn = 28.575/2*mm;
  G4double cylROut = 189.23/2*mm;
  G4double cylH = 3.048*mm;
  G4double rmBoxX = 9.525*mm;
  G4double rmBoxY = 30.48*mm;
  G4double rmBoxZ = 3.048*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;

  G4Tubs * cylGood = new G4Tubs("CylGood", cylRIn, cylROut, cylH/2, angle0, angle360);
  G4Box* rmBoxGood = new G4Box("RmBoxGood", rmBoxX, rmBoxY/2, rmBoxZ);

  G4RotationMatrix * rot0 = new G4RotationMatrix;
  G4double rmBoxXVec = -cylROut;
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxXVec, 0, 0);
  G4Transform3D rmBoxTr = G4Transform3D(*rot0, rmBoxVec);

  G4SubtractionSolid * spacerPlateFinal = new G4SubtractionSolid("SpacerPlateFinal", cylGood, rmBoxGood, rmBoxTr);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * spacerPlate = new G4LogicalVolume(spacerPlateFinal, Copper,"SpacerPlate");

  return spacerPlate;
}
