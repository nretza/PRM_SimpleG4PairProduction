#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <iostream>
#include <vector>

class TTree;
class TFile;
class TH2D;
class TH1D;
class G4Step;
class G4Track;
class CustomTrack;
class CustomStep;
class DataVisualisation;
class DataMessenger;
class DataManager
{
public:
    static DataManager* getInstance();
    ~DataManager();

    void setOutputFileName( const std::string& outputFileName );

    void setWriteData(bool writeData){this-> _writeData = writeData;}
    bool getWriteData(){return this->_writeData;}

    void createTrees();
    void clear();

    void prepare();
    void save();
    void finish();

    void addStep( const G4Step* step );
    void addTrack( const G4Track* track );


    std::string getOutputFileName() const
    {
        return this->_outputFileName;
    }

    TFile* getOutputFile()
    {
        return this->_outputFile;
    }

    unsigned int getTotalNumberOfEvents() const
    {
        return this->_evNr + 1;
    }

    std::vector<CustomStep> getStepList();
    std::vector<CustomTrack>  getTrackList();

private:
    static DataManager* _instance;
    DataManager();

    DataMessenger* _dataMessenger;

    bool _prepared = false;
    bool _writeData = true;

    void createHistograms();

    TTree*      _treeSteps;
    TTree*      _treeTracks;
    TFile*      _outputFile;
    std::string _outputFileName;

    // Step tree entries
    std::vector<CustomStep>  _stepList;
    std::vector<double>*     _stepEventNumber      = nullptr;
    std::vector<double>*     _stepTrackId          = nullptr;
    std::vector<double>*     _stepEnergyDeposition = nullptr;
    std::vector<double>*     _stepPositionX        = nullptr;
    std::vector<double>*     _stepPositionY        = nullptr;
    std::vector<double>*     _stepPositionZ        = nullptr;
    std::vector<double>*     _stepPositionR        = nullptr;
    std::vector<double>*     _stepTotalEnergy      = nullptr;
    std::vector<double>*     _stepKineticEnergy    = nullptr;
    std::vector<double>*     _stepPid              = nullptr;
    std::vector<double>*     _stepTime             = nullptr;

    // Tracks
    std::vector<CustomTrack>  _trackList;
    std::vector<double>*      _trackPositionX              = nullptr;
    std::vector<double>*      _trackPositionY              = nullptr;
    std::vector<double>*      _trackPositionZ              = nullptr;
    std::vector<double>*      _trackMomentumX              = nullptr;
    std::vector<double>*      _trackMomentumY              = nullptr;
    std::vector<double>*      _trackMomentumZ              = nullptr;
    std::vector<double>*      _trackTotalEnergy            = nullptr;
    std::vector<double>*      _trackKineticEnergy          = nullptr;
    std::vector<double>*      _trackTrackId                = nullptr;
    std::vector<double>*      _trackParentId               = nullptr;
    std::vector<double>*      _trackPid                    = nullptr;
    std::vector<std::string>* _trackCreatorProcess         = nullptr;

    unsigned int _evNr = 0;

    TH2D* _histogramStepXY;
    TH2D* _histogramGammaElectronStepXY;
    TH2D* _histogramGammaPositronStepXY;
    TH2D* _histogramMuElectronStepXY;
    TH2D* _histogramMuPositronStepXY;
};

#endif
