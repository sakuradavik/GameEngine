#include "pch.h"
#include "WorldState.h"

using namespace Library;

WorldState::WorldState(World* world) :
mWorld(world), mGameTime()
{
}

const GameTime& WorldState::GetGameTime() const
{
	return mGameTime;
}

void WorldState::SetGameTime(const GameTime& gameTime)
{
	mGameTime = gameTime;
}