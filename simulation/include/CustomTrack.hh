#ifndef CUSTOMTRACK_H
#define CUSTOMTRACK_H

#include <string>

class G4Track;
class CustomTrack
{

public:

    CustomTrack();
    CustomTrack(G4Track* track);
    CustomTrack(const G4Track* track);
    ~CustomTrack();

    void setTrack(G4Track* track);
    void setTrack(const G4Track* track);

    void setTrackID(int fTrackID);
    void setParentID(int fParentID);
    void setParticleID(int fParticleID);

    void setPositionX(double fPosX);
    void setPositionY(double fPosY);
    void setPositionZ(double fPosZ);

    void setMomentumX(double fMomX);
    void setMomentumY(double fMomY);
    void setMomentumZ(double fMomZ);

    void setTotalEnergy(double fTotE);
    void setKineticEnergy(double fKinE);
    void setVertexKineticEnergy(double fVKinE);

    void setTrackCreatorProcess(std::string CreatorProcess);

    int getTrackID();
    int getParentID();
    int getParticleID();

    double getPositionX();
    double getPositionY();
    double getPositionZ();

    double getMomentumX();
    double getMomentumY();
    double getMomentumZ();
    double getMomentumMag();

    double getTotalEnergy();
    double getKineticEnergy();
    double getVertexKineticEnergy();

    std::string getTrackCreatorProcess();

private:

    int _TrackID;
    int _ParentID;
    int _ParticleID;

    double _PositionX;
    double _PositionY;
    double _PositionZ;

    double _MomentumX;
    double _MomentumY;
    double _MomentumZ;

    double _TotalEnergy;
    double _KineticEnergy;
    double _VertexKineticEnergy;

    std::string _trackCreatorProcess;

};
#endif
