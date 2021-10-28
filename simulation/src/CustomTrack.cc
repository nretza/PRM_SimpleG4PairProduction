#include "CustomTrack.hh"
#include "G4Track.hh"

#include <G4VProcess.hh>
#include <cmath>

CustomTrack::CustomTrack() {}

CustomTrack::~CustomTrack() {}

CustomTrack::CustomTrack(G4Track* track)
{
    this->setTrack(track);
}
CustomTrack::CustomTrack(const G4Track* track)
{
    this->setTrack(track);
}


void CustomTrack::setTrack(G4Track* track)
{
    this->_TrackID = track->GetTrackID();
    this->_ParentID = track->GetParentID();
    this->_ParticleID = track->GetParticleDefinition()->GetPDGEncoding();

    this->_PositionX = track->GetPosition().getX();
    this->_PositionY = track->GetPosition().getY();
    this->_PositionZ = track->GetPosition().getZ();

    this->_MomentumX = track->GetMomentum().getX();
    this->_MomentumY = track->GetMomentum().getY();
    this->_MomentumZ = track->GetMomentum().getZ();

    this->_TotalEnergy = track->GetTotalEnergy();
    this->_KineticEnergy = track->GetKineticEnergy();
    this->_VertexKineticEnergy = track->GetVertexKineticEnergy();

    if( track->GetCreatorProcess() == nullptr )
    {
        this->_trackCreatorProcess = "undefined";
    }
    else
    {
        this->_trackCreatorProcess = track->GetCreatorProcess()->GetProcessName();
    }
}


void CustomTrack::setTrack(const G4Track* track)
{
    this->_TrackID = track->GetTrackID();
    this->_ParentID = track->GetParentID();
    this->_ParticleID = track->GetParticleDefinition()->GetPDGEncoding();

    this->_PositionX = track->GetPosition().getX();
    this->_PositionY = track->GetPosition().getY();
    this->_PositionZ = track->GetPosition().getZ();

    this->_MomentumX = track->GetMomentum().getX();
    this->_MomentumY = track->GetMomentum().getY();
    this->_MomentumZ = track->GetMomentum().getZ();

    this->_TotalEnergy = track->GetTotalEnergy();
    this->_KineticEnergy = track->GetKineticEnergy();
    this->_VertexKineticEnergy = track->GetVertexKineticEnergy();

    if( track->GetCreatorProcess() == nullptr )
    {
        this->_trackCreatorProcess = "undefined";
    }
    else
    {
        this->_trackCreatorProcess = track->GetCreatorProcess()->GetProcessName();
    }
}


void CustomTrack::setTrackID(int fTrackID)
{
    this->_TrackID = fTrackID;
}
void CustomTrack::setParentID(int fParentID)
{
    this->_ParentID = fParentID;
}
void CustomTrack::setParticleID(int fParticleID)
{
    this->_ParticleID = fParticleID;
}
void CustomTrack::setPositionX(double fPosX)
{
    this->_PositionX = fPosX;
}
void CustomTrack::setPositionY(double fPosY)
{
    this->_PositionY = fPosY;
}
void CustomTrack::setPositionZ(double fPosZ)
{
    this->_PositionZ = fPosZ;
}
void CustomTrack::setMomentumX(double fMomX)
{
    this->_MomentumX = fMomX;
}
void CustomTrack::setMomentumY(double fMomY)
{
    this->_MomentumY = fMomY;
}
void CustomTrack::setMomentumZ(double fMomZ)
{
    this->_MomentumZ = fMomZ;
}
void CustomTrack::setTotalEnergy(double fTotE)
{
    this->_TotalEnergy = fTotE;
}
void CustomTrack::setKineticEnergy(double fKinE)
{
    this->_KineticEnergy = fKinE;
}
void CustomTrack::setVertexKineticEnergy(double fVKinE)
{
    this->_VertexKineticEnergy = fVKinE;
}
void CustomTrack::setTrackCreatorProcess(std::string CreatorProcess)
{
    this->_trackCreatorProcess = CreatorProcess;
}


int CustomTrack::getTrackID()
{
    return this->_TrackID;
}
int CustomTrack::getParentID()
{
    return this->_ParentID;
}
int CustomTrack::getParticleID()
{
    return this->_ParticleID;
}


double CustomTrack::getPositionX()
{
    return this->_PositionX;
}
double CustomTrack::getPositionY()
{
    return this->_PositionY;
}
double CustomTrack::getPositionZ()
{
    return this->_PositionZ;
}


double CustomTrack::getMomentumX()
{
    return this->_MomentumX;
}
double CustomTrack::getMomentumY()
{
    return this->_MomentumY;
}
double CustomTrack::getMomentumZ()
{
    return this->_MomentumZ;
}
double CustomTrack::getMomentumMag()
{
    double mag_2 = pow(this->_MomentumX, 2) + pow(this->_MomentumY, 2) + pow(this->_MomentumZ, 2);
    return sqrt(mag_2);
}


double CustomTrack::getTotalEnergy()
{
    return this->_TotalEnergy;
}
double CustomTrack::getKineticEnergy()
{
    return this->_KineticEnergy;
}
double CustomTrack::getVertexKineticEnergy()
{
    return this->_VertexKineticEnergy;
}
std::string CustomTrack::getTrackCreatorProcess()
{
    return this->_trackCreatorProcess;
}
