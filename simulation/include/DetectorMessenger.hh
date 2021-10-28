#ifndef DetectorMessenger_h
#define DetectorMessenger_h

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class DetectorMessenger: public G4UImessenger
{
public:

    DetectorMessenger(DetectorConstruction*);
    ~DetectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:

    DetectorConstruction* fDetector;

    G4UIdirectory*             fTestemDir;
    G4UIdirectory*             fDetDir;
    G4UIcmdWithADouble*        fPressureCmd;
    G4UIcmdWithADoubleAndUnit* fPositionZCmd;
    G4UIcmdWithADoubleAndUnit* fLengthCmd;
    G4UIcmdWithAString*        fMaterialCmd;
    G4UIcmdWithAString*        fMaterialStateCmd;
};

#endif

