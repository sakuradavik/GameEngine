#include "pch.h"
#include "ActionList.h"

using namespace Library;
RTTI_DEFINITIONS(ActionList);

ActionList::ActionList() 
{
	mName = std::string();
	mEntity = nullptr;
}

void ActionList::Update(WorldState& worldState)
{
	for (std::uint32_t i = 0; i < mOrderVector.Size(); ++i)
	{
		if (mOrderVector[i]->second.GetType() == Datum::DatumType::Table)
		{
			Scope* scope = mOrderVector[i]->second.GetScope();
			if (scope)
			{
				Action* action = scope->As<Action>();
				if (action)
				{
					worldState.mAction = action;
					action->Update(worldState);
				}
			}
		}
	}
}
