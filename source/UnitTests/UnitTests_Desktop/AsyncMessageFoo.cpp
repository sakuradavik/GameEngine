#include "AsyncMessageFoo.h"

using namespace Library;
using namespace Unit_Tests;

RTTI_DEFINITIONS(AsyncMessageFoo);

AsyncMessageFoo::AsyncMessageFoo() :
bMessageHabeenPassed(false), mNumberOfCalls(0), mMutex()
{
}

void AsyncMessageFoo::SetMessageHasbeenPassed(bool messageHasBeenPassed)
{
	std::lock_guard<std::mutex> lock(mMutex);
	bMessageHabeenPassed = messageHasBeenPassed;
}

AsyncMessageFoo& AsyncMessageFoo::operator=(const AsyncMessageFoo& rhs)
{
	if (this != &rhs)
	{
		bMessageHabeenPassed = rhs.bMessageHabeenPassed;
		mNumberOfCalls = rhs.mNumberOfCalls;
	}
	return *this;
}

Library::EventQueue* AsyncMessageFoo::GetEventQueue()
{
	std::lock_guard<std::mutex> lock(mMutex);
	return mEventQueue;
}

AsyncMessageFoo::AsyncMessageFoo(const AsyncMessageFoo& rhs):
bMessageHabeenPassed(rhs.bMessageHabeenPassed), mNumberOfCalls(rhs.mNumberOfCalls)
{
}

bool AsyncMessageFoo::GetMessageHasBeenPassed()
{
	return bMessageHabeenPassed;
}

void AsyncMessageFoo::IncrementNumberOfCalls()
{
	std::lock_guard<std::mutex> lock(mMutex);
	++mNumberOfCalls;
}
