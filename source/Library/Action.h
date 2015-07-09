#pragma once
#include "WorldState.h"
#include "Attribute.h"
#include "Factory.h"

namespace Library
{
	class Action : public Attribute
	{
		RTTI_DECLARATIONS(Action, Attribute);

	public:
		/**
		* Constructor
		*/
		Action() = default;
		
		/**
		* Destructor
		*/
		virtual ~Action() = default;

		/**
		* @brief A pure virtual method that accepts a reference to a WorldState
		* @param A reference to the current worldState
		* @return Void
		*/
		virtual void Update(WorldState& worldState) = 0;

		void SetEntity(Entity* entity);
		Entity* GetEntity();

		std::string Name() const;
		void SetName(const std::string& name);

	protected:
		std::string mName;
		Entity * mEntity;
	};

#define ActionFactory(ActionConcrete)	\
	ConcreteFactory(Action, ActionConcrete)
}