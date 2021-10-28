#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "DataManager.hh"
#include "PhysicsList.hh"

#include <G4RunManager.hh>
#include <G4PhysListFactory.hh>
#include <FTFP_BERT.hh>
#include <G4UImanager.hh>
#include <Randomize.hh>
#include <G4UIExecutive.hh>
#include <G4VisExecutive.hh>

#include <time.h>


int main(int argc, char** argv)
{
    // detect interactive mode (if no arguments) and define UI session
    G4UIExecutive* ui = nullptr;
    std::string macroFileName  = "/nfs/freenas/tuph/e18/project/prm/nretza/G4_macros/init_vis.mac";
    std::string outputFileName = "/nfs/freenas/tuph/e18/project/prm/nretza/G4_runs/run.root";

    bool writeData = true;

    if (argc == 1)
    {
        ui = new G4UIExecutive(argc,argv);
    }

    else if( argc == 2)
    {
        macroFileName = "/nfs/freenas/tuph/e18/project/prm/nretza/G4_macros/run.mac";
        outputFileName = argv[1];

        if (strcmp(argv[1],"--default") == 0)//Default run
        {
            macroFileName = "/nfs/freenas/tuph/e18/project/prm/nretza/G4_macros/run.mac";
            outputFileName ="/nfs/freenas/tuph/e18/project/prm/nretza/G4_runs/run.root";
        }
    }

    else if( argc == 3)
    {
        // Example ./Simulation output.root run.mac
        outputFileName = argv[1];
        macroFileName  = argv[2];
    }

    else if( argc == 3)
    {
        // Example ./Simulation output.root run.mac
        outputFileName = argv[1];
        macroFileName  = argv[2];
    }

    else if( argc == 4)
    {
        // Example ./Simulation output.root run.mac
        outputFileName = argv[1];
        macroFileName  = argv[2];

    if (strcmp(argv[3],"--NoData") == 0)
        {
            writeData = false;
        }
    }





    // set up the Random engine
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
    CLHEP::HepRandom::setTheSeed(time(NULL));

    // Construct the default run manager
    G4RunManager* runManager = new G4RunManager();

    // set mandatory initialization classes
    DetectorConstruction* detectorConstruction = new DetectorConstruction();
    PhysicsList*          physicsList          = new PhysicsList();

    //G4PhysListFactory*    physListFactory      = new G4PhysListFactory();
    //G4VUserPhysicsList*   physicsList          = physListFactory->GetReferencePhysList("FTFP_BERT");

    runManager->SetUserInitialization(detectorConstruction);
    runManager->SetUserInitialization(physicsList);

    //set user action classes
    PrimaryGeneratorAction* generatorAction = new PrimaryGeneratorAction();
    RunAction*              runAction       = new RunAction();
    TrackingAction*         trackingAction  = new TrackingAction();
    SteppingAction*         steppingAction  = new SteppingAction();
    EventAction*            eventAction     = new EventAction();

    runManager->SetUserAction(eventAction);
    runManager->SetUserAction(generatorAction);
    runManager->SetUserAction(runAction);
    runManager->SetUserAction(trackingAction);
    runManager->SetUserAction(steppingAction);

    // initialize visualization
    G4VisManager* visManager = nullptr;

    // get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Data manager
    DataManager::getInstance()->setOutputFileName(outputFileName);
    DataManager::getInstance()->setWriteData(writeData);

    G4String command = "/control/execute ";

    if (ui)
    {
        // interactive mode
        visManager = new G4VisExecutive;
        visManager->Initialize();
        UImanager->ApplyCommand(command+macroFileName);
        ui->SessionStart();
        delete ui;
    }
    else
    {
        // batch mode
        UImanager->ApplyCommand(command+macroFileName);
    }

    DataManager::getInstance()->finish();

    // job termination
    delete visManager;
    delete runManager;

    return 0;
}
