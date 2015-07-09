#pragma once
#include "Action.h"

namespace Library
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);
	public:
		/**
		* Constructor
		*/
		ActionList();

		/**
		* Destructor
		*/
		virtual ~ActionList() = default;

		/**
		* @brief A pure virtual method that accepts a reference to a WorldState
		* @param A reference to the current worldState
		* @return Void
		*/
		virtual void Update(WorldState& worldState) override;
	};
}
