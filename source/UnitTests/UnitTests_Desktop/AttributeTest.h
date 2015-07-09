#include <cxxtest/TestSuite.h>
#include "AttributedFoo.h"

using namespace Unit_Tests;

class AttributedFooTestSuite : public CxxTest::TestSuite
{
public:

	void setUp()
	{
		mAttributeFoo = new AttributedFoo();
	}

	void tearDown()
	{
		delete mAttributeFoo;
		mAttributeFoo = nullptr;
	}

	void TestIsPrescribedAttribute(void)
	{
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("InternalInteger"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("InternalFloat"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("InternalVector"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("InternalMatrix"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("InternalString"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("InternalRTTI"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("InternalScope"));

		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("ExternalInteger"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("ExternalFloat"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("ExternalVector"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("ExternalMatrix"));
		TS_ASSERT(mAttributeFoo->IsPrescribedAttribute("ExternalString"));


		TS_ASSERT(!mAttributeFoo->IsPrescribedAttribute("BTT"));
	}

	void TestPopulate(void)
	{
		//Testing that Populate populated my internals and externals correctly

		Datum * d = mAttributeFoo->Find("InternalInteger");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetInteger(0), 7);
		TS_ASSERT_EQUALS(d->GetInteger(1), 7);

		d = mAttributeFoo->Find("InternalFloat");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetFloat(0), 7.0f);
		TS_ASSERT_EQUALS(d->GetFloat(1), 7.0f);

		d = mAttributeFoo->Find("InternalVector");
		glm::vec4 v = glm::vec4(1.0f, 2.0f, 3.0f, 4.0f);
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetVector(0) == v, true);
		TS_ASSERT_EQUALS(d->GetVector(1), v);

		d = mAttributeFoo->Find("InternalMatrix");
		glm::mat4 m = glm::mat4(7.0f);
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetMatrix(0), m);

		d = mAttributeFoo->Find("InternalString");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetString(0), "Hi");
		TS_ASSERT_EQUALS(d->GetString(1), "Hi");

		d = mAttributeFoo->Find("InternalRTTI");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetRTTI(0), nullptr);
		TS_ASSERT_EQUALS(d->GetRTTI(1), nullptr);

		d = mAttributeFoo->Find("InternalScope");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(d->GetScope(0), nullptr);

		////External
		d = mAttributeFoo->Find("ExternalInteger");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(&(d->GetInteger()), &(mAttributeFoo->mExternalInteger));

		d = mAttributeFoo->Find("ExternalFloat");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(&(d->GetFloat()), &(mAttributeFoo->mExternalFloat));

		d = mAttributeFoo->Find("ExternalVector");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(&(d->GetVector()), &(mAttributeFoo->mExternalVector));

		d = mAttributeFoo->Find("ExternalMatrix");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(&(d->GetMatrix()), &(mAttributeFoo->mExternalMatrix));

		d = mAttributeFoo->Find("ExternalString");
		TS_ASSERT_EQUALS(d->Size(), 2);
		TS_ASSERT_EQUALS(&(d->GetString()), &(mAttributeFoo->mExternalString));

		d = mAttributeFoo->Find("ExternalRTTI");
		TS_ASSERT_EQUALS(d->Size(), 2);
	}

	void TestAuxiliiaryAttribute(void)
	{
		Datum& d = mAttributeFoo->AppendAuxiliaryAttribute("hello");
		d.SetType(Datum::DatumType::Integer);

		TS_ASSERT(mAttributeFoo->IsAttribute("hello"));
		TS_ASSERT(mAttributeFoo->IsAuxiliaryAttribute("hello"));
		TS_ASSERT(!mAttributeFoo->IsPrescribedAttribute("hello"));

		TS_ASSERT_THROWS_ANYTHING(mAttributeFoo->AppendAuxiliaryAttribute("InternalInteger"));
		TS_ASSERT(!mAttributeFoo->IsAuxiliaryAttribute("InternalInteger"));

		AttributedFoo foo = AttributedFoo();
		TS_ASSERT(!foo.IsAttribute("hello"));
	}

	void TestAttribute(void)
	{
		TS_ASSERT(mAttributeFoo->IsAttribute("InternalInteger"));
		TS_ASSERT(mAttributeFoo->IsAttribute("InternalFloat"));
		TS_ASSERT(mAttributeFoo->IsAttribute("InternalVector"));
		TS_ASSERT(mAttributeFoo->IsAttribute("InternalMatrix"));
		TS_ASSERT(mAttributeFoo->IsAttribute("InternalString"));

		TS_ASSERT(mAttributeFoo->IsAttribute("ExternalInteger"));
		TS_ASSERT(mAttributeFoo->IsAttribute("ExternalFloat"));
		TS_ASSERT(mAttributeFoo->IsAttribute("ExternalVector"));
		TS_ASSERT(mAttributeFoo->IsAttribute("ExternalMatrix"));
		TS_ASSERT(mAttributeFoo->IsAttribute("ExternalString"));

		Datum& d = mAttributeFoo->AppendAuxiliaryAttribute("hello");
		d.SetType(Datum::DatumType::Integer);

		TS_ASSERT(mAttributeFoo->IsAttribute("hello"));
	}

	void TestAuxiliaryBegin(void)
	{
		TS_ASSERT(mAttributeFoo->AuxiliaryBegin() == 14);

	}

	void TestAssignmentOperator(void)
	{
		/*AttributedFoo foo;

		Datum* d = mAttributeFoo->Find("InternalString");
		d->Set("hello");

		foo = *mAttributeFoo;
		Datum * d2 = foo.Find("InternalString");
		TS_ASSERT(d2->GetString() == "hello");*/
	}

	void TestCopyConstructor(void)
	{
	/*	AttributedFoo foo = *mAttributeFoo;

		Datum* d = mAttributeFoo->Find("InternalString");
		d->Set("hello");

		Datum * d2 = foo.Find("InternalString");
		TS_ASSERT(d2->GetString() != "hello");*/

	}

private:
	AttributedFoo * mAttributeFoo;

};