#include <cxxtest/TestSuite.h>
#include "Event.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include "MessageFoo.h"
#include "FooEventSubscriber.h"
#include "EventQueue.h"


using namespace Library;
using namespace Unit_Tests;

class EventTestSuite : public CxxTest::TestSuite
{
public:

	void tearDown()
	{
		Event<MessageFoo>::UnsubscribeAll();
	}

	void TestEventSystem()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		auto* event = eventPublisher->As <Event<MessageFoo>>();
		FooEventSubscriber eventSubscriber;
		Event<MessageFoo>::Subscribe(eventSubscriber);
		EventQueue eventQueue;

		TS_ASSERT_EQUALS(eventQueue.Count(), 0);

		eventQueue.Enqueue(eventPublisher, 0.0f);

		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, false);
		TS_ASSERT_EQUALS(eventSubscriber.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(eventQueue.Count(), 1);

		eventQueue.Update(1.0f);

		TS_ASSERT_EQUALS(eventQueue.Count(), 0);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, true);
		TS_ASSERT_EQUALS(eventSubscriber.bHasBeenNotified, true);
	}

	void TestReusingEvents()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		auto* event = eventPublisher->As <Event<MessageFoo>>();
		FooEventSubscriber eventSubscriber;
		Event<MessageFoo>::Subscribe(eventSubscriber);
		EventQueue eventQueue;

		TS_ASSERT_EQUALS(eventQueue.Count(), 0);

		eventQueue.Enqueue(eventPublisher, 0.0f);

		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, false);
		TS_ASSERT_EQUALS(eventSubscriber.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(eventQueue.Count(), 1);

		eventQueue.Update(1.0f);

		TS_ASSERT_EQUALS(eventQueue.Count(), 0);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, true);
		TS_ASSERT_EQUALS(eventSubscriber.bHasBeenNotified, true);

		eventQueue.Enqueue(eventPublisher, 0.0f);
		TS_ASSERT_EQUALS(eventQueue.Count(), 1);
	}

	void TestMultipleSubscribers()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		auto* event = eventPublisher->As <Event<MessageFoo>>();
		FooEventSubscriber eventSubscriber1;
		FooEventSubscriber eventSubscriber2;
		FooEventSubscriber eventSubscriber3;
		FooEventSubscriber eventSubscriber4;
		Event<MessageFoo>::Subscribe(eventSubscriber1);
		Event<MessageFoo>::Subscribe(eventSubscriber2);
		Event<MessageFoo>::Subscribe(eventSubscriber3);
		Event<MessageFoo>::Subscribe(eventSubscriber4);
		EventQueue eventQueue;

		TS_ASSERT(eventQueue.IsEmpty());
		eventQueue.Enqueue(eventPublisher, 0.0);
		TS_ASSERT_EQUALS(eventQueue.Count(),1);
		TS_ASSERT_EQUALS(event->Message().mNumberOfCalls, 0);

		eventQueue.Update(1.0f);

		TS_ASSERT(eventQueue.IsEmpty());
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, true);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(eventSubscriber2.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(eventSubscriber3.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(eventSubscriber4.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(event->Message().mNumberOfCalls, 4);
	}

	void TestMultipleEvents()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		FooEventSubscriber eventSubscriber1;
		Event<MessageFoo>::Subscribe(eventSubscriber1);

		std::shared_ptr<EventPublisher> eventPublisher2 = std::make_shared<Event<MessageFoo>>(message);
		FooEventSubscriber eventSubscriber2;
		Event<MessageFoo>::Subscribe(eventSubscriber2);

		EventQueue eventQueue;
		eventQueue.Enqueue(eventPublisher, 0.0);
		eventQueue.Enqueue(eventPublisher2, 0.0);

		eventQueue.Update(1.0);
		TS_ASSERT(eventQueue.IsEmpty());
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(eventSubscriber2.bHasBeenNotified, true);
	}

	void TestSubscribe()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		FooEventSubscriber eventSubscriber1;
		Event<MessageFoo>::Subscribe(eventSubscriber1);
		TS_ASSERT_EQUALS(eventPublisher->SubscriberCount(), 1);

		FooEventSubscriber eventSubscriber2;
		Event<MessageFoo>::Subscribe(eventSubscriber2);
		TS_ASSERT_EQUALS(eventPublisher->SubscriberCount(), 2);

		EventQueue eventQueue;
		eventQueue.Enqueue(eventPublisher, 0.0);

		eventQueue.Update(1.0);
		TS_ASSERT(eventQueue.IsEmpty());
		eventQueue.Enqueue(eventPublisher, 0.0);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(eventSubscriber2.bHasBeenNotified, true);

	}

	void TestUnsubscribe()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		FooEventSubscriber eventSubscriber1;
		Event<MessageFoo>::Subscribe(eventSubscriber1);
		TS_ASSERT_EQUALS(eventPublisher->SubscriberCount(), 1);

		FooEventSubscriber eventSubscriber2;
		Event<MessageFoo>::Subscribe(eventSubscriber2);
		TS_ASSERT_EQUALS(eventPublisher->SubscriberCount(), 2);

		Event<MessageFoo>::Unsubscribe(eventSubscriber1);
		TS_ASSERT_EQUALS(eventPublisher->SubscriberCount(), 1);

		Event<MessageFoo>::Unsubscribe(eventSubscriber2);
		TS_ASSERT_EQUALS(eventPublisher->SubscriberCount(), 0);

		EventQueue eventQueue;
		eventQueue.Enqueue(eventPublisher, 0.0);
		eventQueue.Update(1.0);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(eventSubscriber2.bHasBeenNotified, false);

	}

	void TestTimeEnqued()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		FooEventSubscriber eventSubscriber1;
		Event<MessageFoo>::Subscribe(eventSubscriber1);
		TS_ASSERT_EQUALS(eventPublisher->TimeEnqueued(), 0.0);

		EventQueue eventQueue;
		eventQueue.Enqueue(eventPublisher, 2.0);
		TS_ASSERT_EQUALS(eventPublisher->TimeEnqueued(), 2.0);
	}

	void TestDelay()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		auto* event = eventPublisher->As <Event<MessageFoo>>();
		FooEventSubscriber eventSubscriber1;
		Event<MessageFoo>::Subscribe(eventSubscriber1);

		EventQueue eventQueue;
		eventQueue.Enqueue(eventPublisher, 0.0,3.0);
		eventQueue.Update(1.0);
		TS_ASSERT_EQUALS(eventQueue.Count(), 1);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, false);

		eventQueue.Update(2.0);
		TS_ASSERT_EQUALS(eventQueue.Count(), 1);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, false);

		eventQueue.Update(3.0);
		TS_ASSERT_EQUALS(eventQueue.Count(), 1);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, false);

		eventQueue.Update(4.0);
		TS_ASSERT_EQUALS(eventQueue.Count(), 0);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, true);
	}

	void TestSend()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		auto* event = eventPublisher->As <Event<MessageFoo>>();
		FooEventSubscriber eventSubscriber1;
		Event<MessageFoo>::Subscribe(eventSubscriber1);

		EventQueue eventQueue;
		TS_ASSERT_EQUALS(eventQueue.Count(), 0);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, false);

		eventQueue.Send(eventPublisher);
		TS_ASSERT_EQUALS(eventQueue.Count(), 0);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(event->Message().bMessageHabeenPassed, true);
	}

	void TestClear()
	{
		MessageFoo message;
		std::shared_ptr<EventPublisher> eventPublisher = std::make_shared<Event<MessageFoo>>(message);
		FooEventSubscriber eventSubscriber1;
		Event<MessageFoo>::Subscribe(eventSubscriber1);

		std::shared_ptr<EventPublisher> eventPublisher2 = std::make_shared<Event<MessageFoo>>(message);
		FooEventSubscriber eventSubscriber2;
		Event<MessageFoo>::Subscribe(eventSubscriber2);

		EventQueue eventQueue;
		eventQueue.Enqueue(eventPublisher, 0.0);
		eventQueue.Enqueue(eventPublisher2, 0.0);

		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, false);
		TS_ASSERT_EQUALS(eventSubscriber2.bHasBeenNotified, false);
		eventQueue.Clear(1.0);
		TS_ASSERT_EQUALS(eventSubscriber1.bHasBeenNotified, true);
		TS_ASSERT_EQUALS(eventSubscriber2.bHasBeenNotified, true);
	}
};