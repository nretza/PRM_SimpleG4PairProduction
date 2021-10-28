#include "CustomTrajectory.hh"
#include "CustomTrajectoryPoint.hh"
#include "G4VProcess.hh"
#include "G4ParticleTable.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"

// #define G4ATTDEBUG
#ifdef G4ATTDEBUG
#include "G4AttCheck.hh"
#endif

G4Allocator<CustomTrajectory>*& aTrajectoryAllocator()
{
    G4ThreadLocalStatic G4Allocator<CustomTrajectory>* _instance = nullptr;
    return _instance;
}

CustomTrajectory::CustomTrajectory()
    : initialMomentum( G4ThreeVector() )
{
}

CustomTrajectory::CustomTrajectory(const G4Track* aTrack)
{
    G4ParticleDefinition* fpParticleDefinition = aTrack->GetDefinition();
    ParticleName = fpParticleDefinition->GetParticleName();
    PDGCharge = fpParticleDefinition->GetPDGCharge();
    PDGEncoding = fpParticleDefinition->GetPDGEncoding();
    fTrackID = aTrack->GetTrackID();
    fParentID = aTrack->GetParentID();
    initialKineticEnergy = aTrack->GetKineticEnergy();
    initialMomentum = aTrack->GetMomentum();
    positionRecord = new CustomTrajectoryPointContainer();

    if( aTrack->GetCreatorProcess() == nullptr )
    {
        CreatorProcess = "undefined";
    }
    else
    {
        CreatorProcess = aTrack->GetCreatorProcess()->GetProcessName();
    }

    // Following is for the first trajectory point
    positionRecord->push_back(new CustomTrajectoryPoint(aTrack->GetPosition()));
}

CustomTrajectory::CustomTrajectory(CustomTrajectory& right)
    : G4VTrajectory()
{
    CreatorProcess = right.CreatorProcess;
    ParticleName = right.ParticleName;
    PDGCharge = right.PDGCharge;
    PDGEncoding = right.PDGEncoding;
    fTrackID = right.fTrackID;
    fParentID = right.fParentID;
    initialKineticEnergy = right.initialKineticEnergy;
    initialMomentum = right.initialMomentum;
    positionRecord = new CustomTrajectoryPointContainer();

    for(std::size_t i=0; i<right.positionRecord->size(); ++i)
    {
        CustomTrajectoryPoint* rightPoint
            = (CustomTrajectoryPoint*)((*(right.positionRecord))[i]);
        positionRecord->push_back(new CustomTrajectoryPoint(*rightPoint));
    }
}

CustomTrajectory::~CustomTrajectory()
{
    if (positionRecord != nullptr)
    {
        for(std::size_t i=0; i<positionRecord->size(); ++i)
        {
            delete  (*positionRecord)[i];
        }
        positionRecord->clear();
        delete positionRecord;
    }
}

void CustomTrajectory::ShowTrajectory(std::ostream& os) const
{
    // Invoke the default implementation in G4VTrajectory...
    G4VTrajectory::ShowTrajectory(os);

    // ... or override with your own code here.
}

void CustomTrajectory::DrawTrajectory() const
{
    // Invoke the default implementation in G4VTrajectory...
    G4VTrajectory::DrawTrajectory();

    // ... or override with your own code here.
}

const std::map<G4String,G4AttDef>* CustomTrajectory::GetAttDefs() const
{
    G4bool isNew;
    std::map<G4String,G4AttDef>* store
        = G4AttDefStore::GetInstance("CustomTrajectory",isNew);
    if (isNew)
    {
        G4String ID("ID");
        (*store)[ID] = G4AttDef(ID,"Track ID","Physics","","G4int");

        G4String PID("PID");
        (*store)[PID] = G4AttDef(PID,"Parent ID","Physics","","G4int");

        G4String PN("PN");
        (*store)[PN] = G4AttDef(PN,"Particle Name","Physics","","G4String");

        G4String Ch("Ch");
        (*store)[Ch] = G4AttDef(Ch,"Charge","Physics","e+","G4double");

        G4String PDG("PDG");
        (*store)[PDG] = G4AttDef(PDG,"PDG Encoding","Physics","","G4int");

        G4String IKE("IKE");
        (*store)[IKE] =
            G4AttDef(IKE, "Initial kinetic energy",
                     "Physics","G4BestUnit","G4double");

        G4String IMom("IMom");
        (*store)[IMom] = G4AttDef(IMom, "Initial momentum",
                                  "Physics","G4BestUnit","G4ThreeVector");

        G4String IMag("IMag");
        (*store)[IMag] =
            G4AttDef(IMag, "Initial momentum magnitude",
                     "Physics","G4BestUnit","G4double");

        G4String NTP("NTP");
        (*store)[NTP] = G4AttDef(NTP,"No. of points","Physics","","G4int");

    }
    return store;
}

std::vector<G4AttValue>* CustomTrajectory::CreateAttValues() const
{
    std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

    values->push_back
    (G4AttValue("ID",G4UIcommand::ConvertToString(fTrackID),""));

    values->push_back
    (G4AttValue("PID",G4UIcommand::ConvertToString(fParentID),""));

    values->push_back(G4AttValue("PN",ParticleName,""));

    values->push_back(G4AttValue("CP",CreatorProcess,""));

    values->push_back
    (G4AttValue("Ch",G4UIcommand::ConvertToString(PDGCharge),""));

    values->push_back
    (G4AttValue("PDG",G4UIcommand::ConvertToString(PDGEncoding),""));

    values->push_back
    (G4AttValue("IKE",G4BestUnit(initialKineticEnergy,"Energy"),""));

    values->push_back
    (G4AttValue("IMom",G4BestUnit(initialMomentum,"Energy"),""));

    values->push_back
    (G4AttValue("IMag",G4BestUnit(initialMomentum.mag(),"Energy"),""));

    values->push_back
    (G4AttValue("NTP",G4UIcommand::ConvertToString(GetPointEntries()),""));

#ifdef G4ATTDEBUG
    G4cout << G4AttCheck(values,GetAttDefs());
#endif

    return values;
}

void CustomTrajectory::AppendStep(const G4Step* aStep)
{
    positionRecord->push_back( new CustomTrajectoryPoint(aStep->GetPostStepPoint()->
                               GetPosition()) );
}

G4ParticleDefinition* CustomTrajectory::GetParticleDefinition()
{
    return (G4ParticleTable::GetParticleTable()->FindParticle(ParticleName));
}

void CustomTrajectory::MergeTrajectory(G4VTrajectory* secondTrajectory)
{
    if(secondTrajectory == nullptr) return;

    CustomTrajectory* seco = (CustomTrajectory*)secondTrajectory;
    G4int ent = seco->GetPointEntries();
    for(G4int i=1; i<ent; ++i) // initial pt of 2nd trajectory shouldn't be merged
    {
        positionRecord->push_back((*(seco->positionRecord))[i]);
    }
    delete (*seco->positionRecord)[0];
    seco->positionRecord->clear();
}
