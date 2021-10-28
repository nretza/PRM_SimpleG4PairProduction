#ifndef CUSTOMSTEP_H
#define CUSTOMSTEP_H

class G4Step;
class CustomStep
{

public:

    CustomStep();
    CustomStep(G4Step* Step);
    CustomStep(const G4Step* Step);
    ~CustomStep();

    void setStep(G4Step* Step);
    void setStep(const G4Step* Step);

    void setTrackID(int fStepID);
    void setParticleID(int fParticleID);

    void setPositionX(double fPosX);
    void setPositionY(double fPosY);
    void setPositionZ(double fPosZ);
    void setPositionR(double fPosR);
    void setTime(double fTime);

    void setTotalEnergy(double fTotE);
    void setKineticEnergy(double fKinE);
    void setEnergyDeposition(double fEnergyDeposit);

    int getTrackID();
    int getParticleID();

    double getPositionX();
    double getPositionY();
    double getPositionZ();
    double getPositionR();
    double getTime();

    double getTotalEnergy();
    double getKineticEnergy();
    double getEnergyDeposition();

private:

    int _TrackID;
    int _ParticleID;

    double _PositionX;
    double _PositionY;
    double _PositionZ;
    double _PositionR;
    double _Time;

    double _TotalEnergy;
    double _KineticEnergy;
    double _EnergyDeposition;
};
#endif
