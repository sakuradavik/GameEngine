#pragma once
#include "RTTI.H"
#include "EventQueue.h"

namespace Unit_Tests
{
	class AsyncMessageFoo : public Library::RTTI
	{
		RTTI_DECLARATIONS(AsyncMessageFoo, Library::RTTI);

	public:
		AsyncMessageFoo();
		~AsyncMessageFoo() = default;

		void SetMessageHasbeenPassed(bool messageHasBeenPassed);
		bool GetMessageHasBeenPassed();
		void IncrementNumberOfCalls();
		Library::EventQueue* GetEventQueue();

		AsyncMessageFoo& operator=(const AsyncMessageFoo& rhs);
		AsyncMessageFoo(const AsyncMessageFoo& rhs);
		Library::EventQueue* mEventQueue;

	private:
		std::mutex mMutex;
		bool bMessageHabeenPassed;
		std::uint32_t mNumberOfCalls;
		
		
	};
}