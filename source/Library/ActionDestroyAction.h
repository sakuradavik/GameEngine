#pragma once
#include "Action.h"

namespace Library
{
	class ActionDestroyAction : public Action
	{
		RTTI_DECLARATIONS(ActionDestroyAction, Action);
	public:
		/**
		* Constructor
		*/
		ActionDestroyAction();

		/**
		* Destructor
		*/
		~ActionDestroyAction() = default;

		/**
		* @brief Set the instanceName
		* @param string reference
		* @return void
		*/
		void SetInstanceName(const std::string& name);

		/**
		* @brief Set the instanceName
		* @param none
		* @return string
		*/
		std::string GetInstanceName();

		/**
		* @brief handles the update
		* @param reference to the WorldState
		* @return Void
		*/
		virtual void Update(WorldState& worldState) override;

	private:
		std::string mInstanceName;
	};

}