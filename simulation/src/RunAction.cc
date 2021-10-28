#include "DataManager.hh"
#include "DataVisualisation.hh"
#include "DataAnalyser.hh"

#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include <time.h>

RunAction::RunAction() : G4UserRunAction() {}

void RunAction::BeginOfRunAction( const G4Run*)
{
    DataManager::getInstance()->prepare();
    DataAnalyser::getInstance()->prepare();

    startClock = clock();
}

void RunAction::EndOfRunAction( const G4Run*)
{

    endClock = clock();
    double elapsed = double(endClock - startClock)/ (double) CLOCKS_PER_SEC;

    std::cout << "Time in seconds for this run: " << elapsed << std::endl;
}
