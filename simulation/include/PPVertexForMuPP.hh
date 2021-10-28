#ifndef PPVERTEXFORMUPP_H
#define PPVERTEXFORMUPP_H

#include "CustomTrack.hh"

class CustomTrack;
class PPVertexForMuPP
{
public:

    PPVertexForMuPP();
    PPVertexForMuPP(CustomTrack* particle);
    ~PPVertexForMuPP();

    void addParticle(CustomTrack* Particle);

    CustomTrack* getElectron();
    CustomTrack* getPositron();

    bool gethasElectron();
    bool gethasPositron();

    bool fitsinVertex (CustomTrack* particle);
    bool isComplete();
    int countParticles();

    double getAngle();
    double getInvariantMass();

private:

    CustomTrack* electron;
    CustomTrack* positron;

    bool hasElectron = false;
    bool hasPositron = false;

    void addElectron(CustomTrack* electron);
    void addPositron(CustomTrack* positron);

};

#endif
