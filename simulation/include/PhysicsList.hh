#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class StepMax;
class PhysicsListMessenger;
class PhysicsList: public G4VModularPhysicsList
{
	public:
		PhysicsList();
		~PhysicsList();

		virtual void ConstructParticle();

		void AddPhysicsList(const G4String& name);
		virtual void ConstructProcess();

		void SetVerboseLevel(G4int verbose)
		{
            verboseLevel = verbose;
		}

		G4int GetVerboseLevel()
		{
            return verboseLevel;
		}


	private:

        G4int verboseLevel = 1;

		void AddIonGasModels();

		G4bool   fHelIsRegisted;
		G4bool   fBicIsRegisted;
		G4bool   fBiciIsRegisted;

		G4String                             fEmName;
		G4VPhysicsConstructor*               fEmPhysicsList;
		G4VPhysicsConstructor*               fDecPhysicsList;
		std::vector<G4VPhysicsConstructor*>  fHadronPhys;

		PhysicsListMessenger*  fMessenger;
};

#endif
