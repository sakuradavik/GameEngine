#pragma once
#include "Foo.h"
#include <cstdint>

namespace Unit_Tests
{
	class FooHashFunctor
	{
	public:
		std::uint32_t operator()(const Foo& value) const;
	};
}

