#include "PPVertex.hh"
#include "CustomTrack.hh"

#include "TVector3.h"

#include <iostream>
#include <cmath>

PPVertex::PPVertex() {}


PPVertex::~PPVertex() {}


PPVertex::PPVertex(CustomTrack* particle)
{
    this->addParticle(particle);
}


CustomTrack* PPVertex::getPhoton()
{
    return this->photon;
}

CustomTrack* PPVertex::getElectron()
{
    return this->electron;
}

CustomTrack* PPVertex::getPositron()
{
    return this->positron;
}


void PPVertex::addParticle(CustomTrack* particle)
{
    switch(particle->getParticleID())
    {
    case 22:
        this->addPhoton(particle);
        break;

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


void PPVertex::addPhoton(CustomTrack* fphoton)
{
    if (this->fitsinVertex(fphoton))
    {
        this->photon = fphoton;
        this->hasPhoton = true;
    }
    return;
}


void PPVertex::addElectron(CustomTrack* felectron)
{
    if (this->fitsinVertex(felectron))
    {
        this->electron = felectron;
        this->hasElectron = true;
    }
    return;
}


void PPVertex::addPositron(CustomTrack* fpositron)
{
    if (this->fitsinVertex(fpositron))
    {
        this->positron = fpositron;
        this->hasPositron = true;
    }
    return;
}


bool PPVertex::gethasPhoton()
{
    return this->hasPhoton;
}
bool PPVertex::gethasElectron()
{
    return this->hasElectron;
}
bool PPVertex::gethasPositron()
{
    return this->hasPositron;
}


bool PPVertex::fitsinVertex (CustomTrack* particle)
{
    bool fits = true;
    switch (particle->getParticleID())
    {
    case 22:
        if (this->hasPhoton)
        {
            fits &= false;
        }
        if (this->hasElectron)
        {
            fits &= (this->electron->getParentID() == particle->getTrackID());
        }
        if (this->hasPositron)
        {
            fits &= (this->positron->getParentID() == particle->getTrackID());
        }
        break;

    case 11:
        if (this->hasPhoton)
        {
            fits &= (this->photon->getTrackID() == particle->getParentID());
        }
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
        if (this->hasPhoton)
        {
            fits &= (this->photon->getTrackID() == particle->getParentID());
        }
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



bool PPVertex::isComplete()
{
    return (this->hasElectron && this->hasPositron && this->hasPhoton);
}



double PPVertex::getAngle()
{
    if (!(this->isComplete()))
    {
        return 0;
    }

    TVector3 momentum_e(this->electron->getMomentumX(), this->electron->getMomentumY(), this->electron->getMomentumZ());
    TVector3 momentum_p(this->positron->getMomentumX(), this->positron->getMomentumY(), this->positron->getMomentumZ());

    momentum_e.SetMag(1);
    momentum_p.SetMag(1);

    double angle = acos(momentum_e * momentum_p);

    return angle;
}



double PPVertex::getInvariantMass()
{
    double E_add   = this->positron->getTotalEnergy() + this->electron->getTotalEnergy();
    double P_X_add = this->positron->getMomentumX()   + this->electron->getMomentumX();
    double P_Y_add = this->positron->getMomentumY()   + this->electron->getMomentumY();
    double P_Z_add = this->positron->getMomentumZ()   + this->electron->getMomentumZ();

    double s = pow(E_add,2) - ( pow(P_X_add,2) + pow(P_Y_add,2) + pow(P_Z_add,2) );

    return sqrt(s);
}



int PPVertex::countParticles()
{
    int i = 0;
    if (this->hasPhoton)
    {
        i++;
    }
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

