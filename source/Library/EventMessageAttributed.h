#pragma once
#include "Attribute.h"

namespace Library
{
	class World;

	class EventMessageAttributed : public Attribute
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attribute);
	public:
		/**
		* Constructor
		*/
		EventMessageAttributed(World* world = nullptr);

		/**
		* Destructor
		*/
		~EventMessageAttributed() = default;
		
		/**
		* @brief Returns a pointer to the World object
		* @param None
		* @return World pointer
		*/
		World* GetWorld() const;

		/**
		* @brief Will set the world pointer stored in this message
		* @param World pointer
		* @return Void
		*/
		void SetWorld(World* world);

		/**
		* @brief Will return the subtype of this message
		* @param None
		* @return Datum of type string
		*/
		std::string& GetSubtype() const;

		/**
		* @brief Returns the subtype of this message
		* @param a Datum of type string
		* @return Void
		*/
		void SetSubtype(std::string& subtype);

	private:
		World* mWorld;
	};
}
