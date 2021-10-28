#include "CustomTrajectoryPoint.hh"

#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UnitsTable.hh"

// #define G4ATTDEBUG
#ifdef G4ATTDEBUG
#include "G4AttCheck.hh"
#endif

G4Allocator<CustomTrajectoryPoint>*& aTrajectoryPointAllocator()
{
  G4ThreadLocalStatic G4Allocator<CustomTrajectoryPoint>* _instance = nullptr;
  return _instance;
}

CustomTrajectoryPoint::CustomTrajectoryPoint()
{
  fPosition = G4ThreeVector(0.,0.,0.);
}

CustomTrajectoryPoint::CustomTrajectoryPoint(G4ThreeVector pos)
{
  fPosition = pos;
}

CustomTrajectoryPoint::CustomTrajectoryPoint(const CustomTrajectoryPoint& right)
  : G4VTrajectoryPoint(),fPosition(right.fPosition)
{
}

CustomTrajectoryPoint::~CustomTrajectoryPoint()
{
}

const std::map<G4String,G4AttDef>* CustomTrajectoryPoint::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("CustomTrajectoryPoint",isNew);
  if (isNew)
  {
    G4String Pos("Pos");
    (*store)[Pos] =
      G4AttDef(Pos, "Position", "Physics","G4BestUnit","G4ThreeVector");
  }
  return store;
}

std::vector<G4AttValue>* CustomTrajectoryPoint::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

  values->push_back(G4AttValue("Pos",G4BestUnit(fPosition,"Length"),""));

#ifdef G4ATTDEBUG
  G4cout << G4AttCheck(values,GetAttDefs());
#endif

  return values;
}
