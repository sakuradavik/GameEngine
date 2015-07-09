#pragma once
#include "Reaction.h"

namespace Library
{
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);

	public:
		/**
		* Constructor
		*/
		ReactionAttributed();

		/**
		* Destructor
		*/
		virtual ~ReactionAttributed();

		/**
		* @brief Notify functioned derived from Reaction
		* @param EventPublisher address
		* @return Void
		*/
		virtual void Notify(const EventPublisher& eventPublisher) override;

		/**
		* @brief Will set the subtype 
		* @param string 
		* @return Void
		*/
		void SetSubtype(const std::string& subtype);

		/**
		* @brief Will return this ReactionAttributed subtype
		* @param None
		* @return 
		*/
		std::string GetSubtype() const;

		/**
		* Copy Constructor.
		*/
		ReactionAttributed(const ReactionAttributed& rhs);

		/**
		* Assignment Operator Overload.
		*/
		ReactionAttributed& operator=(const ReactionAttributed& rhs);


	private:
		const static std::string SubtypeName;
	};

	ActionFactory(ReactionAttributed);
}
