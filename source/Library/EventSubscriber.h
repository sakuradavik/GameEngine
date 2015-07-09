#pragma once
#include "EventPublisher.h"

namespace Library
{
	class EventSubscriber
	{

	public:
		/*
		* Constructor
		*/
		EventSubscriber() = default;

		/*
		* Destructor
		*/
		virtual ~EventSubscriber() = default;

		/**
		* @brief Pure virtual method that accepts the address of an EventPublisher
		* @param EventPublisher address
		* @return Void
		*/
		virtual void Notify(const EventPublisher& eventPublisher) = 0;
	};
}