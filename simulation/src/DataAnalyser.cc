#include "DataVisualisation.hh"
#include "DataManager.hh"
#include "DataAnalyser.hh"
#include "DataMessenger.hh"

#include "PPVertex.hh"
#include "PPVertexForMuPP.hh"
#include "CustomTrack.hh"
#include "CustomStep.hh"

#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TVector3.h>

#include <cmath>

#include <G4VProcess.hh>
#include <G4ProcessType.hh>

DataAnalyser* DataAnalyser::_instance = nullptr;

DataAnalyser* DataAnalyser::getInstance()
{
    if( _instance == nullptr )
    {
        _instance = new DataAnalyser();
    }
    return _instance;
}

DataAnalyser::DataAnalyser() {}

DataAnalyser::~DataAnalyser() {}



void DataAnalyser::prepare()
{
    if( not this->_prepared )
    {
        this->createHistograms();
    }
    this->clear();
    this->_prepared = true;

}

void DataAnalyser::clear()
{
    this-> _trackList.clear();
    this-> _stepList.clear();

    this-> _electronTrackList.clear();
    this-> _positronTrackList.clear();
    this-> _photonTrackList.clear();

    this-> _gammaVertexTrackList.clear();
    this-> _gammaPPVertexTrackList.clear();

    this-> _muVertexTrackList.clear();
    this-> _muPPVertexTrackList.clear();
}


void DataAnalyser::createHistograms()
{
    if (this->_analyseGammaPP)
    {
        this->_histogramGammaPPPositronE            = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramGammaPPPositronE", "", 300, 0, 30));
        this->_histogramGammaPPElectronE            = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramGammaPPElectronE", "", 300, 0, 30));
        this->_histogramGammaPPEnergyDist           = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramGammaPPEnergyDist", "", 150, 0, 1));
        this->_histogramGammaPPAngle                = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramGammaPPAngle", "", 200, 0, 1));
        this->_histogramGammaPPE                    = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramGammaPPE", "", 200, 0, 500));
        this->_histogramGammaPPAngletoE             = (TH2D*)DataVisualisation::getInstance()->createHistogram(new TH2D("histogramGammaPPAngletoE", "", 200, 0, 1, 200, 0, 500));
        this->_histogramGammaPPInvariantMass        = (TH1D*)DataVisualisation::getInstance()->createHistogram(new TH1D("histogramGammaPPInvariantMass", "", 200, 0, 10));
        this->_histogramGammaPPAngletoInvariantMass = (TH2D*)DataVisualisation::getInstance()->createHistogram(new TH2D("histogramGammaPPAngletoInvariantMass", "", 200, 0 , 1, 200, 0, 20));
        this->_histogramGammaPPMomentumMags         = (TH2D*)DataVisualisation::getInstance()->createHistogram(new TH2D("histogramGammaPPMomentumMags", "", 200, 0 , 20, 200, 0, 20));

        this->_histogramGammaPPPositronE            -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramGammaPPElectronE            -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramGammaPPEnergyDist           -> GetXaxis() -> SetTitle("x");
        this->_histogramGammaPPAngle                -> GetXaxis() -> SetTitle("angle [rad]");
        this->_histogramGammaPPE                    -> GetXaxis() -> SetTitle("E [MeV]"    );
        this->_histogramGammaPPAngletoE             -> GetXaxis() -> SetTitle("angle [rad]");
        this->_histogramGammaPPAngletoE             -> GetYaxis() -> SetTitle("E [MeV]"    );
        this->_histogramGammaPPInvariantMass        -> GetXaxis() -> SetTitle("E [MeV]"    );
        this->_histogramGammaPPAngletoInvariantMass -> GetXaxis() -> SetTitle("ange [rad]" );
        this->_histogramGammaPPAngletoInvariantMass -> GetYaxis() -> SetTitle("E [MeV]"    );
        this->_histogramGammaPPMomentumMags         -> GetXaxis() -> SetTitle("Electron [MeV]");
        this->_histogramGammaPPMomentumMags         -> GetYaxis() -> SetTitle("Positron [MeV]");

    }

    if (this->_analyseMuPP)
    {
        this->_histogramMuPPPositronE            = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramMuPPPositronE", "", 300, 0, 30));
        this->_histogramMuPPElectronE            = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramMuPPElectronE", "", 300, 0, 30));
        this->_histogramMuPPEnergyDist           = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramMuPPEnergyDist", "", 150, 0, 1));
        this->_histogramMuPPAngle                = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramMuPPAngle", "", 200, 0, 0.01));
        this->_histogramMuPPE                    = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramMuPPE", "", 200, 0, 1000));
        this->_histogramMuPPAngletoE             = (TH2D*)DataVisualisation::getInstance()->createHistogram(new TH2D("histogramMuPPAngletoE", "", 200, 0, 0.01, 300, 0, 1000));
        this->_histogramMuPPInvariantMass        = (TH1D*)DataVisualisation::getInstance()->createHistogram(new TH1D("histogramMuPPInvariantMass", "", 200, 0, 6));
        this->_histogramMuPPAngletoInvariantMass = (TH2D*)DataVisualisation::getInstance()->createHistogram(new TH2D("histogramMuPPAngletoInvariantMass", "", 200, 0 , 0.01, 200, 0, 20));
        this->_histogramMuPPMomentumMags         = (TH2D*)DataVisualisation::getInstance()->createHistogram(new TH2D("histogramMuPPMomentumMags", "", 200, 0 , 20, 200, 0, 20));

        this->_histogramMuPPPositronE            -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramMuPPElectronE            -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramMuPPEnergyDist           -> GetXaxis() -> SetTitle("x");
        this->_histogramMuPPAngle                -> GetXaxis() -> SetTitle("angle [rad]");
        this->_histogramMuPPE                    -> GetXaxis() -> SetTitle("E [MeV]"    );
        this->_histogramMuPPAngletoE             -> GetXaxis() -> SetTitle("angle [rad]");
        this->_histogramMuPPAngletoE             -> GetYaxis() -> SetTitle("E [MeV]"    );
        this->_histogramMuPPInvariantMass        -> GetXaxis() -> SetTitle("E [MeV]"    );
        this->_histogramMuPPAngletoInvariantMass -> GetXaxis() -> SetTitle("ange [rad]" );
        this->_histogramMuPPAngletoInvariantMass -> GetYaxis() -> SetTitle("E [MeV]"    );
        this->_histogramMuPPMomentumMags         -> GetXaxis() -> SetTitle("Electron [MeV]");
        this->_histogramMuPPMomentumMags         -> GetYaxis() -> SetTitle("Positron [MeV]");
    }

    if (this->_analysePositron)
    {
        this->_histogramPositronE               = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramPositronE", "", 200, 0, 20));
        this->_histogramPositronEZoom           = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramPositronEzoom", "", 200, 0, 2));
        this->_histogramPositronCreatorProcess  = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D());

        this->_histogramPositronE -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramPositronEZoom -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramPositronCreatorProcess  -> SetName("histogramPositronCreatorProcess");
    }

    if (this->_analysePhoton)
    {
        this->_histogramPhotonE               = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramPhotonE", "", 200, 0, 20));
        this->_histogramPhotonEZoom           = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramPhotonEzoom", "", 200, 0, 2));
        this->_histogramPhotonCreatorProcess  = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D());

        this->_histogramPhotonE -> GetXaxis()   -> SetTitle("E [MeV]");
        this->_histogramPhotonEZoom -> GetXaxis()   -> SetTitle("E [MeV]");
        this->_histogramPhotonCreatorProcess    -> SetName("histogramPhotonCreatorProcess");
    }

    if (this->_analyseElectron)
    {
        this->_histogramElectronE               = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramElectronE", "", 200, 0, 20));
        this->_histogramElectronEZoom           = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D("histogramElectronEzoom", "", 200, 0, 2));
        this->_histogramElectronCreatorProcess  = (TH1D*)DataVisualisation::getInstance()->createHistogram( new TH1D());

        this->_histogramElectronE -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramElectronEZoom -> GetXaxis() -> SetTitle("E [MeV]");
        this->_histogramElectronCreatorProcess  -> SetName("histogramElectronCreatorProcess");

    }
}

void DataAnalyser::analyseEvent()
{
    this->clear();
    this->fillParticleTrackLists();

    if (this->_analysePhoton)
    {
        for (auto& t : this->_photonTrackList)
        {
            this->_histogramPhotonE->Fill(t.getKineticEnergy() / CLHEP::MeV);
            this->_histogramPhotonEZoom->Fill(t.getKineticEnergy() / CLHEP::MeV);
            this->_histogramPhotonCreatorProcess -> Fill( &t.getTrackCreatorProcess()[0], 1);
        }
    }

    if (this->_analyseElectron)
    {
        for (auto& t : this->_electronTrackList)
        {
            this->_histogramElectronE -> Fill(t.getKineticEnergy() / CLHEP::MeV);
            this->_histogramElectronEZoom -> Fill(t.getKineticEnergy() / CLHEP::MeV);
            this->_histogramElectronCreatorProcess -> Fill( &t.getTrackCreatorProcess()[0], 1);
        }
    }

    if (this->_analysePositron)
    {
        for (auto& t : this->_positronTrackList)
        {
            this->_histogramPositronE->Fill(t.getKineticEnergy() / CLHEP::MeV);
            this->_histogramPositronEZoom->Fill(t.getKineticEnergy() / CLHEP::MeV);
            this->_histogramPositronCreatorProcess -> Fill( &t.getTrackCreatorProcess()[0], 1);
        }
    }

    if (this->_analyseGammaPP)
    {
        this->fillGammaPPVertexTrackList();

        //analysing magic
        for (auto& v : this->_gammaPPVertexTrackList)
        {
            double angle    = v.getAngle();
            double E_gamma  = v.getPhoton()->getTotalEnergy();
            double E_plus   = v.getPositron()->getTotalEnergy();
            double E_minus  = v.getElectron()->getTotalEnergy();
            double sqrt_s   = v.getInvariantMass();

            double Mag_e = v.getElectron()->getMomentumMag();
            double Mag_p = v.getPositron()->getMomentumMag();

            this->_histogramGammaPPElectronE            -> Fill(E_minus / CLHEP::MeV);
            this->_histogramGammaPPPositronE            -> Fill(E_plus / CLHEP::MeV);
            this->_histogramGammaPPEnergyDist           -> Fill(E_plus/(E_plus + E_minus));
            this->_histogramGammaPPInvariantMass        -> Fill(sqrt_s/ CLHEP::MeV);
            this->_histogramGammaPPAngle                -> Fill(angle);
            this->_histogramGammaPPE                    -> Fill(E_gamma / CLHEP::MeV);
            this->_histogramGammaPPAngletoE             -> Fill(angle, E_gamma / CLHEP::MeV);
            this->_histogramGammaPPAngletoInvariantMass -> Fill(angle, sqrt_s / CLHEP::MeV);
            this->_histogramGammaPPMomentumMags         -> Fill(Mag_e / CLHEP::MeV, Mag_p / CLHEP::MeV);

        }
    }

    if (this->_analyseMuPP)
    {
        this->fillMuPPVertexTrackList();

        //analysing magic
        for (auto& v : this->_muPPVertexTrackList)
        {
            double angle    = v.getAngle();
            double E_plus   = v.getPositron()->getTotalEnergy();
            double E_minus  = v.getElectron()->getTotalEnergy();
            double E        = v.getElectron()->getTotalEnergy() + v.getPositron()->getTotalEnergy();
            double sqrt_s   = v.getInvariantMass();

            double Mag_e = v.getElectron()->getMomentumMag();
            double Mag_p = v.getPositron()->getMomentumMag();

            this->_histogramMuPPElectronE            -> Fill(E_minus / CLHEP::MeV);
            this->_histogramMuPPPositronE            -> Fill(E_plus / CLHEP::MeV);
            this->_histogramMuPPEnergyDist           -> Fill(E_plus/(E_plus + E_minus));
            this->_histogramMuPPInvariantMass        -> Fill(sqrt_s / CLHEP::MeV);
            this->_histogramMuPPAngle                -> Fill(angle);
            this->_histogramMuPPE                    -> Fill(E / CLHEP::MeV);
            this->_histogramMuPPAngletoE             -> Fill(angle, E / CLHEP::MeV);
            this->_histogramMuPPAngletoInvariantMass -> Fill(angle, sqrt_s / CLHEP::MeV);
            this->_histogramMuPPMomentumMags         -> Fill(Mag_e / CLHEP::MeV, Mag_p / CLHEP::MeV);

        }
    }
}

void DataAnalyser::fillParticleTrackLists()
{
    this->_trackList = DataManager::getInstance()->getTrackList();

    for (auto& t : this->_trackList)
    {
        switch (t.getParticleID())
        {
        case 11:
            this->_electronTrackList.push_back(t);
            break;
        case -11:
            this->_positronTrackList.push_back(t);
            break;
        case 22:
            this->_photonTrackList.push_back(t);
            break;
        }
    }
}

void DataAnalyser::fillGammaPPVertexTrackList()
{
    //fill photons
    for (auto& t : this->_photonTrackList)
    {
        this->_gammaVertexTrackList.push_back(PPVertex(&t));
    }

    //fill electrons
    for (auto& t : this->_electronTrackList)
    {
        for (auto& v : this->_gammaVertexTrackList)
        {
            v.addParticle(&t);
        }
    }

    //fill positrons
    for (auto& t : this->_positronTrackList)
    {
        for (auto& v : this->_gammaVertexTrackList)
        {
            v.addParticle(&t);
        }
    }

    //create list with complete Vertices
    for (auto& v : this->_gammaVertexTrackList)
    {
        if (v.isComplete())
        {
            this->_gammaPPVertexTrackList.push_back(v);
        }
    }
}

void DataAnalyser::fillMuPPVertexTrackList()
{
    //fill electrons
    for (auto& t : this->_electronTrackList)
    {
        if (t.getTrackCreatorProcess() == "muPairProd") //saves some memory, is checked later in vertex anyways
        {
            this->_muVertexTrackList.push_back(PPVertexForMuPP(&t));
        }
    }

    //fill positrons
    for (auto& t : this->_positronTrackList)
    {
        for (auto& v : this->_muVertexTrackList)
        {
            if (t.getTrackCreatorProcess() == "muPairProd") //saves some memory, is checked later in vertex anyways
            {
                v.addParticle(&t);
            }

        }
    }

    //create list with complete Vertices
    for (auto& v : this->_muVertexTrackList)
    {
        if (v.isComplete())
        {
            this->_muPPVertexTrackList.push_back(v);
        }
    }
}
