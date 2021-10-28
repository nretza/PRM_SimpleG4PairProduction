#include "DataMessenger.hh"
#include "DataManager.hh"
#include "DataAnalyser.hh"

#include <G4UIdirectory.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>

DataMessenger::DataMessenger()
    : G4UImessenger(),
      fAnalysisDir(nullptr),
      fGammaPPCmd(nullptr),
      fMuPPCmd(nullptr),
      fPositronCmd(nullptr),
      fElectronCmd(nullptr),
      fPhotonCmd(nullptr)

{
    fAnalysisDir = new G4UIdirectory("/analysis/");
    fAnalysisDir->SetGuidance("Analysis control.");

    fGammaPPCmd = new G4UIcmdWithABool("/analysis/GammaPairProduction",this);
    fGammaPPCmd->SetGuidance("analyses gamma pair production");
    fGammaPPCmd->SetParameterName("Analyse",false);
    fGammaPPCmd->SetDefaultValue(false);
    fGammaPPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fGammaPPCmd->SetToBeBroadcasted(false);

    fMuPPCmd = new G4UIcmdWithABool("/analysis/MuPairProduction",this);
    fMuPPCmd->SetGuidance("analyses Mu pair production");
    fMuPPCmd->SetParameterName("Analyse",false);
    fMuPPCmd->SetDefaultValue(false);
    fMuPPCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fMuPPCmd->SetToBeBroadcasted(false);

    fPositronCmd = new G4UIcmdWithABool("/analysis/Positron",this);
    fPositronCmd->SetGuidance("analyse appearing positrons");
    fPositronCmd->SetParameterName("Analyse",false);
    fPositronCmd->SetDefaultValue(false);
    fPositronCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fPositronCmd->SetToBeBroadcasted(false);

    fElectronCmd = new G4UIcmdWithABool("/analysis/Electron",this);
    fElectronCmd->SetGuidance("analyse appearing Electrons");
    fElectronCmd->SetParameterName("Analyse",false);
    fElectronCmd->SetDefaultValue(false);
    fElectronCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fElectronCmd->SetToBeBroadcasted(false);

    fPhotonCmd = new G4UIcmdWithABool("/analysis/Photon",this);
    fPhotonCmd->SetGuidance("analyse appearing Photons");
    fPhotonCmd->SetParameterName("Analyse",false);
    fPhotonCmd->SetDefaultValue(false);
    fPhotonCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    fPhotonCmd->SetToBeBroadcasted(false);

}

DataMessenger::~DataMessenger()
{
    delete fAnalysisDir;
    delete fGammaPPCmd;
    delete fMuPPCmd;
    delete fPositronCmd;
    delete fElectronCmd;
    delete fPhotonCmd;
}

void DataMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
    if( command == fGammaPPCmd )
    {
        DataAnalyser::getInstance()->setAnalyseGammaPP(fGammaPPCmd->GetNewBoolValue(newValue));
    }
    if( command == fMuPPCmd )
    {
        DataAnalyser::getInstance()->setAnalyseMuPP(fMuPPCmd->GetNewBoolValue(newValue));
    }

    if( command == fPositronCmd )
    {
        DataAnalyser::getInstance()->setAnalysePositron(fPositronCmd->GetNewBoolValue(newValue));
    }

    if( command == fPhotonCmd )
    {
        DataAnalyser::getInstance()->setAnalysePhoton(fPhotonCmd->GetNewBoolValue(newValue));
    }

    if( command == fElectronCmd )
    {
        DataAnalyser::getInstance()->setAnalyseElectron(fElectronCmd->GetNewBoolValue(newValue));
    }

}
