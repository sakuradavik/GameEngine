#include "pch.h"
#include "EventQueue.h"
#include <future>

using namespace Library;
using namespace std;

EventQueue::EventQueue() :
mEvents(), mMutex(), mUpdateInProcess(false)
{
}

void EventQueue::Enqueue(std::shared_ptr<EventPublisher> eventPublisher, std::double_t currentTime, std::double_t delayTime)
{
	lock_guard<mutex> lock(mMutex);
	eventPublisher->SetTime(currentTime, delayTime);
	mEvents.PushBack(eventPublisher);
}

void EventQueue::Send(std::shared_ptr<EventPublisher>& eventPublisher)
{
	eventPublisher->Deliver();
}

void EventQueue::Update(const std::double_t currentTime)
{
	if (!mUpdateInProcess.exchange(true))
	{
		SList<std::shared_ptr<EventPublisher>> expiredEvents;
		vector<future<void>> futures;

		{
			lock_guard<mutex> lock(mMutex);
			for (auto it = mEvents.begin(); it != mEvents.end(); ++it)
			{
				if ((*it)->IsExpired(currentTime))
				{
					futures.emplace_back(async(launch::async, &EventPublisher::Deliver, &(*(*it))));
					expiredEvents.PushBack(move(*it));
				}
			}
			for (auto it = expiredEvents.begin(); it != expiredEvents.end(); ++it)
			{
				mEvents.Remove((*it));
			}
		}

		for (auto& f : futures)
		{
			f.get();
		}
		mUpdateInProcess.store(false);
	}
}

void EventQueue::Clear(std::double_t currentTime)
{
	vector<future<void>> futures;

	{
		lock_guard<mutex> lock(mMutex);
		for (auto it = mEvents.begin(); it != mEvents.end(); ++it)
		{
			if ((*it)->IsExpired(currentTime))
			{
				futures.emplace_back(async(launch::async, &EventPublisher::Deliver, &(*(*it))));
			}
		}
	}

	for (auto& f : futures)
	{
		f.get();
	}

	mEvents.Clear();
}

bool EventQueue::IsEmpty()
{
	lock_guard<mutex> lock(mMutex);
	return mEvents.IsEmpty();
}

std::uint32_t EventQueue::Count()
{
	lock_guard<mutex> lock(mMutex);
	return mEvents.Size();
}