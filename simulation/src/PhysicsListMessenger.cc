#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"

PhysicsListMessenger::PhysicsListMessenger( PhysicsList *phys ) : G4UImessenger(), fPhysicsList( phys )
{
    fPhysDir = new G4UIdirectory( "/simulation/physics/" );
    fPhysDir->SetGuidance( "physics list commands" );

    fListCmd = new G4UIcmdWithAString( "/simulation/physics/addPhysics", this );
    fListCmd->SetGuidance( "Add modula physics list." );
    fListCmd->SetParameterName( "PList", false );
    fListCmd->AvailableForStates( G4State_PreInit );
    fListCmd->SetToBeBroadcasted(false);

    fVerboseCmd = new G4UIcmdWithAnInteger( "/simulation/physics/verbose", this );
    fVerboseCmd->SetGuidance( "Sets verbosity for Physicslists." );
    fVerboseCmd->SetParameterName( "PVerbose", false );
    fVerboseCmd->AvailableForStates( G4State_PreInit );
    fVerboseCmd->SetToBeBroadcasted(false);
}

PhysicsListMessenger::~PhysicsListMessenger()
{
    delete fListCmd;
    delete fPhysDir;
    delete fVerboseCmd;
}

void PhysicsListMessenger::SetNewValue( G4UIcommand *command, G4String newValue )
{
    if ( command == fListCmd )
    {
        fPhysicsList->AddPhysicsList( newValue );
    }

    if ( command == fVerboseCmd )
    {
        fPhysicsList->SetVerboseLevel( fVerboseCmd->GetNewIntValue(newValue) );
    }
}
