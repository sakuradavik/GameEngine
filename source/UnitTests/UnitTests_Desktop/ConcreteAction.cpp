#include "ConcreteAction.h"

using namespace Library;
using namespace Unit_Tests;

RTTI_DEFINITIONS(ConcreteAction);

ConcreteAction::ConcreteAction():
bUpdateHasBeenCalled(false), mWorldState()
{
}

void ConcreteAction::Update(WorldState& worldState)
{
	bUpdateHasBeenCalled = true;
	mWorldState.mAction = worldState.mAction;
	mWorldState.mEntity = worldState.mEntity;
	mWorldState.mSector = worldState.mSector;
	mWorldState.mWorld = worldState.mWorld;
}
