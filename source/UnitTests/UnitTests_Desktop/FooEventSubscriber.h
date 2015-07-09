#pragma once
#include "EventSubscriber.h"
#include "EventQueue.h"
#include "EventPublisher.h"
#include <mutex>

namespace Unit_Tests
{
	class FooEventSubscriber: public Library::EventSubscriber
	{
	public:
		FooEventSubscriber(Library::EventQueue* eventQueue = nullptr);
		~FooEventSubscriber() = default;
		virtual void Notify(const Library::EventPublisher& eventPublisher) override;

		bool bHasBeenNotified;
		std::mutex mMutex;
		Library::EventQueue* mEventQueue;
	};
}
