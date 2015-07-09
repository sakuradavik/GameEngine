#include <cxxtest/TestSuite.h>
#include "Vector.h"
#include "Foo.h"

using namespace Library;
using namespace Unit_Tests;

class VectorTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		TS_ASSERT(mIntVector.IsEmpty());
		TS_ASSERT(mIntPointerVector.IsEmpty());
		TS_ASSERT(mFooVector.IsEmpty());
	}

	void tearDown()
	{
		mIntVector.Clear();
		TS_ASSERT(mIntVector.IsEmpty());

		mIntPointerVector.Clear();
		TS_ASSERT(mIntPointerVector.IsEmpty());

		mFooVector.Clear();
		TS_ASSERT(mFooVector.IsEmpty());
	}

	void TestVectorInitialization(void)
	{
		//Testing Primitive Types
		Vector<int>* intVector = nullptr;
		intVector = new Vector<int>();
		TS_ASSERT_DIFFERS(intVector, nullptr);
		delete intVector;

		//Testing Pointer Types
		Vector<int*>* intPointerVector;
		intPointerVector = nullptr;
		intPointerVector = new Vector<int*>();
		TS_ASSERT_DIFFERS(intPointerVector, nullptr);
		delete intPointerVector;
		
		//Testing User Defined types
		Vector<Foo>* fooVector;
		fooVector = nullptr;
		fooVector = new Vector<Foo>();
		TS_ASSERT_DIFFERS(fooVector, nullptr);
		delete fooVector;
	}

	void TestBracketOperator(void)
	{
		//Testing Primitive Types
		mIntVector.PushBack(7);
		mIntVector.PushBack(2);
		mIntVector.PushBack(9);

		TS_ASSERT_EQUALS(mIntVector[0], 7);
		TS_ASSERT_EQUALS(mIntVector[1], 2);
		TS_ASSERT_EQUALS(mIntVector[2], 9);
		TS_ASSERT_THROWS_ANYTHING(mIntVector[7]);

		//Testing Pointer Types
		int a = 7;
		int b = 9;
		int c = 13;

		mIntPointerVector.PushBack(&a);
		mIntPointerVector.PushBack(&b);
		mIntPointerVector.PushBack(&c);

		TS_ASSERT_EQUALS(mIntPointerVector[0], &a);
		TS_ASSERT_EQUALS(mIntPointerVector[1], &b);
		TS_ASSERT_EQUALS(mIntPointerVector[2], &c);
		TS_ASSERT_THROWS_ANYTHING(mIntPointerVector[7]);

		//Testing User Defined Types 
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		mFooVector.PushBack(foo1);
		mFooVector.PushBack(foo2);
		mFooVector.PushBack(foo3);

		TS_ASSERT_EQUALS(mFooVector[0], foo1);
		TS_ASSERT_EQUALS(mFooVector[1], foo2);
		TS_ASSERT_EQUALS(mFooVector[2], foo3);
		TS_ASSERT_THROWS_ANYTHING(mFooVector[7]);
	}

	void TestPopBack(void)
	{
		//Populating Primitive List
		mIntVector.PushBack(7);
		mIntVector.PushBack(5);
		mIntVector.PushBack(3);

		TS_ASSERT_EQUALS(mIntVector.Back(), 3);
		TS_ASSERT_EQUALS(mIntVector.Size(), 3);

		mIntVector.PopBack();
		TS_ASSERT_EQUALS(mIntVector.Back(), 5);
		TS_ASSERT_EQUALS(mIntVector.Size(), 2);

		mIntVector.PopBack();
		TS_ASSERT_EQUALS(mIntVector.Back(), 7);
		TS_ASSERT_EQUALS(mIntVector.Size(), 1);

		//Testing Primitive Types
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerVector.PushBack(&a);
		mIntPointerVector.PushBack(&b);
		mIntPointerVector.PushBack(&c);

		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &c);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 3);

		mIntPointerVector.PopBack();
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &b);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 2);

		mIntPointerVector.PopBack();
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &a);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 1);

		//Testing User Defined Types 
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		mFooVector.PushBack(foo1);
		mFooVector.PushBack(foo2);
		mFooVector.PushBack(foo3);

		TS_ASSERT_EQUALS(mFooVector.Back(), foo3);
		TS_ASSERT_EQUALS(mFooVector.Size(), 3);

		mFooVector.PopBack();
		TS_ASSERT_EQUALS(mFooVector.Back(), foo2);
		TS_ASSERT_EQUALS(mFooVector.Size(), 2);

		mFooVector.PopBack();
		TS_ASSERT_EQUALS(mFooVector.Back(), foo1);
		TS_ASSERT_EQUALS(mFooVector.Size(), 1);
	}

	void TestFront(void)
	{
		//Testing Primitive Types
		TS_ASSERT_THROWS_ANYTHING(mIntVector.Front());

		mIntVector.PushBack(7);
		TS_ASSERT_EQUALS(mIntVector.Front(), 7);

		mIntVector.PopBack();
		mIntVector.PushBack(9);
		TS_ASSERT_EQUALS(mIntVector.Front(), 9);

		mIntVector.PopBack();
		mIntVector.PushBack(13);
		TS_ASSERT_EQUALS(mIntVector.Front(), 13);

		//Testing Pointer Types
		int a = 7;
		int b = 9;
		int c = 13;

		TS_ASSERT_THROWS_ANYTHING(mIntPointerVector.Front());

		mIntPointerVector.PushBack(&a);
		TS_ASSERT_EQUALS(mIntPointerVector.Front(), &a);

		mIntPointerVector.PopBack();
		mIntPointerVector.PushBack(&b);
		TS_ASSERT_EQUALS(mIntPointerVector.Front(), &b);

		mIntPointerVector.PopBack();
		mIntPointerVector.PushBack(&c);
		TS_ASSERT_EQUALS(mIntPointerVector.Front(), &c);

		//Testing User Defined Types
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		TS_ASSERT_THROWS_ANYTHING(mFooVector.Front());

		mFooVector.PushBack(foo1);
		TS_ASSERT_EQUALS(mFooVector.Front(), foo1);

		mFooVector.PopBack();
		mFooVector.PushBack(foo2);
		TS_ASSERT_EQUALS(mFooVector.Front(), foo2);

		mFooVector.PopBack();
		mFooVector.PushBack(foo3);
		TS_ASSERT_EQUALS(mFooVector.Front(), foo3);
	}

	void TestBack(void)
	{
		//Testing Primitive Types
		TS_ASSERT_THROWS_ANYTHING(mIntVector.Back());

		mIntVector.PushBack(7);
		TS_ASSERT_EQUALS(mIntVector.Back(), 7);

		mIntVector.PushBack(9);
		TS_ASSERT_EQUALS(mIntVector.Back(), 9);

		mIntVector.PushBack(13);
		TS_ASSERT_EQUALS(mIntVector.Back(), 13);

		//Testing Pointer Types
		int a = 7;
		int b = 9;
		int c = 13;

		TS_ASSERT_THROWS_ANYTHING(mIntPointerVector.Back());

		mIntPointerVector.PushBack(&a);
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &a);

		mIntPointerVector.PushBack(&b);
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &b);

		mIntPointerVector.PushBack(&c);
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &c);

		//Testing User Defined Types
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		TS_ASSERT_THROWS_ANYTHING(mFooVector.Back());

		mFooVector.PushBack(foo1);
		TS_ASSERT_EQUALS(mFooVector.Back(), foo1);

		mFooVector.PushBack(foo2);
		TS_ASSERT_EQUALS(mFooVector.Back(), foo2);

		mFooVector.PushBack(foo3);
		TS_ASSERT_EQUALS(mFooVector.Back(), foo3);
	}

	void TestPushBack(void)
	{
		//Testing Primitive Types
		mIntVector.PushBack(7);
		TS_ASSERT_EQUALS(mIntVector.Size(), 1);
		TS_ASSERT_EQUALS(mIntVector.Front(), mIntVector.Back());
		TS_ASSERT_EQUALS(mIntVector.Back(), 7);

		mIntVector.PushBack(13);
		TS_ASSERT_EQUALS(mIntVector.Size(), 2);
		TS_ASSERT_DIFFERS(mIntVector.Front(), mIntVector.Back());
		TS_ASSERT_EQUALS(mIntVector.Back(), 13);
		TS_ASSERT_EQUALS(mIntVector.Front(), 7);

		mIntVector.PushBack(11);
		TS_ASSERT_EQUALS(mIntVector.Size(), 3);
		TS_ASSERT_EQUALS(mIntVector.Back(), 11);
		TS_ASSERT_EQUALS(mIntVector.Front(), 7);

		mIntVector.PushBack(13);
		TS_ASSERT_EQUALS(mIntVector.Size(), 4);
		TS_ASSERT_EQUALS(mIntVector.Back(), 13);
		TS_ASSERT_EQUALS(mIntVector.Capacity(), 6); //checking to see if capacity doubles

		//Testing Pointers
		int a = 1;
		int b = 3;
		int c = 5;

		mIntPointerVector.PushBack(&a);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 1);
		TS_ASSERT_EQUALS(mIntPointerVector.Front(), mIntPointerVector.Back());
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &a);

		mIntPointerVector.PushBack(&b);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 2);
		TS_ASSERT_DIFFERS(mIntPointerVector.Front(), mIntPointerVector.Back());
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &b);

		mIntPointerVector.PushBack(&c);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 3);
		TS_ASSERT_DIFFERS(mIntPointerVector.Front(), mIntPointerVector.Back());
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &c);

		mIntPointerVector.PushBack(&a);
		TS_ASSERT_EQUALS(mIntPointerVector.Size(), 4);
		TS_ASSERT_EQUALS(mIntPointerVector.Back(), &a);
		TS_ASSERT_EQUALS(mIntPointerVector.Capacity(), 6);

		//Testing User Defined Types
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		mFooVector.PushBack(foo1);
		TS_ASSERT_EQUALS(mFooVector.Size(), 1);
		TS_ASSERT_EQUALS(mFooVector.Front(), mFooVector.Back());
		TS_ASSERT_EQUALS(mFooVector.Back(), foo1);

		mFooVector.PushBack(foo2);
		TS_ASSERT_EQUALS(mFooVector.Size(), 2);
		TS_ASSERT_DIFFERS(mFooVector.Front(), mFooVector.Back());
		TS_ASSERT_EQUALS(mFooVector.Back(), foo2);

		mFooVector.PushBack(foo3);
		TS_ASSERT_EQUALS(mFooVector.Size(), 3);
		TS_ASSERT_DIFFERS(mFooVector.Front(), mFooVector.Back());
		TS_ASSERT_EQUALS(mFooVector.Back(), foo3);

		mFooVector.PushBack(foo1);
		TS_ASSERT_EQUALS(mFooVector.Size(), 4);
		TS_ASSERT_EQUALS(mFooVector.Back(), foo1);
		TS_ASSERT_EQUALS(mFooVector.Capacity(), 6);
	}

	void TestCopyConstructor(void)
	{
		//Testing Primitive Types
		mIntVector.PushBack(7);
		mIntVector.PushBack(5);
		mIntVector.PushBack(3);
		mIntVector.PushBack(1);

		Vector<int> secondIntVector = mIntVector;
		TS_ASSERT_EQUALS(secondIntVector.Size(), mIntVector.Size());

		while (!mIntVector.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntVector.Back(), mIntVector.Back());
			secondIntVector.PopBack();
			mIntVector.PopBack();
		}

		//Testing Pointers
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerVector.PushBack(&a);
		mIntPointerVector.PushBack(&b);
		mIntPointerVector.PushBack(&c);

		Vector<int*> secondIntPointerVector = mIntPointerVector;
		TS_ASSERT_EQUALS(secondIntPointerVector.Size(), mIntPointerVector.Size());

		while (!mIntPointerVector.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntPointerVector.Back(), mIntPointerVector.Back());
			secondIntPointerVector.PopBack();
			mIntPointerVector.PopBack();
		}

		//Testing User Defined Types
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		mFooVector.PushBack(foo1);
		mFooVector.PushBack(foo2);
		mFooVector.PushBack(foo3);

		Vector<Foo> secondFooVector = mFooVector;
		TS_ASSERT_EQUALS(secondFooVector.Size(), mFooVector.Size());

		while (!mFooVector.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondFooVector.Back(), mFooVector.Back());
			secondFooVector.PopBack();
			mFooVector.PopBack();
		}
	}

	void TestOperatorEquals(void)
	{
		//Testing Primitive Types
		mIntVector.PushBack(7);
		mIntVector.PushBack(5);
		mIntVector.PushBack(3);
		mIntVector.PushBack(1);

		Vector<int> secondIntVector;
		secondIntVector.PushBack(3);
		secondIntVector.PushBack(5);

		secondIntVector = mIntVector;
		TS_ASSERT_EQUALS(secondIntVector.Size(), mIntVector.Size());

		while (!mIntVector.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntVector.Back(), mIntVector.Back());
			secondIntVector.PopBack();
			mIntVector.PopBack();
		}

		//Testing Pointers
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerVector.PushBack(&a);
		mIntPointerVector.PushBack(&b);
		mIntPointerVector.PushBack(&c);

		Vector<int*> secondIntPointerVector;
		secondIntPointerVector.PushBack(&a);

		secondIntPointerVector = mIntPointerVector;
		TS_ASSERT_EQUALS(secondIntPointerVector.Size(), mIntPointerVector.Size());

		while (!mIntPointerVector.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntPointerVector.Back(), mIntPointerVector.Back());
			secondIntPointerVector.PopBack();
			mIntPointerVector.PopBack();
		}

		//Testing User Defined Types
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		mFooVector.PushBack(foo1);
		mFooVector.PushBack(foo2);
		mFooVector.PushBack(foo3);

		Vector<Foo> secondFooVector;
		secondFooVector.PushBack(foo1);

		secondFooVector = mFooVector;
		TS_ASSERT_EQUALS(secondFooVector.Size(), mFooVector.Size());

		while (!mFooVector.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondFooVector.Back(), mFooVector.Back());
			secondFooVector.PopBack();
			mFooVector.PopBack();
		}
	}

	void TestAt(void)
	{
		//Testing Primitive Types
		mIntVector.Reserve(10);

		mIntVector.PushBack(9);
		mIntVector.PushBack(13);
		mIntVector.PushBack(15);

		TS_ASSERT_EQUALS(mIntVector.At(0), mIntVector[0]);
		TS_ASSERT_EQUALS(mIntVector.At(1), mIntVector[1]);
		mIntVector.At(5);
		TS_ASSERT_EQUALS(mIntVector.Size(), 6);
		TS_ASSERT_THROWS_ANYTHING(mIntVector.At(15));

		//Testing User Defined Types
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 13;

		mFooVector.Reserve(10);
		mFooVector.PushBack(foo1);
		mFooVector.PushBack(foo2);
		mFooVector.PushBack(foo3);

		TS_ASSERT_EQUALS(mFooVector.At(0), mFooVector[0]);
		TS_ASSERT_EQUALS(mFooVector.At(1), mFooVector[1]);
		mFooVector.At(5);
		TS_ASSERT_EQUALS(mFooVector.Size(), 6);
		TS_ASSERT_THROWS_ANYTHING(mFooVector.At(15));

		Foo foo4;
		TS_ASSERT_EQUALS(mFooVector.At(9), foo4);

	}

	void TestReserve(void)
	{
		//Testing Primitive Types
		mIntVector.Reserve(8);
		TS_ASSERT_EQUALS(mIntVector.Capacity(), 8);
		mIntVector.Reserve(6);
		TS_ASSERT_EQUALS(mIntVector.Capacity(), 8);


		//Testing User Defined Types
		mFooVector.Reserve(8);
		TS_ASSERT_EQUALS(mFooVector.Capacity(), 8);
		mIntVector.Reserve(6);
		TS_ASSERT_EQUALS(mFooVector.Capacity(), 8);
	}

	void TestFind(void)
	{
		for (int i = 0; i < 5; ++i)
		{
			mIntVector.PushBack(i);
		}

		Vector<int>::Iterator iterator = mIntVector.Find(3);
		TS_ASSERT_EQUALS(*iterator, 3);

		iterator = mIntVector.Find(7);
		TS_ASSERT_EQUALS(iterator, mIntVector.end());
	}

	void TestIterator(void)
	{
		//Default Constructor
		Vector<int>::Iterator* iterator = nullptr;
		iterator = new Vector<int>::Iterator();
		TS_ASSERT_DIFFERS(iterator, nullptr);

		//Exceptions
		Vector<int>::Iterator iterator2 = mIntVector.begin();
		TS_ASSERT_THROWS_ANYTHING(*iterator2);
		TS_ASSERT_THROWS_ANYTHING(iterator2++);

		//Populate mIntVector
		for (int i = 0; i < 5; i++)
		{
			mIntVector.PushBack(i);
		}

		//Pre-Increment and Dereferencing
		int count = 0;
		for (auto it = mIntVector.begin(); it != mIntVector.end(); ++it)
		{
			TS_ASSERT_EQUALS(count, *it);
			count++;
		}
		TS_ASSERT_EQUALS(mIntVector.Size(), count);

		//Post-Increment and Dereferencing
		count = 0;
		for (auto it = mIntVector.begin(); it != mIntVector.end(); it++)
		{
			TS_ASSERT_EQUALS(count, *it);
			count++;
		}

		//Assignment Operator
		Vector<int>::Iterator iterator3;
		iterator3 = Vector<int>::Iterator();

		iterator3 = iterator2;
		for (auto it = iterator2, it2 = iterator3; it != mIntVector.end(); ++it, ++it2)
		{
			TS_ASSERT_EQUALS(*it, *it2);
		}

		//Copy Constructor
		Vector<int>::Iterator iterator4 = iterator2;

		for (auto it = iterator2, it2 = iterator4; it != mIntVector.end(); ++it, ++it2)
		{
			TS_ASSERT_EQUALS(*it, *it2);
		}

		delete iterator;
	}

	void TestRemove(void)
	{
		mIntVector.PushBack(9);
		mIntVector.PushBack(13);
		mIntVector.PushBack(15);

		mIntVector.Remove(1);
		TS_ASSERT_EQUALS(mIntVector.Size(), 2);
		TS_ASSERT_EQUALS(mIntVector[0], 9);
		TS_ASSERT_EQUALS(mIntVector[1], 15);
		TS_ASSERT_THROWS_ANYTHING(mIntVector[2]);
	}

private:
	Vector<int> mIntVector;
	Vector<int*> mIntPointerVector;
	Vector<Foo> mFooVector;
};