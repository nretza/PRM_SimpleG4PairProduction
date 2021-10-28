#include "EventAction.hh"
#include "DataManager.hh"
#include "DataAnalyser.hh"

EventAction::EventAction() : G4UserEventAction() {}

void EventAction::BeginOfEventAction(const G4Event*)
{
    DataManager::getInstance()->clear();
    DataAnalyser::getInstance()->clear();
}

void EventAction::EndOfEventAction(const G4Event*)
{
    DataManager::getInstance()->save();
    DataAnalyser::getInstance()->analyseEvent();
}
