#pragma once
#include "Action.h"

namespace Unit_Tests
{
	class ConcreteAction : public Library::Action
	{
		RTTI_DECLARATIONS(ConcreteAction, Library::Action);
	public:
		virtual void Update(Library::WorldState& worldState) override;
		ConcreteAction();
		~ConcreteAction() = default;

		bool bUpdateHasBeenCalled;

		//Will keep track of the state when this action was updated
		Library::WorldState mWorldState;
	};
}
