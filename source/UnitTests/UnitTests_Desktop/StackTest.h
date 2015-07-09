#include <cxxtest/TestSuite.h>
#include "Stack.h"
#include "Foo.h"

using namespace Library;
using namespace Unit_Tests;

class StackTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{

	}

	void tearDown()
	{
		mIntStack.Clear();
		mIntPointerStack.Clear();
		mFooStack.Clear();
	}

	void TestStackInitialization(void)
	{
		//Testing Stacks to see if they are empty
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		//Testing Primitive Types
		Stack<int>* intStack = nullptr;
		intStack = new Stack<int>();
		TS_ASSERT_DIFFERS(intStack, nullptr);
		delete intStack;

		//Testing Pointer Types
		Stack<int*>* intPointerStack;
		intPointerStack = nullptr;
		intPointerStack = new Stack<int*>();
		TS_ASSERT_DIFFERS(intPointerStack, nullptr);
		delete intPointerStack;

		//Testing User Defined types
		Stack<Foo>* fooStack;
		fooStack = nullptr;
		fooStack = new Stack<Foo>();
		TS_ASSERT_DIFFERS(fooStack, nullptr);
		delete fooStack;
	}

	void TestCopyConstructor(void)
	{
		//Testing Stacks to see if they are empty
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		//Testing Primitive Types
		mIntStack.Push(7);
		mIntStack.Push(5);
		mIntStack.Push(3);
		mIntStack.Push(1);

		Stack<int> secondIntStack = mIntStack;
		TS_ASSERT_EQUALS(secondIntStack.Size(), mIntStack.Size());

		while (!mIntStack.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntStack.Top(), mIntStack.Top());
			secondIntStack.Pop();
			mIntStack.Pop();
		}

		//Testing Pointers
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerStack.Push(&a);
		mIntPointerStack.Push(&b);
		mIntPointerStack.Push(&c);

		Stack<int*> secondIntPointerStack = mIntPointerStack;
		TS_ASSERT_EQUALS(secondIntPointerStack.Size(), mIntPointerStack.Size());

		while (!mIntPointerStack.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntPointerStack.Top(), mIntPointerStack.Top());
			secondIntPointerStack.Pop();
			mIntPointerStack.Pop();
		}

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooStack.Push(aFoo);
		mFooStack.Push(bFoo);
		mFooStack.Push(cFoo);

		Stack<Foo> secondFooStack = mFooStack;
		TS_ASSERT_EQUALS(secondFooStack.Size(), mFooStack.Size());

		while (!mFooStack.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondFooStack.Top(), mFooStack.Top());
			secondFooStack.Pop();
			mFooStack.Pop();
		}
	}

	void TestEqualOperator(void)
	{
		//Testing Stacks to see if they are empty
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		//Testing Primitive Types
		mIntStack.Push(7);
		mIntStack.Push(5);
		mIntStack.Push(3);
		mIntStack.Push(1);

		Stack<int> secondIntStack;
		secondIntStack.Push(3);
		secondIntStack.Push(5);

		secondIntStack = mIntStack;
		TS_ASSERT_EQUALS(secondIntStack.Size(), mIntStack.Size());

		while (!mIntStack.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntStack.Top(), mIntStack.Top());
			secondIntStack.Pop();
			mIntStack.Pop();
		}

		//Testing Pointers
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerStack.Push(&a);
		mIntPointerStack.Push(&b);
		mIntPointerStack.Push(&c);

		Stack<int*> secondIntPointerStack;
		secondIntPointerStack.Push(&a);

		secondIntPointerStack = mIntPointerStack;
		TS_ASSERT_EQUALS(secondIntPointerStack.Size(), mIntPointerStack.Size());

		while (!mIntPointerStack.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondIntPointerStack.Top(), mIntPointerStack.Top());
			secondIntPointerStack.Pop();
			mIntPointerStack.Pop();
		}

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooStack.Push(aFoo);
		mFooStack.Push(bFoo);
		mFooStack.Push(cFoo);

		Stack<Foo> secondFooStack;
		secondFooStack.Push(aFoo);

		secondFooStack = mFooStack;
		TS_ASSERT_EQUALS(secondFooStack.Size(), mFooStack.Size());

		while (!mFooStack.IsEmpty())
		{
			TS_ASSERT_EQUALS(secondFooStack.Top(), mFooStack.Top());
			secondFooStack.Pop();
			mFooStack.Pop();
		}
	}

	void TestPush(void)
	{
		//Testing Stacks to see if they are empty
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		//Testing Primitive Types
		mIntStack.Push(7);
		TS_ASSERT_EQUALS(mIntStack.Size(), 1);

		mIntStack.Push(13);
		TS_ASSERT_EQUALS(mIntStack.Size(), 2);
		TS_ASSERT_EQUALS(mIntStack.Top(), 13);

		mIntStack.Push(11);
		TS_ASSERT_EQUALS(mIntStack.Size(), 3);
		TS_ASSERT_EQUALS(mIntStack.Top(), 11);

		//Testing Pointers
		int a = 1;
		int b = 3;
		int c = 5;

		mIntPointerStack.Push(&a);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 1);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &a);

		mIntPointerStack.Push(&b);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 2);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &b);

		mIntPointerStack.Push(&c);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 3);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &c);

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooStack.Push(aFoo);
		TS_ASSERT_EQUALS(mFooStack.Size(), 1);
		TS_ASSERT_EQUALS(mFooStack.Top(), aFoo);

		mFooStack.Push(bFoo);
		TS_ASSERT_EQUALS(mFooStack.Size(), 2);
		TS_ASSERT_EQUALS(mFooStack.Top(), bFoo);

		mFooStack.Push(cFoo);
		TS_ASSERT_EQUALS(mFooStack.Size(), 3);
		TS_ASSERT_EQUALS(mFooStack.Top(), cFoo);
	}

	void TestPop(void)
	{
		//Testing Stacks to see if they are empty
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		
		mIntStack.Push(7);
		mIntStack.Push(5);
		mIntStack.Push(3);

		TS_ASSERT_EQUALS(mIntStack.Size(), 3);

		mIntStack.Pop();
		TS_ASSERT_EQUALS(mIntStack.Top(), 5);
		TS_ASSERT_EQUALS(mIntStack.Size(), 2);

		mIntStack.Pop();
		TS_ASSERT_EQUALS(mIntStack.Top(), 7);
		TS_ASSERT_EQUALS(mIntStack.Size(), 1);

		//Testing Primitive Types
		int a = 1;
		int b = 2;
		int c = 3;

		mIntPointerStack.Push(&a);
		mIntPointerStack.Push(&b);
		mIntPointerStack.Push(&c);

		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 3);

		mIntPointerStack.Pop();
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &b);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 2);

		mIntPointerStack.Pop();
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &a);
		TS_ASSERT_EQUALS(mIntPointerStack.Size(), 1);

		//Testing User Defined Type
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		mFooStack.Push(aFoo);
		mFooStack.Push(bFoo);
		mFooStack.Push(cFoo);

		TS_ASSERT_EQUALS(mFooStack.Size(), 3);

		mFooStack.Pop();
		TS_ASSERT_EQUALS(mFooStack.Top(), bFoo);
		TS_ASSERT_EQUALS(mFooStack.Size(), 2);

		mFooStack.Pop();
		TS_ASSERT_EQUALS(mFooStack.Top(), aFoo);
		TS_ASSERT_EQUALS(mFooStack.Size(), 1);
	}

	void TestTop(void)
	{
		//Testing Stacks to see if they are empty
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		//Testing Primitive Types
		TS_ASSERT_THROWS_ANYTHING(mIntStack.Top());

		mIntStack.Push(7);
		TS_ASSERT_EQUALS(mIntStack.Top(), 7);

		mIntStack.Push(5);
		TS_ASSERT_EQUALS(mIntStack.Top(), 5);

		mIntStack.Push(3);
		TS_ASSERT_EQUALS(mIntStack.Top(), 3);

		mIntStack.Push(1);
		TS_ASSERT_EQUALS(mIntStack.Top(), 1);

		//Testing Pointers
		int a = 1;
		int b = 3;
		int c = 5;

		TS_ASSERT_THROWS_ANYTHING(mIntPointerStack.Top());

		mIntPointerStack.Push(&a);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &a);

		mIntPointerStack.Push(&b);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &b);

		mIntPointerStack.Push(&c);
		TS_ASSERT_EQUALS(mIntPointerStack.Top(), &c);

		//Testing User Defined Types
		Foo aFoo;
		aFoo.mData = 1;
		Foo bFoo;
		bFoo.mData = 2;
		Foo cFoo;
		cFoo.mData = 3;

		TS_ASSERT_THROWS_ANYTHING(mFooStack.Top());

		mFooStack.Push(aFoo);
		TS_ASSERT_EQUALS(mFooStack.Top(), aFoo);

		mFooStack.Push(bFoo);
		TS_ASSERT_EQUALS(mFooStack.Top(), bFoo);

		mFooStack.Push(cFoo);
		TS_ASSERT_EQUALS(mFooStack.Top(), cFoo);
	}

	void TestClear()
	{
		//Testing Stacks to see if they are empty
		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());

		int a = 0;
		mIntStack.Push(a);
		mIntPointerStack.Push(&a);
		Foo aFoo;
		aFoo.mData = 0;
		mFooStack.Push(aFoo);

		mIntStack.Clear();
		mIntPointerStack.Clear();
		mFooStack.Clear();

		TS_ASSERT(mIntStack.IsEmpty());
		TS_ASSERT(mIntPointerStack.IsEmpty());
		TS_ASSERT(mFooStack.IsEmpty());
	}

private:
	Stack<int> mIntStack;
	Stack<int*> mIntPointerStack;
	Stack<Foo> mFooStack;
};