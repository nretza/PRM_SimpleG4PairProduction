#include "PhysListEmStandard.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4EmParameters.hh"
#include "G4EmBuilder.hh"
#include "G4LossTableManager.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4VEmModel.hh"
#include "G4BetheHeitler5DModel.hh"
#include "G4LivermoreGammaConversion5DModel.hh"
#include "G4PenelopeGammaConversionModel.hh"


#include "G4eMultipleScattering.hh"
#include "G4hMultipleScattering.hh"
#include "G4CoulombScattering.hh"
#include "G4eCoulombScatteringModel.hh"
#include "G4WentzelVIModel.hh"
#include "G4UrbanMscModel.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4GenericIon.hh"

#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"
#include "G4EmModelActivator.hh"
#include "G4GammaGeneralProcess.hh"

// factory
#include "G4PhysicsConstructorFactory.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysListEmStandard::PhysListEmStandard(const G4String& name, G4int verbose , int opt )
    :  G4VPhysicsConstructor(name)
{
    verboseLevel = verbose;
    option = opt;

    G4EmParameters* param = G4EmParameters::Instance();
    param->SetDefaults();
    param->SetVerbose(verbose);
    SetPhysicsType(bElectromagnetic);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


PhysListEmStandard::~PhysListEmStandard()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysListEmStandard::ConstructParticle()
{
    // minimal set of particles for EM physics
    G4EmBuilder::ConstructMinimalEmSet();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysListEmStandard::ConstructProcess()
{
    if(verboseLevel > 1)
    {
        G4cout << "### " << GetPhysicsName() << " Construct Processes " << G4endl;
    }
    G4EmBuilder::PrepareEMPhysics();

    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

    // processes used by several particles
    G4hMultipleScattering* hmsc = new G4hMultipleScattering("ionmsc");
    G4NuclearStopping* pnuc(nullptr);

    // high energy limit for e+- scattering models and bremsstrahlung
    G4double highEnergyLimit = G4EmParameters::Instance()->MscEnergyLimit();

    // Add gamma EM Processes
    G4ParticleDefinition* particle = G4Gamma::Gamma();

    G4PhotoElectricEffect* pee = new G4PhotoElectricEffect();
    pee->SetEmModel(new G4LivermorePhotoElectricModel());


////////////////////////////////////////////////////////////////////////////////

    //Conversion Model
    G4GammaConversion* ConvProcess = new G4GammaConversion();
    if ( option == 1 ) //EMOPT4
    {
        G4VEmModel* conv = new G4BetheHeitler5DModel();
        ConvProcess->SetEmModel(conv);
    }
    else if ( option == 2 ) //LIVERMORE
    {
        G4VEmModel* convLiv = new G4LivermoreGammaConversion5DModel();
        ConvProcess->SetEmModel(convLiv);
    }
    else if ( option == 3 )//PENELOPE
    {
        G4PenelopeGammaConversionModel* theGCPenelopeModel = new G4PenelopeGammaConversionModel();
        theGCPenelopeModel->SetHighEnergyLimit(1.0*CLHEP::GeV);
        ConvProcess->AddEmModel(0, theGCPenelopeModel);
    }
    else //EMOPT0
    {

    }

////////////////////////////////////////////////////////////////////////////////

    if(G4EmParameters::Instance()->GeneralProcessActive())
    {
        G4GammaGeneralProcess* sp = new G4GammaGeneralProcess();
        sp->AddEmProcess(pee);
        sp->AddEmProcess(new G4ComptonScattering());
        sp->AddEmProcess(ConvProcess);
        sp->AddEmProcess(new G4RayleighScattering());
        G4LossTableManager::Instance()->SetGammaGeneralProcess(sp);
        ph->RegisterProcess(sp, particle);

    }
    else
    {
        ph->RegisterProcess(pee, particle);
        ph->RegisterProcess(new G4ComptonScattering(), particle);
        ph->RegisterProcess(ConvProcess, particle);
        ph->RegisterProcess(new G4RayleighScattering(), particle);
    }

    // e-
    particle = G4Electron::Electron();

    G4eMultipleScattering* msc = new G4eMultipleScattering;
    G4UrbanMscModel* msc1 = new G4UrbanMscModel();
    G4WentzelVIModel* msc2 = new G4WentzelVIModel();
    msc1->SetHighEnergyLimit(highEnergyLimit);
    msc2->SetLowEnergyLimit(highEnergyLimit);
    msc->SetEmModel(msc1);
    msc->SetEmModel(msc2);

    G4eCoulombScatteringModel* ssm = new G4eCoulombScatteringModel();
    G4CoulombScattering* ss = new G4CoulombScattering();
    ss->SetEmModel(ssm);
    ss->SetMinKinEnergy(highEnergyLimit);
    ssm->SetLowEnergyLimit(highEnergyLimit);
    ssm->SetActivationLowEnergyLimit(highEnergyLimit);

    ph->RegisterProcess(msc, particle);
    ph->RegisterProcess(new G4eIonisation(), particle);
    ph->RegisterProcess(new G4eBremsstrahlung(), particle);
    ph->RegisterProcess(ss, particle);

    // e+
    particle = G4Positron::Positron();

    msc = new G4eMultipleScattering;
    msc1 = new G4UrbanMscModel();
    msc2 = new G4WentzelVIModel();
    msc1->SetHighEnergyLimit(highEnergyLimit);
    msc2->SetLowEnergyLimit(highEnergyLimit);
    msc->SetEmModel(msc1);
    msc->SetEmModel(msc2);

    ssm = new G4eCoulombScatteringModel();
    ss = new G4CoulombScattering();
    ss->SetEmModel(ssm);
    ss->SetMinKinEnergy(highEnergyLimit);
    ssm->SetLowEnergyLimit(highEnergyLimit);
    ssm->SetActivationLowEnergyLimit(highEnergyLimit);

    ph->RegisterProcess(msc, particle);
    ph->RegisterProcess(new G4eIonisation(), particle);
    ph->RegisterProcess(new G4eBremsstrahlung(), particle);
    ph->RegisterProcess(new G4eplusAnnihilation(), particle);
    ph->RegisterProcess(ss, particle);

    // generic ion
    particle = G4GenericIon::GenericIon();
    G4ionIonisation* ionIoni = new G4ionIonisation();
    ph->RegisterProcess(hmsc, particle);
    ph->RegisterProcess(ionIoni, particle);

    // muons, hadrons ions
    G4EmBuilder::ConstructCharged(hmsc, pnuc);

    // extra configuration
    G4EmModelActivator mact(GetPhysicsName());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
