#pragma once
#include "Attribute.h"
#include "WorldState.h"
#include "EventQueue.h"

namespace Library
{
	class Sector;

	class World final : public Attribute
	{
		RTTI_DECLARATIONS(World, Attribute);
	public:
		/** 
		* Constructor
		*/
		World();

		/**
		* Destructor
		*/
		~World() = default;

		/** 
		* @brief Returns a string with the name of the world
		* @param None
		* @return string&
		*/
		const std::string& Name() const;

		/**
		* @brief Sets the name of the world
		* @param string&
		* @return Void
		*/
		void SetName(const std::string& name);

		/**
		* @brief Returns a reference to the Scope*
		* @param None
		* @return Scope*
		*/
		Scope* Sectors();

		/**
		* @brief Instantiates a new sector
		* @param const string& to the new sectors name
		* @return Pointer to the newly created scope
		*/
		Sector* CreateSector(const std::string& name);

		/**
		* @brief Iterates thought the contained Sectors and calls their 
		* Update method
		* @param WorldState&
		* @return Void
		*/
		void Update(WorldState& worldState);

		/**
		* For Testing purposes 
		*/
		WorldState& GetWorldState();

		/*
		* Returns the EventQueue                                                                      
		*/
		EventQueue& GetEventQueue();

	private:
		std::string mName;
		WorldState mWorldState;
		EventQueue mEventQueue;
	};

}