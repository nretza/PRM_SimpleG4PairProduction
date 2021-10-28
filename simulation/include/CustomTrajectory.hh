#ifndef CustomTrajectory_hh
#define CustomTrajectory_hh 1

#include <stdlib.h>                 // Include from 'system'
#include <vector>

#include "trkgdefs.hh"
#include "G4VTrajectory.hh"
#include "G4Allocator.hh"
#include "G4ios.hh"                 // Include from 'system'
#include "globals.hh"               // Include from 'global'
#include "G4ParticleDefinition.hh"  // Include from 'particle+matter'
#include "CustomTrajectoryPoint.hh"     // Include from 'tracking'
#include "G4Track.hh"
#include "G4Step.hh"

class G4Polyline;

class CustomTrajectory : public G4VTrajectory
{

  using CustomTrajectoryPointContainer = std::vector<G4VTrajectoryPoint*>;

  public:

    // Constructors/Destructor

    CustomTrajectory();
    CustomTrajectory(const G4Track* aTrack);
    CustomTrajectory(CustomTrajectory &);
    virtual ~CustomTrajectory();

    // Operators

    inline void* operator new(size_t);
    inline void  operator delete(void*);
    inline G4int operator == (const CustomTrajectory& r) const;

    // Get/Set functions

    inline G4int GetTrackID() const
      { return fTrackID; }
    inline G4int GetParentID() const
      { return fParentID; }
    inline G4String GetParticleName() const
      { return ParticleName; }
    inline G4double GetCharge() const
      { return PDGCharge; }
    inline G4int GetPDGEncoding() const
      { return PDGEncoding; }
    inline G4double GetInitialKineticEnergy() const
      { return initialKineticEnergy; }
    inline G4ThreeVector GetInitialMomentum() const
      { return initialMomentum; }

    // Other member functions

    virtual void ShowTrajectory(std::ostream& os=G4cout) const;
    virtual void DrawTrajectory() const;
    virtual void AppendStep(const G4Step* aStep);
    virtual G4int GetPointEntries() const
      { return G4int(positionRecord->size()); }
    virtual G4VTrajectoryPoint* GetPoint(G4int i) const
      { return (*positionRecord)[i]; }
    virtual void MergeTrajectory(G4VTrajectory* secondTrajectory);

    G4ParticleDefinition* GetParticleDefinition();

    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
    virtual std::vector<G4AttValue>* CreateAttValues() const;

  private:

    CustomTrajectoryPointContainer* positionRecord = nullptr;
    G4int                           fTrackID = 0;
    G4int                           fParentID = 0;
    G4int                           PDGEncoding = 0;
    G4double                        PDGCharge = 0.0;
    G4String                        ParticleName = "";
    G4String                        CreatorProcess = "";
    G4double                        initialKineticEnergy = 0.0;
    G4ThreeVector                   initialMomentum;
};

extern G4TRACKING_DLL G4Allocator<CustomTrajectory>*& aTrajectoryAllocator();

inline void* CustomTrajectory::operator new(size_t)
{
  if (aTrajectoryAllocator() == nullptr)
  {
    aTrajectoryAllocator() = new G4Allocator<CustomTrajectory>;
  }
  return (void*)aTrajectoryAllocator()->MallocSingle();
}

inline void CustomTrajectory::operator delete(void* aTrajectory)
{
  aTrajectoryAllocator()->FreeSingle((CustomTrajectory*)aTrajectory);
}

inline G4int CustomTrajectory::operator == (const CustomTrajectory& r) const
{
  return (this==&r);
}

#endif
