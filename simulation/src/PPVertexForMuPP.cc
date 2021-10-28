#include "PPVertexForMuPP.hh"
#include "CustomTrack.hh"

#include "TVector3.h"
#include "G4Track.hh"

#include <iostream>
#include <cmath>

PPVertexForMuPP::PPVertexForMuPP() {}


PPVertexForMuPP::~PPVertexForMuPP() {}


PPVertexForMuPP::PPVertexForMuPP(CustomTrack* particle)
{
    this->addParticle(particle);
}

CustomTrack* PPVertexForMuPP::getElectron()
{
    return this->electron;
}

CustomTrack* PPVertexForMuPP::getPositron()
{
    return this->positron;
}


void PPVertexForMuPP::addParticle(CustomTrack* particle)
{
    switch(particle->getParticleID())
    {

    case 11:
        this->addElectron(particle);
        break;

    case -11:
        this->addPositron(particle);
        break;

    default:
        std::cout << "Unable to set Particle to Vertex" << std::endl;
    }
    return;
}


void PPVertexForMuPP::addElectron(CustomTrack* felectron)
{
    if (this->fitsinVertex(felectron))
    {
        this->electron = felectron;
        this->hasElectron = true;
    }
    return;
}


void PPVertexForMuPP::addPositron(CustomTrack* fpositron)
{
    if (this->fitsinVertex(fpositron))
    {
        this->positron = fpositron;
        this->hasPositron = true;
    }
    return;
}


bool PPVertexForMuPP::gethasElectron()
{
    return this->hasElectron;
}
bool PPVertexForMuPP::gethasPositron()
{
    return this->hasPositron;
}


bool PPVertexForMuPP::fitsinVertex (CustomTrack* particle)
{
    bool fits = true;
    fits &= particle->getTrackCreatorProcess() == "muPairProd";

    switch (particle->getParticleID())
    {
    case 11:
        if (this->hasElectron)
        {
            fits &= false;
        }
        if (this->hasPositron)
        {
            fits &= (this->positron->getParentID() == particle->getParentID());
        }
        break;

    case -11:
        if (this->hasElectron)
        {
            fits &= (this->electron->getParentID() == particle->getParentID());
        }
        if (this->hasPositron)
        {
            fits &= false;
        }
        break;

    default:
        fits &= false;
    }
    return fits;
}



bool PPVertexForMuPP::isComplete()
{
    return (this->hasElectron && this->hasPositron);
}



double PPVertexForMuPP::getAngle()
{
    if (!(this->isComplete()))
    {
        return 0;
    }

    TVector3 momentum_e(this->electron->getMomentumX(), this->electron->getMomentumY(), this->electron->getMomentumZ());
    TVector3 momentum_p(this->positron->getMomentumX(), this->positron->getMomentumY(), this->positron->getMomentumZ());

    //std::cout << std::fixed << "Electron: " << momentum_e[0] /CLHEP::keV  << "\t" << momentum_e[1] /CLHEP::keV  << "\t" << momentum_e[2] /CLHEP::keV  << "\t" << std::endl;
    //std::cout << std::fixed << "Positron: " << momentum_p[0] /CLHEP::keV  << "\t" << momentum_p[1] /CLHEP::keV  << "\t" << momentum_p[2] /CLHEP::keV  << "\t" << std::endl;
    //std::cout << std::endl;

    momentum_e.SetMag(1);
    momentum_p.SetMag(1);

    //std::cout << std::fixed << "Electron: " << momentum_e[0] /CLHEP::keV  << "\t" << momentum_e[1] /CLHEP::keV  << "\t" << momentum_e[2] /CLHEP::keV  << "\t" << std::endl;
    //std::cout << std::fixed << "Positron: " << momentum_p[0] /CLHEP::keV  << "\t" << momentum_p[1] /CLHEP::keV  << "\t" << momentum_p[2] /CLHEP::keV  << "\t" << std::endl;

    double angle = acos( momentum_e * momentum_p);

    //std::cout << std::endl << "Angle:    " << angle << std::endl << std::endl << std::endl << std::endl;


    return angle;
}


double PPVertexForMuPP::getInvariantMass()
{
    double E_add   = this->positron->getTotalEnergy() + this->electron->getTotalEnergy();
    double P_X_add = this->positron->getMomentumX()   + this->electron->getMomentumX();
    double P_Y_add = this->positron->getMomentumY()   + this->electron->getMomentumY();
    double P_Z_add = this->positron->getMomentumZ()   + this->electron->getMomentumZ();

    double s = pow(E_add,2) - ( pow(P_X_add,2) + pow(P_Y_add,2) + pow(P_Z_add,2) );

    return sqrt(s);
}


int PPVertexForMuPP::countParticles()
{
    int i = 0;
    if (this->hasElectron)
    {
        i++;
    }
    if (this->hasPositron)
    {
        i++;
    }
    return i;
}
