#ifndef PPVERTEX_H
#define PPVERTEX_H

#include "CustomTrack.hh"

class CustomTrack;
class PPVertex
{
public:

    PPVertex();
    PPVertex(CustomTrack* particle);
    ~PPVertex();

    void addParticle(CustomTrack* Particle);

    CustomTrack* getPhoton();
    CustomTrack* getElectron();
    CustomTrack* getPositron();

    bool gethasPhoton();
    bool gethasElectron();
    bool gethasPositron();

    bool fitsinVertex (CustomTrack* particle);
    bool isComplete();
    int countParticles();

    double getAngle();
    double getInvariantMass();

private:

    CustomTrack* photon;
    CustomTrack* electron;
    CustomTrack* positron;

    bool hasPhoton = false;
    bool hasElectron = false;
    bool hasPositron = false;

    void addPhoton(CustomTrack* photon);
    void addElectron(CustomTrack* electron);
    void addPositron(CustomTrack* positron);

};

#endif
