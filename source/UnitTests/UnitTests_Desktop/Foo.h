#pragma once
#include "RTTI.H"

namespace Unit_Tests
{
	class Foo : public Library::RTTI
	{
		RTTI_DECLARATIONS(Foo, RTTI);
	public:
		Foo();
		Foo(int data);
		~Foo();
		bool operator==(const Foo& rhs) const;
		bool operator==(const Foo& rhs);
		Foo& operator=(const Foo& rhs);
		Foo(const Foo& rhs);

		int mData;
		int* mData2;
	};
}

