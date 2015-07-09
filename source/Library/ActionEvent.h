#pragma once
#include "Action.h"

namespace Library
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);
	public:
		/**
		* Constructor
		*/
		ActionEvent();

		/**
		* Destructor
		*/
		virtual ~ActionEvent() = default;

		/**
		* @brief enques the events
		* do anything when called
		* @param World State
		* @return Void
		*/
		virtual void Update(WorldState& worldState) override;

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

		/*
		* Returns the delay
		*/
		std::int32_t GetDelay() const;

		void SetDelay(std::int32_t delay);
	};

	ActionFactory(ActionEvent);
}