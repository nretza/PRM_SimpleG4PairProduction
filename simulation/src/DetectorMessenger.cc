#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include <G4UIdirectory.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
    : G4UImessenger(),
      fDetector(Det),
      fTestemDir(nullptr),
      fDetDir(nullptr),
      fPressureCmd(nullptr),
      fMaterialCmd(nullptr),
      fMaterialStateCmd(nullptr)
{
    fTestemDir = new G4UIdirectory("/simulation/");
    fTestemDir->SetGuidance("Simulation control.");

    fDetDir = new G4UIdirectory("/simulation/TPC/");
    fDetDir->SetGuidance("TPC Detector construction commands");

    fPressureCmd = new G4UIcmdWithADouble("/simulation/TPC/setPressure",this);
    fPressureCmd->SetGuidance("Select pressure of the gas.");
    fPressureCmd->SetParameterName("pressure",false);
    fPressureCmd->SetRange("pressure>0.");
    fPressureCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fPressureCmd->SetToBeBroadcasted(false);

    fPositionZCmd = new G4UIcmdWithADoubleAndUnit("/simulation/TPC/setPositionZ",this);
    fPositionZCmd->SetGuidance("Set position z (mm)");
    fPositionZCmd->SetParameterName("positionZ",false);
    fPositionZCmd->SetUnitCategory("Length");
    fPositionZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fPositionZCmd->SetToBeBroadcasted(false);

    fLengthCmd = new G4UIcmdWithADoubleAndUnit("/simulation/TPC/setLength",this);
    fLengthCmd->SetGuidance("Set length (mm)");
    fLengthCmd->SetParameterName("length",false);
    fLengthCmd->SetUnitCategory("Length");
    fLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fLengthCmd->SetToBeBroadcasted(false);

    fMaterialCmd = new G4UIcmdWithAString("/simulation/TPC/setMaterial",this);
    fMaterialCmd->SetGuidance("Set the material inside the TPC");
    fMaterialCmd->SetParameterName("material",false);
    fMaterialCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fMaterialCmd->SetToBeBroadcasted(false);

    fMaterialStateCmd = new G4UIcmdWithAString("/simulation/TPC/setMaterialState",this);
    fMaterialStateCmd->SetGuidance("Set state of material");
    fMaterialStateCmd->SetParameterName("materialState",false);
    fMaterialStateCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fMaterialStateCmd->SetToBeBroadcasted(false);
    fMaterialStateCmd->SetCandidates("solid gas");
}

DetectorMessenger::~DetectorMessenger()
{
    delete fPressureCmd;
    delete fLengthCmd;
    delete fMaterialCmd;
    delete fMaterialStateCmd;

    delete fDetDir;
    delete fTestemDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
    // Set TPC Pressure
    if( command == fPressureCmd )
    {
        fDetector->setPressure(fPressureCmd->GetNewDoubleValue(newValue));
    }

    // Set Position Z
    if( command == fPositionZCmd )
    {
        fDetector->setPositionZ(fPositionZCmd->GetNewDoubleValue(newValue));
    }

    // Set Position Z
    if( command == fLengthCmd )
    {
        fDetector->setLength(fPositionZCmd->GetNewDoubleValue(newValue));
    }

    // Set TPC material
    if( command == fMaterialCmd )
    {
        fDetector->switchMaterial(newValue);
    }

    // Set TPC material state
    if( command == fMaterialStateCmd )
    {
        fDetector->switchMaterialState(newValue);
    }

}
