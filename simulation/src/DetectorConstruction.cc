#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include <G4ThreeVector.hh>
#include <G4RunManager.hh>
#include <G4NistManager.hh>
#include <G4Tubs.hh>
#include <G4Box.hh>
#include <G4PVPlacement.hh>
#include <G4ProductionCuts.hh>
#include <G4VisAttributes.hh>
#include <G4GeometryManager.hh>
#include <G4PhysicalVolumeStore.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4SolidStore.hh>

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(),
      _radius(0),
      _length(0),
      _pressure(1),
      _worldSizeX(0),
      _worldSizeY(0),
      _worldSizeZ(0),
      _targetSizeX(0),
      _targetSizeY(0),
      _targetSizeZ(0),
      _materialName("G4_H"),
      _materialState("gas"),
      _detectorMessenger(nullptr)
{
    // Default parameter values
    this->_positionZ    = 0.0 * CLHEP::mm;
    this->_length       = 4*400 * CLHEP::mm;
    this->_pressure     = 20 * CLHEP::STP_Pressure;
    this->_materialName = "G4_H";
    this->_materialState = "gas";

    // WORLD VOLUME
    this->_worldSizeX  = 100 * CLHEP::meter;
    this->_worldSizeY  = this->_worldSizeX;
    this->_worldSizeZ  = this->_worldSizeX;

    this->_detectorMessenger = new DetectorMessenger(this);
}

void DetectorConstruction::_setMaterial()
{
    if(this->_materialState == "gas")
    {
        this->_material = G4NistManager::Instance()->ConstructNewGasMaterial( "TPC_Gas", this->_materialName, CLHEP::STP_Temperature, this->_pressure);
        this->_material->GetIonisation()->SetMeanEnergyPerIonPair( this->_material->GetIonisation()->GetMeanExcitationEnergy());
    }
    else if (this->_materialState == "solid")
    {
        this->_material = G4NistManager::Instance()->FindOrBuildMaterial(this->_materialName);
    }

    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
}

void DetectorConstruction::switchMaterial(std::string materialName)
{
    this->_materialName = materialName;
}

void DetectorConstruction::switchMaterialState(std::string materialState)
{
    std::string states = "gas solid liquid";
    if (states.find(materialState) != std::string::npos)
    {
        this->_materialState = materialState;
    }
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    return this->_constructVolumes();
}

G4VPhysicalVolume* DetectorConstruction::_constructVolumes()
{
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    this->_world = new G4Box("World", this->_worldSizeX/2, this->_worldSizeY/2, this->_worldSizeZ/2);

    this->_worldLogicalVolume = new G4LogicalVolume(this->_world, G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic"), "World");

    this->_worldLogicalVolume->SetVisAttributes( G4VisAttributes::GetInvisible() );
    this->_worldPlacement = new G4PVPlacement(nullptr, G4ThreeVector(), "World", this->_worldLogicalVolume, nullptr, false, 0);

    G4LogicalVolume* tpcVolumeLogical = this->_constructTPC();


    return this->_worldPlacement;
}

void DetectorConstruction::setPressure(double value)
{
    this->_pressure = value * CLHEP::STP_Pressure;
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
}
void DetectorConstruction::setPositionZ( double positionZ )
{
    this->_positionZ = positionZ * CLHEP::mm;
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
}
void DetectorConstruction::setLength( double length )
{
    this->_length = length * CLHEP::mm;
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
}

DetectorConstruction::~DetectorConstruction()
{
    delete this->_detectorMessenger;
}

G4LogicalVolume* DetectorConstruction::_constructTPC()
{
    // Constructs TPC-Material
    this->_setMaterial();

    // Construct TPC volume
    G4Tubs* tpcVolume = new G4Tubs("TPCVolume", 0, 300 * CLHEP::mm, 0.5 * this->_length, 0, CLHEP::twopi);
    G4LogicalVolume* tpcVolumeLogical = new G4LogicalVolume(tpcVolume, this->_material, "TPCVolume");

    G4Colour transparentBlue( 0, 0, 255, 0.5 );

    tpcVolumeLogical->SetVisAttributes( G4VisAttributes( transparentBlue ) );
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,this->_positionZ), "TPCVolume", tpcVolumeLogical, this->_worldPlacement, false, 0);

    return tpcVolumeLogical;
}
