#include "Foo.h"
#include <string>

using namespace Unit_Tests;

RTTI_DEFINITIONS(Foo);

Foo::Foo() :
mData(0)
{
	mData2 = new int[7];
	for (int i = 0; i < 7; ++i)
	{
		mData2[i] = i;
	}
}

Foo::Foo(int data) :
mData(data)
{
	mData2 = new int[7];
	for (int i = 0; i < 7; ++i)
	{
		mData2[i] = i;
	}
}

Foo::~Foo()
{
	delete[] mData2;
	mData2 = nullptr;
}

bool Foo::operator==(const Foo& rhs)
{
	return (rhs.mData == mData);
}

bool Foo::operator==(const Foo& rhs) const
{
	return  (rhs.mData == mData);
}

Foo& Foo::operator=(const Foo& rhs)
{
	mData = rhs.mData;
	for (int i = 0; i < 7; ++i)
	{
		mData2[i] = rhs.mData2[i];
	}
	return *this;
}

Foo::Foo(const Foo& rhs)
:Foo()
{
	operator=(rhs);
}