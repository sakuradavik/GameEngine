#pragma once
#include <cstdint>
#include "RTTI.H"

namespace Unit_Tests
{
	class MessageFoo : public Library::RTTI
	{
		RTTI_DECLARATIONS(MessageFoo, Library::RTTI);
	public:
		MessageFoo();
		~MessageFoo() = default;

		//add an eventQueue so you can re-enquee 
		bool bMessageHabeenPassed;
		std::uint32_t mNumberOfCalls;
		static int mTestInt;
	};
}
