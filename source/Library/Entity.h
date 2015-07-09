#pragma once
#include "Attribute.h"
#include "WorldState.h"
#include "Factory.h"

namespace Library
{
	class Sector;
	class Action;

	class Entity: public Attribute
	{
		RTTI_DECLARATIONS(Entity, Attribute);
		friend class Sector;
	public:
		/**
		* Constructor
		*/
		explicit Entity(Sector* sector = nullptr);

		/**
		* Virtual Destructor
		*/
		virtual ~Entity() = default;

		/**
		* Copy Constructor
		*/
		Entity(const Entity& rhs) = delete;

		/**
		* Assignment Operator
		*/
		Entity& operator=(const Entity& rhs) = delete;

		/**
		* @brief Returns a string with the name of the entity
		* @param None
		* @return String reference of the name of this class
		*/
		const std::string& Name() const;

		/**
		* @brief Returns the address of the Sector this object pertains to 
		* @param None
		* @return Sector pointer to the parent sector of this entity
		*/
		const Sector* GetSector() const;

		/**
		* @brief Takes a pointer to the sector this entity will get adopted to
		* @param Sector pointer to where this entity will now belong
		* @return Void
		*/
		void SetSector(Sector* sector);

		/**
		* @brief Takes a WorldState reference and updates this entity
		* @param WorldState reference 
		* @return void
		*/
		virtual void Update(WorldState& worldState);

		/**
		* @brief Returns the Scope* that stores the contained actions in the entity.
		* @param None
		* @return Scope* to all the actions in this entity
		*/
		Scope* Actions();

		/**
		* @brief  which takes an action class name and its instance name, and uses the
		* Action factory to make a new object of the given type, adopts the entity into the sector
		* @param Const string reference of the action name and a const string reference of the instance name
		* @return Void
		*/
		Action* CreateAction(const std::string& actionName, const std::string& instanceName);

	private:
	    std::string mName;
		Sector* mSector;
	};

	ConcreteFactory(Entity, Entity);
}

