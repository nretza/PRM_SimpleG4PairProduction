#ifndef DataMessenger_h
#define DataMessenger_h

#include "globals.hh"
#include "G4UImessenger.hh"

class DataManager;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class DataMessenger: public G4UImessenger
{
public:

    DataMessenger();
    ~DataMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:

    DataManager*               fData;
    G4UIdirectory*             fAnalysisDir;
    G4UIcmdWithABool*          fGammaPPCmd;
    G4UIcmdWithABool*          fMuPPCmd;

    G4UIcmdWithABool*          fPositronCmd;
    G4UIcmdWithABool*          fElectronCmd;
    G4UIcmdWithABool*          fPhotonCmd;

};

#endif
