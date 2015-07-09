#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace Library
{
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);
	public:
		/*
		* Constructor
		*/
		Reaction() = default;

		/*
		* Destructor
		*/
		virtual ~Reaction() = default;

		/**
		* @brief Update function that is derived from ActionList. It will not
		* do anything when called
		* @param World State
		* @return Void
		*/
		virtual void Update(Library::WorldState& worldState) override;
	};
}