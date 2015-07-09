#pragma once
#include "RTTI.H"
#include "SList.h"
#include <mutex>

namespace Library
{
	class EventSubscriber;

	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI);
	public:
		/**
		* Constructor
		*/
		EventPublisher(SList<EventSubscriber*>& subscribers, std::mutex& mutex);

		/**
		* Destructor
		*/
		virtual ~EventPublisher() = default;

		/*
		* Assignment Operator
		*/
		EventPublisher& operator=(const EventPublisher& rhs);

		/*
		* Copy Constructor
		*/
		EventPublisher(const EventPublisher& rhs);

		/**
		* @brief Assigns a currentTime and an optional delay for the event
		* @param const double currentTime, double const double if a delay is desired
		* @return Void
		*/
		void SetTime(const std::double_t currentTime, const std::double_t delay = 0.0);

		/**
		* @brief Returns the time when this event was enqueued
		* @param None
		* @return double enqueued time
		*/
		std::double_t TimeEnqueued();

		/**
		* @brief Takes the current time and returns true if the event has expired
		* @param double_t that is the current time
		* @return Boolean indicating that the even has expired
		*/
		bool IsExpired(std::double_t currentTime);

		/**
		* @brief Notify all subscribers of this event
		* @param None
		* @return Void
		*/
		void Deliver();

		/**
		* For Testing purposes I am exposing the numberOfSubscribers
		*/
		std::uint32_t SubscriberCount();

	private:
		std::double_t mTimeEnqueued;
		std::double_t mDelayedTime;
		SList<EventSubscriber*>* mSubscribers;
		mutable std::mutex mMutex;
		std::mutex* mEventMutex;
	};
}
