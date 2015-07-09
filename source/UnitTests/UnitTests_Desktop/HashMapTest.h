#include <cxxtest/TestSuite.h>
#include "Foo.h"
#include "HashMap.h"
#include "FooHashFunctor.h"

using namespace Library;
using namespace Unit_Tests;

class HashMapTestSuite : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 0);
		TS_ASSERT_EQUALS(mStringKeyHash.Size(), 0);
	}

	void tearDown()
	{
		mIntHashMap.Clear();
		mFooHashMap.Clear();
		mStringKeyHash.Clear();
	}

	void TestInitialization(void)
	{
		//Testing HashMap Iterator
		HashMap<int,int>::Iterator* it = nullptr;
		it = new HashMap<int,int>::Iterator();
		TS_ASSERT_DIFFERS(it, nullptr);
		delete it;

		//Testing Primitive Keys
		//Default Capacity
		HashMap<int, int>* intHashMap = nullptr;
		intHashMap = new HashMap<int, int>();
		TS_ASSERT_DIFFERS(intHashMap, nullptr);
		delete intHashMap;

		//Testing Primitive Keys
		HashMap<int*, int>* intPointerHashMap;
		intPointerHashMap = new HashMap<int*, int>();
		TS_ASSERT_DIFFERS(intPointerHashMap, nullptr);
		delete intPointerHashMap;
	}

	void TestFindAndInsert(void)
	{
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 0);

		//Testing for primitive types
		auto it = mIntHashMap.Find(5);
		TS_ASSERT_EQUALS(it, mIntHashMap.end());

		bool inserted;

		mIntHashMap.Insert(5, 1, inserted);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 1);
		mIntHashMap.Insert(7, 2, inserted);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);
		mIntHashMap.Insert(9, 3, inserted);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 3);

		it = mIntHashMap.Find(5);
		TS_ASSERT_EQUALS((*it).first, 5);
		TS_ASSERT_EQUALS((*it).second, 1);

		it = mIntHashMap.Find(7);
		TS_ASSERT_EQUALS((*it).first, 7);
		TS_ASSERT_EQUALS((*it).second, 2);

		it = mIntHashMap.Find(9);
		TS_ASSERT_EQUALS((*it).first, 9);
		TS_ASSERT_EQUALS((*it).second, 3);

		it = mIntHashMap.Find(67);
		TS_ASSERT_EQUALS(it, mIntHashMap.end());

		//Testing for User Defined Types
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 11;

		auto it3 = mFooHashMap.Find(foo1);
		TS_ASSERT_EQUALS(it3, mFooHashMap.end());

		mFooHashMap.Insert(foo1, 1, inserted);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 1);
		mFooHashMap.Insert(foo2, 2, inserted);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 2);
		mFooHashMap.Insert(foo3, 3, inserted);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 3);

		it3 = mFooHashMap.Find(foo1);
		TS_ASSERT_EQUALS((*it3).first, foo1);
		TS_ASSERT_EQUALS((*it3).second, 1);

		it3 = mFooHashMap.Find(foo2);
		TS_ASSERT_EQUALS((*it3).first, foo2);
		TS_ASSERT_EQUALS((*it3).second, 2);

		it3 = mFooHashMap.Find(foo3);
		TS_ASSERT_EQUALS((*it3).first, foo3);
		TS_ASSERT_EQUALS((*it3).second, 3);

		it3 = mFooHashMap.Find(67);
		TS_ASSERT_EQUALS(it, mIntHashMap.end());

		auto it4 = mStringKeyHash.Find("hello");
		TS_ASSERT_EQUALS(it4, mStringKeyHash.end());

		mStringKeyHash.Insert("hello", 5, inserted);
		it4 = mStringKeyHash.Find("hello");
		TS_ASSERT_EQUALS((*it4).second, 5);
	}

	void TestAssignmentOperator(void)
	{
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 0);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 0);

		bool inserted;

		//Testing Primitive Types
		mIntHashMap.Insert(1, 1, inserted);
		mIntHashMap.Insert(2, 2, inserted);
		mIntHashMap.Insert(3, 3, inserted);

		HashMap<int, int> secondIntHashMap;
		secondIntHashMap = mIntHashMap;

		TS_ASSERT_EQUALS(secondIntHashMap.Find(1)->first, 1);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), secondIntHashMap.Size());

		TS_ASSERT_EQUALS(secondIntHashMap.Find(2)->first, 2);
		TS_ASSERT_EQUALS(secondIntHashMap.Find(3)->first, 3);

		//User defined
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 11;

		mFooHashMap.Insert(foo1, 1, inserted);
		mFooHashMap.Insert(foo2, 2, inserted);
		mFooHashMap.Insert(foo3, 3, inserted);

		HashMap<Foo, int, FooHashFunctor> secondFooHashMap;
		secondFooHashMap = mFooHashMap;

		TS_ASSERT_EQUALS(secondFooHashMap.Find(foo1)->first, foo1);
		TS_ASSERT_EQUALS(mIntHashMap.Size(), secondIntHashMap.Size());

		TS_ASSERT_EQUALS(secondFooHashMap.Find(foo2)->first, foo2);
		TS_ASSERT_EQUALS(secondFooHashMap.Find(foo3)->first, foo3);

		//String
		mStringKeyHash.Insert("hello", 1, inserted);
		mStringKeyHash.Insert("a", 2, inserted);

		HashMap<std::string, int> stringHashMap;
		stringHashMap = mStringKeyHash;

		TS_ASSERT_EQUALS(stringHashMap.Find("hello")->first, "hello");
		TS_ASSERT_EQUALS(stringHashMap.Size(), mStringKeyHash.Size());

		TS_ASSERT_EQUALS(stringHashMap.Find("a")->first, "a");

	}

	void TestRemove(void)
	{
		bool inserted;
		mIntHashMap.Insert(5, 1, inserted);
		mIntHashMap.Insert(7, 2, inserted);
		mIntHashMap.Insert(9, 3, inserted);

		TS_ASSERT_EQUALS(mIntHashMap.Size(), 3);

		mIntHashMap.Remove(5);
		auto it = mIntHashMap.Find(5);
		TS_ASSERT_EQUALS(it, mIntHashMap.end());
		TS_ASSERT_EQUALS(mIntHashMap.Size(), 2);

		mIntHashMap.Remove(4);
		
		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 11;

		auto it3 = mFooHashMap.Find(foo1);
		TS_ASSERT_EQUALS(it3, mFooHashMap.end());

		mFooHashMap.Insert(foo1, 1, inserted);
		mFooHashMap.Insert(foo2, 2, inserted);
		mFooHashMap.Insert(foo3, 3, inserted);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 3);

		mFooHashMap.Remove(foo1);
		TS_ASSERT_EQUALS(mFooHashMap.Size(), 2);

		it3 = mFooHashMap.Find(foo1);
		TS_ASSERT_EQUALS(it3, mFooHashMap.end());

		mStringKeyHash.Insert("hello", 1, inserted);
		mStringKeyHash.Insert("a", 2, inserted);

		TS_ASSERT_EQUALS(mStringKeyHash.Size(), 2);

		mStringKeyHash.Remove("hello");
		TS_ASSERT_EQUALS(mStringKeyHash.Size(), 1);

		auto it4 = mStringKeyHash.Find("hello");
		TS_ASSERT_EQUALS(it4, mStringKeyHash.end());


	}

	void TestContainsKey(void)
	{
		bool inserted;
		mIntHashMap.Insert(5, 1, inserted);
		mIntHashMap.Insert(7, 2, inserted);
		mIntHashMap.Insert(9, 3, inserted);

		TS_ASSERT(mIntHashMap.ContainsKey(5));
		TS_ASSERT(mIntHashMap.ContainsKey(7));
		TS_ASSERT(mIntHashMap.ContainsKey(9));
		TS_ASSERT_EQUALS(mIntHashMap.ContainsKey(55),false);

		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 11;
		Foo foo4;
		foo4.mData = 8;

		mFooHashMap.Insert(foo1, 1, inserted);
		mFooHashMap.Insert(foo2, 2, inserted);
		mFooHashMap.Insert(foo3, 3, inserted);

		TS_ASSERT(mFooHashMap.ContainsKey(foo1));
		TS_ASSERT(mFooHashMap.ContainsKey(foo2));
		TS_ASSERT(mFooHashMap.ContainsKey(foo3));
		TS_ASSERT_EQUALS(mFooHashMap.ContainsKey(foo4), false);

		mStringKeyHash.Insert("hello", 1, inserted);
		mStringKeyHash.Insert("a", 2, inserted);
		TS_ASSERT(mStringKeyHash.ContainsKey("hello"));
		TS_ASSERT(mStringKeyHash.ContainsKey("a"));
		TS_ASSERT_EQUALS(mStringKeyHash.ContainsKey("b"), false);
	}

	void TestIterator(void)
	{
		bool inserted;

		mIntHashMap.Insert(5, 1, inserted);
		mIntHashMap.Insert(7, 2, inserted);
		mIntHashMap.Insert(9, 3, inserted);

		auto it = mIntHashMap.begin();
		int i = 0;
		for (; it != mIntHashMap.end(); ++it)
		{
			i++;
		}

		TS_ASSERT_EQUALS(mIntHashMap.Size(), i);

		Foo foo1;
		foo1.mData = 7;
		Foo foo2;
		foo2.mData = 9;
		Foo foo3;
		foo3.mData = 11;

		mFooHashMap.Insert(foo1, 1, inserted);
		mFooHashMap.Insert(foo2, 2, inserted);
		mFooHashMap.Insert(foo3, 3, inserted);

		auto it2 = mFooHashMap.begin();
		i = 0;
		for (; it2 != mFooHashMap.end(); ++it2)
		{
			i++;
		}
		TS_ASSERT_EQUALS(mFooHashMap.Size(), i);

		mStringKeyHash.Insert("hello", 1, inserted);
		mStringKeyHash.Insert("a", 2, inserted);

		auto it3 = mStringKeyHash.begin();
		i = 0;
		for (; it3 != mStringKeyHash.end(); ++it3)
		{
			i++;
		}
		TS_ASSERT_EQUALS(mStringKeyHash.Size(), i);
	}

private:
	HashMap<int, int> mIntHashMap;
	HashMap<Foo, int, FooHashFunctor> mFooHashMap;
	HashMap<std::string, int> mStringKeyHash;
};
