#include "pch.h"
#include "Action.h"

using namespace Library;

RTTI_DEFINITIONS(Action);

void Action::SetEntity(Entity* entity)
{
	mEntity = entity;
}

Entity* Action::GetEntity()
{
	return mEntity;
}

std::string Action::Name() const
{
	return mName;
}
void Action::SetName(const std::string& name)
{
	mName = name;
}