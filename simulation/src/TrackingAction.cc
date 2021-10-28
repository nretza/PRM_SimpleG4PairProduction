#include "TrackingAction.hh"
#include "DataManager.hh"
#include "G4Track.hh"
#include "CustomTrajectory.hh"
#include "G4TrackingManager.hh"

TrackingAction::TrackingAction() :G4UserTrackingAction() {}

TrackingAction::~TrackingAction() {}

void TrackingAction::PreUserTrackingAction(const G4Track* track)
{
    DataManager::getInstance()->addTrack( track );
}

void TrackingAction::PostUserTrackingAction(const G4Track*)
{

}

