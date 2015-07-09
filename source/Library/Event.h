#pragma once
#include "EventPublisher.h"

namespace Library
{
	template <typename T>
	class Event : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, RTTI);
	public:
		/*
		* Constructor
		*/
		Event(const T& message);

		/*
		* Destructor
		*/
		virtual ~Event() = default;

		/*
		* Assignment Operator
		*/
		Event& operator=(const Event& rhs) = delete;

		/*
		* Copy Constructor
		*/
		Event(const Event& rhs) = delete;

		/**
		* @brief Given the address of an EventSubscriber and adds it to the
		* list of subscribers
		* @param Takes an address to an EventSubscriber
		* @return Void
		*/
		static void Subscribe(EventSubscriber& eventSubscriber);

		/**
		* @brief Given the address of an EventSubscriiber and remove it
		* from the list of subscribers
		* @param Takes an address to an EventSubscriber
		* @return Void
		*/
		static void Unsubscribe(EventSubscriber& eventSubscriber);

		/**
		* @brief Unsubscribe all subscribers to this event type
		* @param None
		* @return void
		*/
		static void UnsubscribeAll();

		/**
		* @brief Returns the message object
		* @param None
		* @return message object associated with this event
		*/
		 T& Message();

	private:
		T mMessage;

	protected:
		static SList<EventSubscriber*> sSubscriber;
		static std::mutex mMutex;
	};
}

#include "Event.inl"