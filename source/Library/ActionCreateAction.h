#pragma once
#include "Action.h"

namespace Library
{
	class ActionCreateAction : public Action
	{
		RTTI_DECLARATIONS(ActionCreateAction, Action);
	public:
		/**
		* Constructor
		*/
		ActionCreateAction();

		/**
		* Destructor
		*/
		~ActionCreateAction() = default;

		/**
		* @brief Set the instanceName
		* @param string reference
		* @return void
		*/
		void SetInstanceName(const std::string& name);

		/**
		* @brief Set the className
		* @param string reference
		* @return void
		*/
		void SetClassName(const std::string& className);

		/**
		* @brief Set the instanceName
		* @param none
		* @return string
		*/
		std::string GetInstanceName();

		/**
		* @brief Set the instanceName
		* @param none
		* @return string
		*/
		std::string GetClassName();

		/**
		* @brief handles the update 
		* @param reference to the WorldState
		* @return Void
		*/
		virtual void Update(WorldState& worldState) override;

	private:
		std::string mInstanceName;
		std::string mClassName;
	};

}