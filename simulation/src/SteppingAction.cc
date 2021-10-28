#include <DataManager.hh>

#include "SteppingAction.hh"
#include "G4Step.hh"


SteppingAction::SteppingAction() : G4UserSteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction( const G4Step *step )
{
    G4double energyDeposition = step->GetTotalEnergyDeposit();
    if ( energyDeposition <= 0. )
    {
        return;
    }
    DataManager::getInstance()->addStep( step );
}


