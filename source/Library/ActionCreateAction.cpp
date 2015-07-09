#include "pch.h"
#include "ActionCreateAction.h"
#include "Factory.h"
#include "Entity.h"

using namespace Library;

RTTI_DEFINITIONS(ActionCreateAction);

ActionCreateAction::ActionCreateAction() :
mInstanceName(), mClassName()
{
}

void ActionCreateAction::Update(WorldState& worldState)
{
	if (mEntity && !Search(mInstanceName))
	{
		Action* action = mEntity->CreateAction(mClassName, mInstanceName);
		action->SetName(mInstanceName);
		action->SetEntity(mEntity);
	}
}

void ActionCreateAction::SetInstanceName(const std::string& name)
{
	mInstanceName = name;
}

void ActionCreateAction::SetClassName(const std::string& className)
{
	mClassName = className;
}


std::string ActionCreateAction::GetInstanceName()
{
	return mInstanceName;
}

std::string ActionCreateAction::GetClassName()
{
	return mClassName;
}