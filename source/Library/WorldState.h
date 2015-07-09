#pragma once
#include "GameTime.h"

namespace Library
{
	class World;
	class Sector;
	class Entity;
	class Action;

	class WorldState final
	{
	public:
		/**
		* Constructor
		*/
		WorldState(World* world = nullptr);

		/**
		* Destructor
		*/
		~WorldState() = default;

		/**
		* @brief Returns the current GameTime
		* @param None
		* @return Returns a GameTime reference
		*/
		const GameTime& GetGameTime() const;

		/**
		* @brief Will take a GameTime reference and set this worlds GameTime
		* @param A const GameTimme reference
		* @return Void
		*/
		void SetGameTime(const GameTime& gameTime);

		World* mWorld;
		Sector* mSector;
		Entity* mEntity;
		Action* mAction;

	private:
		GameTime mGameTime;
	};
}
