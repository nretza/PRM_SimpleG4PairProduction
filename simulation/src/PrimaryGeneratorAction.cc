#include "PrimaryGeneratorAction.hh"

#include "DataManager.hh"

#include <G4Event.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>


PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(),
    fParticleGun(nullptr)
{
    this->fParticleGun             = new G4ParticleGun(1);

    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("mu-");     // DUMMY
    G4ThreeVector* position  = new G4ThreeVector(0,0,-2000 * CLHEP::mm);                           // DUMMY
    G4ThreeVector* momentum = new G4ThreeVector(0,0,1);                                            // DUMMY
    momentum->setMag( 100 * CLHEP::GeV );                                                          // DUMMY

    this->fParticleGun->SetParticleDefinition(particle);
    this->fParticleGun->SetParticleEnergy(momentum->mag());
    this->fParticleGun->SetParticlePosition(*position);
    this->fParticleGun->SetParticleMomentumDirection(*momentum);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete this->fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    this->fParticleGun->GeneratePrimaryVertex(event);
}
