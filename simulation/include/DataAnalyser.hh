#ifndef DATAANALYSER_H
#define DATAANALYSER_H

#include <iostream>
#include <vector>

class TH2D;
class TH1D;
class CustomTrack;
class CustomStep;
class DataVisualisation;
class DataMessenger;
class PPVertex;
class PPVertexForMuPP;
class DataMananger;
class DataAnalyser
{
public:
    static DataAnalyser* getInstance();
    ~DataAnalyser();

    void clear();
    void finish();
    void save();
    void prepare();

    void analyseEvent();

    //for DataMessanger
    void setAnalyseGammaPP(bool value)
    {
        this->_analyseGammaPP = value;
    }
    void setAnalyseMuPP(bool value)
    {
        this->_analyseMuPP = value;
    }
    void setAnalysePhoton(bool value)
    {
        this->_analysePhoton = value;
    }
    void setAnalysePositron(bool value)
    {
        this->_analysePositron = value;
    }
    void setAnalyseElectron(bool value)
    {
        this->_analyseElectron = value;
    }

private:

    static DataAnalyser* _instance;
    DataAnalyser();

    bool _prepared = false;

    void createHistograms();

    //for DataMessanger
    bool _analyseGammaPP  = false;
    bool _analyseMuPP     = false;
    bool _analysePhoton   = false;
    bool _analysePositron = false;
    bool _analyseElectron = false;

    std::vector<CustomTrack> _trackList;
    std::vector<CustomStep>  _stepList;

    std::vector<CustomTrack> _electronTrackList;
    std::vector<CustomTrack> _photonTrackList;
    std::vector<CustomTrack> _positronTrackList;

    std::vector<PPVertex>    _gammaVertexTrackList;
    std::vector<PPVertex>    _gammaPPVertexTrackList;

    std::vector<PPVertexForMuPP>    _muVertexTrackList;
    std::vector<PPVertexForMuPP>    _muPPVertexTrackList;

    void fillParticleTrackLists();
    void fillGammaPPVertexTrackList();
    void fillMuPPVertexTrackList();

    TH1D* _histogramGammaPPPositronE;
    TH1D* _histogramGammaPPElectronE;
    TH1D* _histogramGammaPPEnergyDist;
    TH1D* _histogramGammaPPInvariantMass;
    TH1D* _histogramGammaPPAngle;
    TH1D* _histogramGammaPPE;
    TH2D* _histogramGammaPPAngletoE;
    TH2D* _histogramGammaPPAngletoInvariantMass;
    TH2D* _histogramGammaPPMomentumMags;

    TH1D* _histogramMuPPPositronE;
    TH1D* _histogramMuPPElectronE;
    TH1D* _histogramMuPPEnergyDist;
    TH1D* _histogramMuPPInvariantMass;
    TH1D* _histogramMuPPAngle;
    TH1D* _histogramMuPPE;
    TH2D* _histogramMuPPAngletoE;
    TH2D* _histogramMuPPAngletoInvariantMass;
    TH2D* _histogramMuPPMomentumMags;

    TH1D* _histogramPositronE;
    TH1D* _histogramPositronEZoom;
    TH1D* _histogramPositronCreatorProcess;

    TH1D* _histogramElectronE;
    TH1D* _histogramElectronEZoom;
    TH1D* _histogramElectronCreatorProcess;

    TH1D* _histogramPhotonE;
    TH1D* _histogramPhotonEZoom;
    TH1D* _histogramPhotonCreatorProcess;
};

#endif
