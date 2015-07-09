#pragma once
#include "EventPublisher.h"
#include <memory>
#include <mutex>
#include <atomic>

namespace Library
{
	class EventQueue
	{
	public:
		/*
		* Constructor
		*/
		EventQueue();

		/*
		* Destructor
		*/
		~EventQueue() = default;

		/**
		* @brief Given the address of an EventPublisher, current time and
		* an optional delay time, either enqueue the event of deliver it
		* immediately
		* @param EventPublisher reference and a double current time
		* @return Void
		*/
		void Enqueue(std::shared_ptr<EventPublisher> eventPublisher, std::double_t currentTime, std::double_t delayTime = 0.0);

		/**
		* @brief Given the address of an EventPublisher, sent the event immediately
		* @param An address of an EventPublisher
		* @return void
		*/
		void Send(std::shared_ptr<EventPublisher>& eventPublisher);

		/**
		* @brief Given the current time, publish an queued events that have expired
		* @param a double of the current time
		* @return void
		*/
		void Update(const std::double_t currentTime);

		/**
		* @brief Clear the event queue, sending any expired events
		* @param None
		* @return Void
		*/
		void Clear(std::double_t currentTime);

		/**
		* @brief Returns a boolean indicating the emptiness of the queue
		* @param None
		* @return bool indicating if the queue is empty
		*/
		bool IsEmpty();

		/**
		* @brief Returns the number of events in the queue
		* @param None
		* @return a uint_32 of the number of the events
		*/
		std::uint32_t Count();

	private:
		SList<std::shared_ptr<EventPublisher>> mEvents;
		std::mutex mMutex;
		std::atomic<bool> mUpdateInProcess;
	};
}
