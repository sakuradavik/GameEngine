#include "pch.h"
#include "ActionDestroyAction.h"
#include "Factory.h"
#include "Entity.h"
#include "Datum.h"

using namespace Library;

RTTI_DEFINITIONS(ActionDestroyAction);

ActionDestroyAction::ActionDestroyAction() :
mInstanceName()
{
}

void ActionDestroyAction::Update(WorldState& worldState)
{
	Datum * datum = mEntity->Actions()->Search(mInstanceName);
	if (datum)
	{
		Scope* scope = datum->GetScope();
		if (scope)
		{
			scope->Orphan();
			delete scope;
		}
	}
}

void ActionDestroyAction::SetInstanceName(const std::string& name)
{
	mInstanceName = name;
}

std::string ActionDestroyAction::GetInstanceName()
{
	return mInstanceName;
}
