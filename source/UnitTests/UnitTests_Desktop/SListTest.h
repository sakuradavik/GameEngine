#include <cxxtest/TestSuite.h>
#include "Foo.h"
#include "SList.h"

using namespace Library;
using namespace Unit_Tests;

class SListTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		TS_ASSERT(mIntList.IsEmpty());
		TS_ASSERT(mIntPointerList.IsEmpty());
		TS_ASSERT(mFooList.IsEmpty());
	}

	void tearDown()
	{
		mIntList.Clear();
		TS_ASSERT(mIntList.IsEmpty());

		mIntPointerList.Clear();
		TS_ASSERT(mIntPointerList.IsEmpty());

		mFooList.Clear();
		TS_ASSERT(mFooList.IsEmpty());
	}

	void TestSListInstantiation(void)
	{
		//Testing Primitive Types
		SList<int>* intList = nullptr;
		intList = new SList<int>();
		TS_ASSERT_DIFFERS(intList, nullptr);
		delete intList;

		//Testing Pointers
		SList<int*>* intPointerList;
		intPointerList = nullptr;
		intPointerList = new SList<int*>();
		TS_ASSERT_DIFFERS(intPointerList, nullptr);
		delete intPointerList;

		//Testing User Defined Types
		SList<Foo>* fooList = nullptr;
		fooList = new SList<Foo>();
		TS_ASSERT_DIFFERS(fooList, nullptr);
		delete fooList;
	}

	void TestPushFront(void)
	{
		//Testing Primitive Types
		mIntList.PushFront(7);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_EQUALS(mIntList.Front(), mIntList.Back());
		TS_ASSERT_EQUALS(mIntList.Front(), 7);

		mIntList.PushFront(13);
		TS_ASSERT_EQUALS(mIntList.Size(), 2);
		TS_ASSERT_DIFFERS(mIntList.Front(), mIntList.Back());
		TS_ASSERT_EQUALS(mIntList.Front(), 13);
		TS_ASSERT_EQUALS(mIntList.Back(), 7);

		mIntList.PushFront(11);
		TS_ASSERT_EQUALS(mIntList.Size(), 3);
		TS_ASSERT_EQUALS(mIntList.Back(),7);
		TS_ASSERT_EQUALS(mIntList.Front(), 11);

		//Testing Pointers
		int a = 1;
		int b = 3;
		int c = 5;

		mIntPointerList.PushFront(&a);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), mIntPointerList.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &a);

		mIntPointerList.PushFront(&b);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 2);
		TS_ASSERT_DIFFERS(mIntPointerList.Front(), mIntPointerList.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &b);

		mIntPointerList.PushFront(&c);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 3);
		TS_ASSERT_DIFFERS(mIntPointerList.Front(), mIntPointerList.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &c);

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooList.PushFront(aFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 1);
		TS_ASSERT_EQUALS(mFooList.Front(), mFooList.Back());
		TS_ASSERT_EQUALS(mFooList.Front(), aFoo);

		mFooList.PushFront(bFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 2);
		TS_ASSERT_DIFFERS(mFooList.Front(), mFooList.Back());
		TS_ASSERT_EQUALS(mFooList.Front(), bFoo);

		mFooList.PushFront(cFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 3);
		TS_ASSERT_DIFFERS(mFooList.Front(), mFooList.Back());
		TS_ASSERT_EQUALS(mFooList.Front(), cFoo);

	}

	void TestPopFront(void)
	{
		//Populating Primitive List
		mIntList.PushBack(7);
		mIntList.PushBack(5);
		mIntList.PushBack(3);

		TS_ASSERT_EQUALS(mIntList.Size(), 3);

		mIntList.PopFront();
		TS_ASSERT_EQUALS(mIntList.Front(), 5);
		TS_ASSERT_EQUALS(mIntList.Size(),2);

		mIntList.PopFront();
		TS_ASSERT_EQUALS(mIntList.Front(), 3);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);

		//Testing Primitive Types
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerList.PushBack(&a);
		mIntPointerList.PushBack(&b);
		mIntPointerList.PushBack(&c);

		TS_ASSERT_EQUALS(mIntPointerList.Size(), 3);

		mIntPointerList.PopFront();
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &b);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 2);

		mIntPointerList.PopFront();
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &c);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);

		//Testing User Defined Type
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooList.PushBack(aFoo);
		mFooList.PushBack(bFoo);
		mFooList.PushBack(cFoo);

		TS_ASSERT_EQUALS(mFooList.Size(), 3);

		mFooList.PopFront();
		TS_ASSERT_EQUALS(mFooList.Front(), bFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 2);

		mFooList.PopFront();
		TS_ASSERT_EQUALS(mFooList.Front(), cFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 1);
	}

	void TestPushBack(void)
	{
		//Testing Primitive Types
		mIntList.PushBack(7);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);
		TS_ASSERT_EQUALS(mIntList.Front(), mIntList.Back());
		TS_ASSERT_EQUALS(mIntList.Back(), 7);

		mIntList.PushBack(13);
		TS_ASSERT_EQUALS(mIntList.Size(), 2);
		TS_ASSERT_DIFFERS(mIntList.Front(), mIntList.Back());
		TS_ASSERT_EQUALS(mIntList.Back(), 13);
		TS_ASSERT_EQUALS(mIntList.Front(), 7);

		mIntList.PushBack(11);
		TS_ASSERT_EQUALS(mIntList.Size(), 3);
		TS_ASSERT_EQUALS(mIntList.Back(), 11);
		TS_ASSERT_EQUALS(mIntList.Front(), 7);

		//Testing Pointers
		int a = 1;
		int b = 3;
		int c = 5;

		mIntPointerList.PushBack(&a);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), mIntPointerList.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Back(), &a);

		mIntPointerList.PushBack(&b);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 2);
		TS_ASSERT_DIFFERS(mIntPointerList.Front(), mIntPointerList.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Back(), &b);

		mIntPointerList.PushBack(&c);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 3);
		TS_ASSERT_DIFFERS(mIntPointerList.Front(), mIntPointerList.Back());
		TS_ASSERT_EQUALS(mIntPointerList.Back(), &c);

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooList.PushBack(aFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 1);
		TS_ASSERT_EQUALS(mFooList.Front(), mFooList.Back());
		TS_ASSERT_EQUALS(mFooList.Back(), aFoo);

		mFooList.PushBack(bFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 2);
		TS_ASSERT_DIFFERS(mFooList.Front(), mFooList.Back());
		TS_ASSERT_EQUALS(mFooList.Back(), bFoo);

		mFooList.PushBack(cFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 3);
		TS_ASSERT_DIFFERS(mFooList.Front(), mFooList.Back());
		TS_ASSERT_EQUALS(mFooList.Back(), cFoo);
	}

	void TestFront(void)
	{
		//Testing Primitive Types
		TS_ASSERT_THROWS_ANYTHING(mIntList.Front());

		mIntList.PushFront(7);
		TS_ASSERT_EQUALS(mIntList.Front(),7);

		mIntList.PushFront(5);
		TS_ASSERT_EQUALS(mIntList.Front(), 5);

		mIntList.PushFront(3);
		TS_ASSERT_EQUALS(mIntList.Front(), 3);

		mIntList.PushFront(1);
		TS_ASSERT_EQUALS(mIntList.Front(), 1);

		//Testing Pointers
		int a = 1;
		int b = 3;
		int c = 5;

		TS_ASSERT_THROWS_ANYTHING(mIntPointerList.Front());

		mIntPointerList.PushFront(&a);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &a);

		mIntPointerList.PushFront(&b);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &b);

		mIntPointerList.PushFront(&c);
		TS_ASSERT_EQUALS(mIntPointerList.Front(), &c);

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		TS_ASSERT_THROWS_ANYTHING(mFooList.Front());

		mFooList.PushFront(aFoo);
		TS_ASSERT_EQUALS(mFooList.Front(), aFoo);

		mFooList.PushFront(bFoo);
		TS_ASSERT_EQUALS(mFooList.Front(), bFoo);

		mFooList.PushFront(cFoo);
		TS_ASSERT_EQUALS(mFooList.Front(), cFoo);

	}

	void TestBack(void)
	{
		//Testing Primitive Types
		TS_ASSERT_THROWS_ANYTHING(mIntList.Back());

		mIntList.PushBack(7);
		TS_ASSERT_EQUALS(mIntList.Back(), 7);

		mIntList.PushBack(5);
		TS_ASSERT_EQUALS(mIntList.Back(), 5);

		mIntList.PushBack(3);
		TS_ASSERT_EQUALS(mIntList.Back(), 3);

		mIntList.PushBack(1);
		TS_ASSERT_EQUALS(mIntList.Back(), 1);

		//Testing Pointers
		int a = 1;
		int b = 3;
		int c = 5;

		TS_ASSERT_THROWS_ANYTHING(mIntPointerList.Back());

		mIntPointerList.PushBack(&a);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), &a);

		mIntPointerList.PushBack(&b);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), &b);

		mIntPointerList.PushBack(&c);
		TS_ASSERT_EQUALS(mIntPointerList.Back(), &c);

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		TS_ASSERT_THROWS_ANYTHING(mFooList.Back());

		mFooList.PushBack(aFoo);
		TS_ASSERT_EQUALS(mFooList.Back(), aFoo);

		mFooList.PushBack(bFoo);
		TS_ASSERT_EQUALS(mFooList.Back(), bFoo);

		mFooList.PushBack(cFoo);
		TS_ASSERT_EQUALS(mFooList.Back(), cFoo);

	}

	void TestSize(void)
	{
		//Testing Primitive Types
		TS_ASSERT_EQUALS(mIntList.Size(),0);

		mIntList.PushFront(7);
		TS_ASSERT_EQUALS(mIntList.Size(), 1);

		mIntList.PushBack(7);
		TS_ASSERT_EQUALS(mIntList.Size(), 2);

		mIntList.PopFront();
		TS_ASSERT_EQUALS(mIntList.Size(), 1);

		//Testing Pointers
		int a = 7;
		int b = 9;

		TS_ASSERT_EQUALS(mIntPointerList.Size(), 0);

		mIntPointerList.PushFront(&a);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);

		mIntPointerList.PushBack(&b);
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 2);

		mIntPointerList.PopFront();
		TS_ASSERT_EQUALS(mIntPointerList.Size(), 1);

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		TS_ASSERT_EQUALS(mFooList.Size(), 0);

		mFooList.PushFront(aFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 1);

		mFooList.PushBack(bFoo);
		TS_ASSERT_EQUALS(mFooList.Size(), 2);

		mFooList.PopFront();
		TS_ASSERT_EQUALS(mFooList.Size(), 1);

	}

	void TestCopyConstructor(void)
	{
		//Testing Primitive Types
		mIntList.PushBack(7);
		mIntList.PushBack(5);
		mIntList.PushBack(3);
		mIntList.PushBack(1);

		SList<int> secondIntList = mIntList;
		TS_ASSERT_EQUALS(secondIntList.Size(), mIntList.Size());

		while (!mIntList.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntList.Front(), mIntList.Front());
			secondIntList.PopFront();
			mIntList.PopFront();
		}

		//Testing Pointers
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerList.PushBack(&a);
		mIntPointerList.PushBack(&b);
		mIntPointerList.PushBack(&c);

		SList<int*> secondIntPointerList = mIntPointerList;
		TS_ASSERT_EQUALS(secondIntPointerList.Size(), mIntPointerList.Size());

		while (!mIntPointerList.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntPointerList.Front(), mIntPointerList.Front());
			secondIntPointerList.PopFront();
			mIntPointerList.PopFront();
		}

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooList.PushBack(aFoo);
		mFooList.PushBack(bFoo);
		mFooList.PushBack(cFoo);

		SList<Foo> secondFooList = mFooList;
		TS_ASSERT_EQUALS(secondFooList.Size(), mFooList.Size());

		while (!mFooList.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondFooList.Front(), mFooList.Front());
			secondFooList.PopFront();
			mFooList.PopFront();
		}
	}

	void TestOperatorEquals(void)
	{
		//Testing Primitive Types
		mIntList.PushBack(7);
		mIntList.PushBack(5);
		mIntList.PushBack(3);
		mIntList.PushBack(1);

		SList<int> secondIntList;
		secondIntList.PushBack(3);
		secondIntList.PushBack(5);

		secondIntList = mIntList;
		TS_ASSERT_EQUALS(secondIntList.Size(), mIntList.Size());

		while (!mIntList.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntList.Front(), mIntList.Front());
			secondIntList.PopFront();
			mIntList.PopFront();
		}

		//Testing Pointers
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerList.PushBack(&a);
		mIntPointerList.PushBack(&b);
		mIntPointerList.PushBack(&c);

		SList<int*> secondIntPointerList;
		secondIntPointerList.PushBack(&a);

		secondIntPointerList = mIntPointerList;
		TS_ASSERT_EQUALS(secondIntPointerList.Size(), mIntPointerList.Size());

		while (!mIntPointerList.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntPointerList.Front(), mIntPointerList.Front());
			secondIntPointerList.PopFront();
			mIntPointerList.PopFront();
		}

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooList.PushBack(aFoo);
		mFooList.PushBack(bFoo);
		mFooList.PushBack(cFoo);

		SList<Foo> secondFooList;
		secondFooList.PushBack(aFoo);

		secondFooList = mFooList;
		TS_ASSERT_EQUALS(secondFooList.Size(), mFooList.Size());

		while (!mFooList.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondFooList.Front(), mFooList.Front());
			secondFooList.PopFront();
			mFooList.PopFront();
		}

	}

	void TestIterator(void)
	{
		//Default Constructor
		SList<int>::Iterator* iterator = nullptr;
		iterator = new SList<int>::Iterator();
		TS_ASSERT_DIFFERS(iterator, nullptr);

		//Exceptions
		SList<int>::Iterator iterator2 = mIntList.begin();
		TS_ASSERT_THROWS_ANYTHING(*iterator2);
		TS_ASSERT_THROWS_ANYTHING(iterator2++);

		//Populate mIntList
		for (int i = 0; i < 5; i++)
		{
			mIntList.PushBack(i);
		}
		
		//Pre-Increment and Dereferencing
		int count = 0;
		for (auto it = mIntList.begin(); it != mIntList.end(); ++it)
		{
			TS_ASSERT_EQUALS(count, *it);
			count++;
		}
		TS_ASSERT_EQUALS(mIntList.Size(), count);

		//Post-Increment and Dereferencing
		count = 0;
		for (auto it = mIntList.begin(); it != mIntList.end(); it++)
		{
			TS_ASSERT_EQUALS(count, *it);
			count++;
		}

		//Assignment Operator
		SList<int>::Iterator iterator3;
		iterator3 = SList<int>::Iterator();

		iterator3 = iterator2;
		for (auto it = iterator2, it2 = iterator3; it != mIntList.end(); ++it, ++it2)
		{
			TS_ASSERT_EQUALS(*it, *it2);
		}

		//Copy Constructor
		SList<int>::Iterator iterator4 = iterator2;

		for (auto it = iterator2, it2 = iterator4; it != mIntList.end(); ++it, ++it2)
		{
			TS_ASSERT_EQUALS(*it, *it2);
		}

		delete iterator;

	}

	void TestFind(void)
	{
		for (int i = 0; i < 5; ++i)
		{
			mIntList.PushBack(i);
		}

		SList<int>::Iterator iterator = mIntList.Find(3);
		TS_ASSERT_EQUALS(*iterator, 3);

		iterator = mIntList.Find(7);
		TS_ASSERT_EQUALS(iterator,mIntList.end());
	}

	void TestInsertAfter(void)
	{
		//Inserting into an empty list
		SList<int>::Iterator iterator = mIntList.begin();
		mIntList.InsertAfter(iterator, 7);
		TS_ASSERT_EQUALS(mIntList.Front(), 7);

		for (int i = 0; i < 5; i++)
		{
			mIntList.PushBack(i);
		}

		SList<int>::Iterator iterator2 = mIntList.Find(3);
		mIntList.InsertAfter(iterator2, 13);
		iterator2++;
		TS_ASSERT_EQUALS(*iterator2, 13);

		mIntList.PushBack(77);

		iterator2 = mIntList.Find(77);
		mIntList.InsertAfter(iterator2, 15);
		iterator2++;
		TS_ASSERT_EQUALS(*iterator2, mIntList.Back());
	}


	void TestRemove(void)
	{
		mIntList.Remove(7);
		TS_ASSERT_EQUALS(mIntList.Size(), 0);

	    mIntList.PushFront(7);
		mIntList.Remove(7);
		TS_ASSERT_EQUALS(mIntList.Size(), 0);

		mIntList.PushBack(7);
		mIntList.PushBack(5);
		mIntList.PushBack(3);
		mIntList.PushBack(2);

		mIntList.Remove(5);
		TS_ASSERT_EQUALS(mIntList.Size(), 3);
		SList<int>::Iterator iterator = mIntList.Find(5);
		TS_ASSERT_EQUALS(iterator,mIntList.end());

		mIntList.Remove(2);
		TS_ASSERT_EQUALS(mIntList.Size(), 2);
		iterator = mIntList.Find(2);
		TS_ASSERT_EQUALS(iterator, mIntList.end());
		TS_ASSERT_EQUALS(mIntList.Back(), 3);
	}
	
private:
	SList<int> mIntList;
	SList<int*> mIntPointerList;
	SList<Foo> mFooList;

};