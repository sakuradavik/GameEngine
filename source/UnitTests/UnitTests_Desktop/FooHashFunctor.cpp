#include "FooHashFunctor.h"
using namespace Unit_Tests;

typedef std::uint8_t byte;
#define HashValue 33

std::uint32_t FooHashFunctor::operator()(const Foo& value) const
{
	uint32_t hash = 0;
	const byte* bytes = reinterpret_cast<const byte*>((value.mData2));
	uint32_t size = sizeof(*bytes);

	for (uint32_t i = 0; i < size; ++i)
	{
		hash = bytes[i] + HashValue * hash;
	}

	bytes = reinterpret_cast<const byte*>(&(value).mData);
	size = sizeof(*bytes);

	for (uint32_t i = 0; i < size; i++)
	{
		hash = bytes[i] + HashValue * hash;
	}
	return hash;
}