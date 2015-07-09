#pragma once
#include "Attribute.h"
#include "WorldState.h"

namespace Library
{
	class World;

	class Sector final : public Attribute
	{
		RTTI_DECLARATIONS(Sector, Attribute);
		friend class World;

	public:
		/**
		* Constructor
		*/
		explicit Sector(World* world = nullptr);

		/**
		* Virtual Destructor
		*/
		~Sector() = default;

		/**
		* Copy Constructor
		*/
		Sector(const Sector& rhs) = delete;

		/**
		* Assignment Operator
		*/
		Sector& operator=(const Sector& rhs) = delete;

		/**
		* @brief Returns a string with the name of the Entity
		* @param None
		* @return String reference of the name of this class
		*/
		const std::string& Name() const;

		/**
		* @brief Returns the Scope* that stores the contained entities in the sector.
		* @param None
		* @return Scope* to all the entities in this sector
		*/
		Scope* Entities();

		/**
		* @brief  which takes an Entity class name and its instance name, and uses the
		* Entity factory to make a new object of the given type, adopts the Entity into the sector
		* @param Const string reference of the Entity name and a const string reference of the instance name
		* @return Void
		*/
		Entity* CreateEntity(const std::string& EntityName, const std::string& instanceName);

		/**
		* @brief Takes a pointer to the world this sector belongs to
		* @param World pointer to the new World this sector will belong to
		* @return Void
		*/
		void SetWorld(World* world);

		/**
		* @brief Returns a pointer to this sectors world
		* @param None
		* @return const World pointer to this sectors world
		*/
		const World* GetWorld() const;

		/**
		* @brief Takes a WorldState reference and updates this sector
		* @param WorldState reference
		* @return Void
		*/
		void Update(WorldState& worldState);

	private:
		std::string mName;
		World* mWorld;
	};

}