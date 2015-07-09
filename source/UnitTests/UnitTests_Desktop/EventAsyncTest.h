#include <cxxtest/TestSuite.h>
#include "Event.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "AsyncMessageFoo.h"
#include "FooEventSubscriber.h"
#include "EventQueue.h"


using namespace Library;
using namespace Unit_Tests;

class EventAsyncTestSuite : public CxxTest::TestSuite
{
public:
	void tearDown()
	{
		Event<AsyncMessageFoo>::UnsubscribeAll();
	}

	void TestMultipleEventSubscribers()
	{
		EventQueue eventQueue;
		AsyncMessageFoo message = AsyncMessageFoo();
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<AsyncMessageFoo>>(message);
		std::shared_ptr<EventPublisher> eventPublisher2 = std::make_shared<Event<AsyncMessageFoo>>(message);
		FooEventSubscriber eventSubscriber = FooEventSubscriber(&eventQueue);
		FooEventSubscriber eventSubscriber2 = FooEventSubscriber(&eventQueue);
		Event<AsyncMessageFoo>::Subscribe(eventSubscriber);
		Event<AsyncMessageFoo>::Subscribe(eventSubscriber2);
		

		TS_ASSERT_EQUALS(eventQueue.Count(), 0);

		for (int i = 0; i < 500; i++)
		{
			eventQueue.Enqueue(eventPublisher, 0.0);
			eventQueue.Enqueue(eventPublisher2, 0.0);
		}
		

		TS_ASSERT_EQUALS(eventSubscriber.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(eventQueue.Count(), 1000);

		eventQueue.Update(1.0f);

		TS_ASSERT_EQUALS(eventSubscriber.bHasBeenNotified, true);
	}
};