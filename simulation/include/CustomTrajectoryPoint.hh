#ifndef CustomTrajectoryPoint_hh
#define CustomTrajectoryPoint_hh 1

#include "trkgdefs.hh"
#include "G4VTrajectoryPoint.hh"
#include "globals.hh"                // Include from 'global'
#include "G4ThreeVector.hh"          // Include from 'geometry'
#include "G4Allocator.hh"            // Include from 'particle+matter'

class CustomTrajectoryPoint : public G4VTrajectoryPoint
{
  public:

    // Constructors/Destructor

    CustomTrajectoryPoint();
    CustomTrajectoryPoint(G4ThreeVector pos);
    CustomTrajectoryPoint(const CustomTrajectoryPoint& right);
    virtual ~CustomTrajectoryPoint();

    // Operators

    inline void *operator new(size_t);
    inline void operator delete(void *aTrajectoryPoint);
    inline G4bool operator==(const CustomTrajectoryPoint& right) const;

    // Get/Set functions

    inline const G4ThreeVector GetPosition() const
      { return fPosition; }

    // Get method for HEPRep style attributes

    virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
    virtual std::vector<G4AttValue>* CreateAttValues() const;


  private:

   G4ThreeVector fPosition;
};

extern G4TRACKING_DLL
G4Allocator<CustomTrajectoryPoint>*& aTrajectoryPointAllocator();

inline void* CustomTrajectoryPoint::operator new(size_t)
{
  if (aTrajectoryPointAllocator() == nullptr)
  {
    aTrajectoryPointAllocator() = new G4Allocator<CustomTrajectoryPoint>;
  }
  return (void *) aTrajectoryPointAllocator()->MallocSingle();
}

inline void CustomTrajectoryPoint::operator delete(void *aTrajectoryPoint)
{
  aTrajectoryPointAllocator()
    ->FreeSingle((CustomTrajectoryPoint *) aTrajectoryPoint);
}

inline G4bool
CustomTrajectoryPoint::operator==(const CustomTrajectoryPoint& right) const
{
  return (this==&right);
}

#endif
