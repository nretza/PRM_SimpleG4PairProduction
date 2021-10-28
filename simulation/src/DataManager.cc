#include "DataVisualisation.hh"
#include "DataManager.hh"
#include "DataMessenger.hh"
#include "DataAnalyser.hh"
#include "PPVertex.hh"
#include "CustomTrack.hh"
#include "CustomStep.hh"

#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>

#include <cmath>

#include <G4Step.hh>
#include <G4Track.hh>
#include <G4VProcess.hh>
#include <G4ProcessType.hh>


DataManager* DataManager::_instance = nullptr;

DataManager * DataManager::getInstance()
{
    if( _instance == nullptr )
    {
        _instance = new DataManager();
    }
    return _instance;
}

DataManager::DataManager() : _dataMessenger()
{
    this->_dataMessenger = new DataMessenger();
}

DataManager::~DataManager()
{
    delete this->_dataMessenger;
}

void DataManager::setOutputFileName( const std::string& filename )
{
    this->_outputFileName = filename;
    this->_outputFile     = new TFile( this->_outputFileName.c_str(), "RECREATE" );
    std::cout << "Output file set to \"" << filename << "\"" << std::endl;
}


void DataManager::createTrees()
{
    // Steps
    this->_treeSteps = new TTree("Steps", "Steps");
    this->_treeSteps->Branch("eventNumber"        , &this->_stepEventNumber         );
    this->_treeSteps->Branch("energyDeposition"   , &this->_stepEnergyDeposition    );
    this->_treeSteps->Branch("positionX"          , &this->_stepPositionX           );
    this->_treeSteps->Branch("positionY"          , &this->_stepPositionY           );
    this->_treeSteps->Branch("positionZ"          , &this->_stepPositionZ           );
    this->_treeSteps->Branch("positionR"          , &this->_stepPositionR           );
    this->_treeSteps->Branch("totalEnergy"        , &this->_stepTotalEnergy         );
    this->_treeSteps->Branch("kineticEnergy"      , &this->_stepKineticEnergy       );
    this->_treeSteps->Branch("pid"                , &this->_stepPid                 );
    this->_treeSteps->Branch("time"               , &this->_stepTime                );
    this->_treeSteps->Branch("trackId"            , &this->_stepTrackId             );

    // Tracks
    this->_treeTracks = new TTree("Tracks", "Tracks");
    this->_treeTracks->Branch( "positionX"           , &this->_trackPositionX            );
    this->_treeTracks->Branch( "positionY"           , &this->_trackPositionY            );
    this->_treeTracks->Branch( "positionZ"           , &this->_trackPositionZ            );
    this->_treeTracks->Branch( "momentumX"           , &this->_trackMomentumX            );
    this->_treeTracks->Branch( "momentumY"           , &this->_trackMomentumY            );
    this->_treeTracks->Branch( "momentumZ"           , &this->_trackMomentumZ            );
    this->_treeTracks->Branch( "trackId"             , &this->_trackTrackId              );
    this->_treeTracks->Branch( "parentId"            , &this->_trackParentId             );
    this->_treeTracks->Branch( "pid"                 , &this->_trackPid                  );
    this->_treeTracks->Branch( "creatorProcess"      , &this->_trackCreatorProcess       );
    this->_treeTracks->Branch( "totalEnergy"         , &this->_trackTotalEnergy          );
    this->_treeTracks->Branch( "kineticEnergy"       , &this->_trackKineticEnergy        );
}

/*bevore event*/
void DataManager::clear()
{
    // Step Entries
    this->_stepList.clear();
    this->_stepPositionX->clear();
    this->_stepPositionY->clear();
    this->_stepPositionZ->clear();
    this->_stepPositionR->clear();
    this->_stepTotalEnergy->clear();
    this->_stepTime->clear();
    this->_stepKineticEnergy->clear();
    this->_stepPid->clear();
    this->_stepEnergyDeposition->clear();
    this->_stepEventNumber->clear();
    this->_stepTrackId->clear();

    // Track Entries
    this->_trackList.clear();
    this->_trackPositionX->clear();
    this->_trackPositionY->clear();
    this->_trackPositionZ->clear();
    this->_trackMomentumX->clear();
    this->_trackMomentumY->clear();
    this->_trackMomentumZ->clear();
    this->_trackTrackId->clear();
    this->_trackParentId->clear();
    this->_trackPid->clear();
    this->_trackCreatorProcess->clear();
    this->_trackTotalEnergy->clear();
    this->_trackKineticEnergy->clear();
}

/*at beginning*/
void DataManager::prepare()
{
    if( not this->_prepared )
    {
        this->_outputFile->cd();
        this->createTrees();
        this->createHistograms();
    }
    this->clear();
    this->_prepared = true;
}

/*at end of event*/
void DataManager::save()
{
    // Fill trees and ajust counters
    if (this->_writeData)
    {
        this->_treeSteps->Fill();
        this->_treeTracks->Fill();
    }
    this->_evNr++;

}

/*at end of everything*/
void DataManager::finish()
{
    // Save Tree
    this->_outputFile->cd();
    this->_treeSteps->Write(0, TObject::kOverwrite); //(overrides Autosaves)
    this->_treeTracks->Write(0, TObject::kOverwrite); //(overrides Autosaves)

    // Save Plots
    DataVisualisation::getInstance()->saveData();

    // Close File
    this->_outputFile->Close();
}


void DataManager::addStep(const G4Step* step)
{
    // Basics
    this->_stepEventNumber     ->push_back( this->_evNr);
    this->_stepTrackId         ->push_back( step->GetTrack()->GetTrackID());
    this->_stepPositionX       ->push_back( step->GetPostStepPoint()->GetPosition().getX()      / CLHEP::mm  );
    this->_stepPositionY       ->push_back( step->GetPostStepPoint()->GetPosition().getY()      / CLHEP::mm  );
    this->_stepPositionZ       ->push_back( step->GetPostStepPoint()->GetPosition().getZ()      / CLHEP::mm  );
    this->_stepPositionR       ->push_back( step->GetPostStepPoint()->GetPosition().getR()      / CLHEP::mm  );
    this->_stepTime            ->push_back( step->GetPostStepPoint()->GetGlobalTime()           / CLHEP::ns  );
    this->_stepTotalEnergy     ->push_back( step->GetPostStepPoint()->GetTotalEnergy()          / CLHEP::GeV );
    this->_stepKineticEnergy   ->push_back( step->GetPostStepPoint()->GetKineticEnergy()        / CLHEP::GeV );
    this->_stepEnergyDeposition->push_back( step->GetTotalEnergyDeposit()                       / CLHEP::GeV );
    this->_stepPid             ->push_back( step->GetTrack()->GetDefinition()->GetPDGEncoding()              );

    //Steplist
    this->_stepList.push_back(CustomStep(step));

    // Histograms
    this->_histogramStepXY->Fill( this->_stepPositionX->back() , this->_stepPositionY->back() );

    if ( step->GetTrack()->GetCreatorProcess() != nullptr )
    {
        const G4String& processname = step->GetTrack()->GetCreatorProcess()->GetProcessName();

        if (processname == "conv")
        {
            if (step->GetTrack()->GetParticleDefinition()->GetPDGEncoding() == 11)
            {
                this->_histogramGammaElectronStepXY->Fill( this->_stepPositionX->back() , this->_stepPositionY->back() );
            }
            if (step->GetTrack()->GetParticleDefinition()->GetPDGEncoding() == -11)
            {
                this->_histogramGammaPositronStepXY->Fill( this->_stepPositionX->back() , this->_stepPositionY->back() );
            }
        }

        if (processname == "muPairProd")
        {
            if (step->GetTrack()->GetParticleDefinition()->GetPDGEncoding() == 11)
            {
                this->_histogramMuElectronStepXY->Fill( this->_stepPositionX->back() , this->_stepPositionY->back() );
            }
            if (step->GetTrack()->GetParticleDefinition()->GetPDGEncoding() == -11)
            {
                this->_histogramMuPositronStepXY->Fill( this->_stepPositionX->back() , this->_stepPositionY->back() );
            }
        }
    }
}



void DataManager::addTrack( const G4Track* track)
{
    //Basics
    this->_trackPositionX           ->push_back( track->GetPosition().getX()        / CLHEP::mm   );
    this->_trackPositionY           ->push_back( track->GetPosition().getY()        / CLHEP::mm   );
    this->_trackPositionZ           ->push_back( track->GetPosition().getZ()        / CLHEP::mm   );
    this->_trackMomentumX           ->push_back( track->GetMomentum().getX()        / CLHEP::GeV  );
    this->_trackMomentumY           ->push_back( track->GetMomentum().getY()        / CLHEP::GeV  );
    this->_trackMomentumZ           ->push_back( track->GetMomentum().getZ()        / CLHEP::GeV  );
    this->_trackTotalEnergy         ->push_back( track->GetTotalEnergy()            / CLHEP::GeV  );
    this->_trackKineticEnergy       ->push_back( track->GetKineticEnergy()          / CLHEP::GeV  );
    this->_trackTrackId             ->push_back( track->GetTrackID()                              );
    this->_trackParentId            ->push_back( track->GetParentID()                             );
    this->_trackPid                 ->push_back( track->GetParticleDefinition()->GetPDGEncoding() );
    if( track->GetCreatorProcess() == nullptr )
    {
        // not sure what happens here
        this->_trackCreatorProcess->push_back("undefined");
    }
    else
    {
        this->_trackCreatorProcess->push_back(track->GetCreatorProcess()->GetProcessName() );
    }

    //Tracklist
    this->_trackList.push_back(CustomTrack(track));


}


void DataManager::createHistograms()
{
    this->_histogramStepXY              = (TH2D*)DataVisualisation::getInstance()->createHistogram( new TH2D("histogramStepXY", "", 300, -300, 300, 300, -300, 300));
    this->_histogramGammaElectronStepXY = (TH2D*)DataVisualisation::getInstance()->createHistogram( new TH2D("histogramGammaElectronStepXY", "", 300, -300, 300, 300, -300, 300));
    this->_histogramGammaPositronStepXY = (TH2D*)DataVisualisation::getInstance()->createHistogram( new TH2D("histogramGammaPositronStepXY", "", 300, -300, 300, 300, -300, 300));
    this->_histogramMuElectronStepXY    = (TH2D*)DataVisualisation::getInstance()->createHistogram( new TH2D("histogramMuElectronStepXY", "", 300, -300, 300, 300, -300, 300));
    this->_histogramMuPositronStepXY    = (TH2D*)DataVisualisation::getInstance()->createHistogram( new TH2D("histogramMuPositronStepXY", "", 300, -300, 300, 300, -300, 300));
}

std::vector<CustomStep> DataManager::getStepList()
{
    return this->_stepList;
}

std::vector<CustomTrack> DataManager::getTrackList()
{
    return this->_trackList;
}
