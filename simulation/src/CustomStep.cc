#include "CustomStep.hh"
#include "G4Step.hh"

#include <G4VProcess.hh>

CustomStep::CustomStep() {}

CustomStep::~CustomStep() {}

CustomStep::CustomStep(G4Step* step)
{
    this->setStep(step);
}
CustomStep::CustomStep(const G4Step* step)
{
    this->setStep(step);
}

void CustomStep::setStep(G4Step* step)
{
    this->_TrackID = step->GetTrack()->GetTrackID();
    this->_ParticleID = step->GetTrack()->GetDefinition()->GetPDGEncoding();

    this->_PositionX = step->GetPostStepPoint()->GetPosition().getX();
    this->_PositionY = step->GetPostStepPoint()->GetPosition().getY();
    this->_PositionZ = step->GetPostStepPoint()->GetPosition().getZ();
    this->_PositionR = step->GetPostStepPoint()->GetPosition().getR();
    this->_Time      = step->GetPostStepPoint()->GetGlobalTime();

    this->_TotalEnergy      = step->GetPostStepPoint()->GetTotalEnergy();
    this->_KineticEnergy    = step->GetPostStepPoint()->GetKineticEnergy();
    this->_EnergyDeposition = step->GetTotalEnergyDeposit();
}


void CustomStep::setStep(const G4Step* step)
{
    this->_TrackID = step->GetTrack()->GetTrackID();
    this->_ParticleID = step->GetTrack()->GetDefinition()->GetPDGEncoding();

    this->_PositionX = step->GetPostStepPoint()->GetPosition().getX();
    this->_PositionY = step->GetPostStepPoint()->GetPosition().getY();
    this->_PositionZ = step->GetPostStepPoint()->GetPosition().getZ();
    this->_PositionR = step->GetPostStepPoint()->GetPosition().getR();
    this->_Time      = step->GetPostStepPoint()->GetGlobalTime();

    this->_TotalEnergy      = step->GetPostStepPoint()->GetTotalEnergy();
    this->_KineticEnergy    = step->GetPostStepPoint()->GetKineticEnergy();
    this->_EnergyDeposition = step->GetTotalEnergyDeposit();
}


void CustomStep::setTrackID(int fTrackID)
{
    this->_TrackID = fTrackID;
}
void CustomStep::setParticleID(int fParticleID)
{
    this->_ParticleID = fParticleID;
}
void CustomStep::setPositionX(double fPosX)
{
    this->_PositionX = fPosX;
}
void CustomStep::setPositionY(double fPosY)
{
    this->_PositionY = fPosY;
}
void CustomStep::setPositionZ(double fPosZ)
{
    this->_PositionZ = fPosZ;
}
void CustomStep::setPositionR(double fPosR)
{
    this->_PositionR = fPosR;
}
void CustomStep::setTime(double fTime)
{
    this->_Time = fTime;
}
void CustomStep::setTotalEnergy(double fTotE)
{
    this->_TotalEnergy = fTotE;
}
void CustomStep::setKineticEnergy(double fKinE)
{
    this->_KineticEnergy = fKinE;
}
void CustomStep::setEnergyDeposition(double fEnergyDeposit)
{
    this->_EnergyDeposition = fEnergyDeposit;
}


int CustomStep::getTrackID()
{
    return this->_TrackID;
}
int CustomStep::getParticleID()
{
    return this->_ParticleID;
}
double CustomStep::getPositionX()
{
    return this->_PositionX;
}
double CustomStep::getPositionY()
{
    return this->_PositionY;
}
double CustomStep::getPositionZ()
{
    return this->_PositionZ;
}
double CustomStep::getPositionR()
{
    return this->_PositionR;
}
double CustomStep::getTime()
{
    return this->_Time;
}
double CustomStep::getTotalEnergy()
{
    return this->_TotalEnergy;
}
double CustomStep::getKineticEnergy()
{
    return this->_KineticEnergy;
}
double CustomStep::getEnergyDeposition()
{
    return this->_EnergyDeposition;
}
