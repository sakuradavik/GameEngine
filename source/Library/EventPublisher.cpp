#include "pch.h"
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include <thread>
#include <future>

using namespace Library;
using namespace std;

RTTI_DEFINITIONS(EventPublisher);

EventPublisher::EventPublisher(SList<EventSubscriber*>& subscribers, std::mutex& mutex) :
mTimeEnqueued(), mDelayedTime(), mSubscribers(&subscribers), mMutex(), mEventMutex(&mutex)
{
}

EventPublisher& EventPublisher::operator=(const EventPublisher& rhs)
{
	lock_guard<mutex> lock(mMutex);
	if (this != &rhs)
	{
		mSubscribers = rhs.mSubscribers;
		mTimeEnqueued = rhs.mTimeEnqueued;
		mDelayedTime = rhs.mDelayedTime;
	}
	return *this;
}

EventPublisher::EventPublisher(const EventPublisher& rhs) :
mTimeEnqueued(rhs.mTimeEnqueued), mDelayedTime(rhs.mDelayedTime), mSubscribers(rhs.mSubscribers)
{
}

void EventPublisher::SetTime(const std::double_t currentTime, const std::double_t delay)
{
	lock_guard<mutex> lock(mMutex);
	mTimeEnqueued = currentTime;
	mDelayedTime = delay;
}

std::double_t EventPublisher::TimeEnqueued()
{
	lock_guard<mutex> lock(mMutex);
	return mTimeEnqueued;
}

bool EventPublisher::IsExpired(std::double_t currentTime)
{
	if (currentTime < 0)
	{
		throw std::exception("Current Time cannot be negative");
	}

	if ((mTimeEnqueued + mDelayedTime) < currentTime)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void EventPublisher::Deliver()
{
	vector<future<void>> futures;

	{
		lock_guard<mutex> lock(*mEventMutex);
		for (auto& it : *mSubscribers)
		{
			futures.emplace_back(async(launch::async, &EventSubscriber::Notify, &(*it), ref(*this)));
		}
	}

	for (auto& f : futures)
	{
		f.get();
	}
}

std::uint32_t EventPublisher::SubscriberCount()
{
	lock_guard<mutex> lock(mMutex);
	return mSubscribers->Size();
}