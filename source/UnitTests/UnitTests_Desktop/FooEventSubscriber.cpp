#include "FooEventSubscriber.h"
#include "Event.h"
#include "MessageFoo.h"
#include "AsyncMessageFoo.h"
#include <memory>
#include <iostream>

using namespace Unit_Tests;
using namespace Library;
using namespace std;

FooEventSubscriber::FooEventSubscriber(EventQueue* eventQueue) :
bHasBeenNotified(false), mMutex(), mEventQueue(eventQueue)
{
}

void FooEventSubscriber::Notify(const EventPublisher& eventPublisher)
{
	Event<MessageFoo> * event = eventPublisher.As<Event<MessageFoo>>();
	if (event)
	{

		bHasBeenNotified = true;
		event->Message().bMessageHabeenPassed = true;
		event->Message().mNumberOfCalls++;
		event->Message().mTestInt++;
	}

	Event<AsyncMessageFoo> * event2 = eventPublisher.As<Event<AsyncMessageFoo>>();
	if (event2)
	{
		lock_guard<mutex> lock(mMutex);
		Event<AsyncMessageFoo>::Unsubscribe(*this);
		bHasBeenNotified = true;
		event2->Message().SetMessageHasbeenPassed(true);
		event2->Message().IncrementNumberOfCalls();

		AsyncMessageFoo asyncMessage = AsyncMessageFoo();
		std::shared_ptr<Event<AsyncMessageFoo>> asyncEvent = std::make_shared<Event<AsyncMessageFoo>>(asyncMessage);
		mEventQueue->Enqueue(asyncEvent, 0.0);
		mEventQueue->Update(1.0);
	}
}
