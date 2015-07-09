#include <cxxtest/TestSuite.h>
#include "Datum.h"
#include "Foo.h"

using namespace Library;
using namespace Unit_Tests;

class DatumTestSuite : public CxxTest::TestSuite
{
public:
	void TestIntDatum()
	{
		TS_ASSERT_THROWS_ANYTHING(mIntDatum.SetSize(5));
		TS_ASSERT_EQUALS(mIntDatum.GetType(), Datum::DatumType::Unknown);
		mIntDatum.SetType(Datum::DatumType::Integer);

		mIntDatum.Set(7, 0);
		TS_ASSERT_EQUALS(mIntDatum.Size(), 1);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(0), 7);

		TS_ASSERT_THROWS_ANYTHING(mIntDatum.SetType(Datum::DatumType::String));

		mIntDatum.Set(9, 1);
		TS_ASSERT_EQUALS(mIntDatum.Size(), 2);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(1), 9);

		mIntDatum.SetSize(11);
		TS_ASSERT_EQUALS(mIntDatum.Size(), 11);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(0), 7);

		mIntDatum.SetFromString("555", 0);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(), 555);

		mIntDatum.SetSize(5);
		TS_ASSERT_EQUALS(mIntDatum.Size(), 5);

		mIntDatum.Set(8, 2);
		TS_ASSERT_EQUALS(mIntDatum.Size(), 5);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(2), 8);

		mIntDatum.Set(8, 7);
		TS_ASSERT_EQUALS(mIntDatum.Size(), 8);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(7), 8);

		std::int32_t a = 5;
		TS_ASSERT_THROWS_ANYTHING(mIntDatum.SetStorage(&a, 0));

		mIntDatum = 5;
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(), 5);
		TS_ASSERT_EQUALS((mIntDatum == 5), true);
		TS_ASSERT_EQUALS(mIntDatum.ToString(), "5");

		mIntDatum.Clear();
		TS_ASSERT_EQUALS(mIntDatum.Size(), 0);

		std::int32_t b = 4;
		std::int32_t c = 6;
		std::int32_t d[] = { a, b, c };
		
		mIntDatum.SetStorage(d,3);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(), a);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(1), b);
		TS_ASSERT_EQUALS(mIntDatum.GetInteger(2), c);
		TS_ASSERT_EQUALS(mIntDatum.Size(), 3);
		TS_ASSERT_THROWS_ANYTHING(mIntDatum.SetSize(7));

		Datum datum = mIntDatum;
		TS_ASSERT_EQUALS(datum.Size(), mIntDatum.Size());
		TS_ASSERT_EQUALS(datum.GetInteger(), mIntDatum.GetInteger());
		TS_ASSERT_EQUALS(datum.GetInteger(1), mIntDatum.GetInteger(1));
		TS_ASSERT_EQUALS(datum.GetInteger(2), mIntDatum.GetInteger(2));
		TS_ASSERT_EQUALS((datum == mIntDatum), true);

	}

	void TestFloatDatum()
	{
		TS_ASSERT_THROWS_ANYTHING(mFloatDatum.SetSize(5));
		TS_ASSERT_EQUALS(mFloatDatum.GetType(), Datum::DatumType::Unknown);
		mFloatDatum.SetType(Datum::DatumType::Float);

		mFloatDatum.Set(7.0f, 0);
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 1);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(0), 7.0f);

		TS_ASSERT_THROWS_ANYTHING(mFloatDatum.SetType(Datum::DatumType::String));

		mFloatDatum.Set(9.0f, 1);
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 2);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(1), 9.0f);

		mFloatDatum.SetSize(11);
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 11);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(), 7.0f);

		mFloatDatum.SetFromString("555.0f", 0);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(), 555.0f);

		mFloatDatum.SetSize(5);
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 5);

		mFloatDatum.Set(8.0f, 2);
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 5);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(2), 8.0f);

		mFloatDatum.Set(8.0f, 7);
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 8);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(7), 8.0f);

		std::float_t a = 5.0f;
		TS_ASSERT_THROWS_ANYTHING(mFloatDatum.SetStorage(&a, 0));

		mFloatDatum = 5.0f;
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(), 5.0f);
		TS_ASSERT_EQUALS((mFloatDatum == 5.0f), true);
		TS_ASSERT_EQUALS(mFloatDatum.ToString(), "5.000000");

		mFloatDatum.Clear();
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 0);

		std::float_t b = 4.0f;
		std::float_t c = 6.0f;
		std::float_t d[] = { a, b, c };

		mFloatDatum.SetStorage(d, 3);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(), a);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(1), b);
		TS_ASSERT_EQUALS(mFloatDatum.GetFloat(2), c);
		TS_ASSERT_EQUALS(mFloatDatum.Size(), 3);
		TS_ASSERT_THROWS_ANYTHING(mFloatDatum.SetSize(7));

		Datum datum = mFloatDatum;
		TS_ASSERT_EQUALS(datum.Size(), mFloatDatum.Size());
		TS_ASSERT_EQUALS(datum.GetFloat(), mFloatDatum.GetFloat());
		TS_ASSERT_EQUALS(datum.GetFloat(1), mFloatDatum.GetFloat(1));
		TS_ASSERT_EQUALS(datum.GetFloat(2), mFloatDatum.GetFloat(2));
		TS_ASSERT_EQUALS((datum == mFloatDatum), true);
	}

	void TestVectorDatum()
	{
		TS_ASSERT_THROWS_ANYTHING(mVectorDatum.SetSize(5));
		TS_ASSERT_EQUALS(mVectorDatum.GetType(), Datum::DatumType::Unknown);
		mVectorDatum.SetType(Datum::DatumType::Vector);

		glm::vec4 v = glm::vec4(1.0f, 3.0f, 5.0f, 7.0f);
		glm::vec4 v2 = glm::vec4(11.0f, 13.0f, 15.0f, 17.0f);
		glm::vec4 v3 = glm::vec4(111.0f, 113.0f, 115.0f, 117.0f);

		mVectorDatum.Set(v, 0);
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 1);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(0), v);

		TS_ASSERT_THROWS_ANYTHING(mVectorDatum.SetType(Datum::DatumType::String));

		mVectorDatum.Set(v2, 1);
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 2);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(1),v2);

		mVectorDatum.SetSize(11);
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 11);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(), v);

		mVectorDatum.SetSize(5);
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 5);

		mVectorDatum.Set(v3, 2);
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 5);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(2), v3);

		mVectorDatum.Set(v3, 7);
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 8);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(7), v3);

		TS_ASSERT_THROWS_ANYTHING(mVectorDatum.SetStorage(&v, 0));

		mVectorDatum = v2;
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(), v2);
		TS_ASSERT_EQUALS((mVectorDatum == v2), true);
		TS_ASSERT_EQUALS(mVectorDatum.ToString(), glm::to_string(v2));

		mVectorDatum.Clear();
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 0);

		glm::vec4 d[] = { v2, v3, v };

		mVectorDatum.SetStorage(d, 3);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(), v2);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(1), v3);
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(2), v);
		TS_ASSERT_EQUALS(mVectorDatum.Size(), 3);
		TS_ASSERT_THROWS_ANYTHING(mVectorDatum.SetSize(7));


		Datum datum = mVectorDatum;
		TS_ASSERT_EQUALS(datum.Size(), mVectorDatum.Size());
		TS_ASSERT_EQUALS(datum.GetVector(), mVectorDatum.GetVector());
		TS_ASSERT_EQUALS(datum.GetVector(1), mVectorDatum.GetVector(1));
		TS_ASSERT_EQUALS(datum.GetVector(2), mVectorDatum.GetVector(2));
		TS_ASSERT_EQUALS((datum == mVectorDatum), true);

		mVectorDatum.SetFromString("11.0, 13.0, 15.0, 17.0");
		TS_ASSERT_EQUALS(mVectorDatum.GetVector(), v2);
	}

	void TestMatrixDatum()
	{
		TS_ASSERT_THROWS_ANYTHING(mMatrixDatum.SetSize(5));
		TS_ASSERT_EQUALS(mMatrixDatum.GetType(), Datum::DatumType::Unknown);
		mMatrixDatum.SetType(Datum::DatumType::Matrix);

		glm::mat4 v = glm::mat4(1.0f);
		glm::mat4 v2 = glm::mat4(11.0f);
		glm::mat4 v3 = glm::mat4(111.0f);

		mMatrixDatum.Set(v, 0);
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 1);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(0), v);

		TS_ASSERT_THROWS_ANYTHING(mMatrixDatum.SetType(Datum::DatumType::String));

		mMatrixDatum.Set(v2, 1);
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 2);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(1), v2);

		mMatrixDatum.SetSize(11);
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 11);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(), v);

		mMatrixDatum.SetSize(5);
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 5);

		mMatrixDatum.Set(v3, 2);
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 5);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(2), v3);

		mMatrixDatum.Set(v3, 7);
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 8);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(7), v3);

		TS_ASSERT_THROWS_ANYTHING(mMatrixDatum.SetStorage(&v, 0));

		mMatrixDatum = v2;
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(), v2);
		TS_ASSERT_EQUALS((mMatrixDatum == v2), true);
		TS_ASSERT_EQUALS(mMatrixDatum.ToString(), glm::to_string(v2));

		mMatrixDatum.Clear();
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 0);

		glm::mat4 d[] = { v2, v3, v };

		mMatrixDatum.SetStorage(d, 3);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(), v2);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(1), v3);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(2), v);
		TS_ASSERT_EQUALS(mMatrixDatum.Size(), 3);
		TS_ASSERT_THROWS_ANYTHING(mMatrixDatum.SetSize(7));


		Datum datum = mMatrixDatum;
		TS_ASSERT_EQUALS(datum.Size(), mMatrixDatum.Size());
		TS_ASSERT_EQUALS(datum.GetMatrix(), mMatrixDatum.GetMatrix());
		TS_ASSERT_EQUALS(datum.GetMatrix(1), mMatrixDatum.GetMatrix(1));
		TS_ASSERT_EQUALS(datum.GetMatrix(2), mMatrixDatum.GetMatrix(2));
		TS_ASSERT_EQUALS((datum == mMatrixDatum), true);

		mMatrixDatum.SetFromString("5.0", 0);
		TS_ASSERT_EQUALS(mMatrixDatum.GetMatrix(), glm::mat4(5.0f));
	}

	void TestStringDatum()
	{
		TS_ASSERT_THROWS_ANYTHING(mStringDatum.SetSize(5));
		TS_ASSERT_EQUALS(mStringDatum.GetType(), Datum::DatumType::Unknown);
		mStringDatum.SetType(Datum::DatumType::String);

		std::string v = "a";
		std::string v2 = "b";
		std::string v3 = "c";

		mStringDatum.Set(v, 0);
		TS_ASSERT_EQUALS(mStringDatum.Size(), 1);
		TS_ASSERT_EQUALS(mStringDatum.GetString(0), v);

		TS_ASSERT_THROWS_ANYTHING(mStringDatum.SetType(Datum::DatumType::String));

		mStringDatum.Set(v2, 1);
		TS_ASSERT_EQUALS(mStringDatum.Size(), 2);
		TS_ASSERT_EQUALS(mStringDatum.GetString(1), v2);

		mStringDatum.SetSize(11);
		TS_ASSERT_EQUALS(mStringDatum.Size(), 11);
		TS_ASSERT_EQUALS(mStringDatum.GetString(), v);

		mStringDatum.SetSize(5);
		TS_ASSERT_EQUALS(mStringDatum.Size(), 5);

		mStringDatum.Set(v3, 2);
		TS_ASSERT_EQUALS(mStringDatum.Size(), 5);
		TS_ASSERT_EQUALS(mStringDatum.GetString(2), v3);

		mStringDatum.Set(v3, 7);
		TS_ASSERT_EQUALS(mStringDatum.Size(), 8);
		TS_ASSERT_EQUALS(mStringDatum.GetString(7), v3);

		TS_ASSERT_THROWS_ANYTHING(mStringDatum.SetStorage(&v, 0));

		mStringDatum = v2;
		TS_ASSERT_EQUALS(mStringDatum.GetString(), v2);
		TS_ASSERT_EQUALS((mStringDatum == v2), true);
		TS_ASSERT_EQUALS(mStringDatum.ToString(), v2);

		mStringDatum.Clear();
		TS_ASSERT_EQUALS(mStringDatum.Size(), 0);

		std::string d[] = { v2, v3, v };

		mStringDatum.SetStorage(d, 3);
		TS_ASSERT_EQUALS(mStringDatum.GetString(), v2);
		TS_ASSERT_EQUALS(mStringDatum.GetString(1), v3);
		TS_ASSERT_EQUALS(mStringDatum.GetString(2), v);
		TS_ASSERT_EQUALS(mStringDatum.Size(), 3);
		TS_ASSERT_THROWS_ANYTHING(mStringDatum.SetSize(7));


		Datum datum = mStringDatum;
		TS_ASSERT_EQUALS(datum.Size(), mStringDatum.Size());
		TS_ASSERT_EQUALS(datum.GetString(), mStringDatum.GetString());
		TS_ASSERT_EQUALS(datum.GetString(1), mStringDatum.GetString(1));
		TS_ASSERT_EQUALS(datum.GetString(2), mStringDatum.GetString(2));
		TS_ASSERT_EQUALS((datum == mStringDatum), true);
	}

	void TestRTTIDatum()
	{
		TS_ASSERT_THROWS_ANYTHING(mRTTIDatum.SetSize(5));
		TS_ASSERT_EQUALS(mRTTIDatum.GetType(), Datum::DatumType::Unknown);
		mRTTIDatum.SetType(Datum::DatumType::Pointer);

		RTTI *v = new Foo();
		RTTI *v2 = new Foo();
		RTTI *v3 = new Foo();

		mRTTIDatum.Set(v, 0);
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 1);

		TS_ASSERT_THROWS_ANYTHING(mRTTIDatum.SetType(Datum::DatumType::String));

		mRTTIDatum.Set(v2, 1);
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 2);

		mRTTIDatum.SetSize(11);
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 11);

		mRTTIDatum.SetSize(5);
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 5);

		mRTTIDatum.Set(v3, 2);
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 5);

		mRTTIDatum.Set(v3, 7);
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 8);

		TS_ASSERT_THROWS_ANYTHING(mRTTIDatum.SetStorage(&v, 0));

		mRTTIDatum = v2;
		TS_ASSERT_EQUALS((mRTTIDatum == v2), true);

		mRTTIDatum.Clear();
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 0);

		RTTI* d[] = { v2, v3, v };

		mRTTIDatum.SetStorage(d, 3);
		TS_ASSERT_EQUALS(mRTTIDatum.Size(), 3);
		TS_ASSERT_THROWS_ANYTHING(mRTTIDatum.SetSize(7));

		TS_ASSERT_EQUALS((mRTTIDatum != v3), true);

		Datum datum = mRTTIDatum;
		TS_ASSERT_EQUALS(datum.Size(), mRTTIDatum.Size());
		TS_ASSERT_EQUALS((datum == mRTTIDatum), true);

		delete (Foo*)v;
		delete (Foo*)v2;
		delete (Foo*)v3;
		
	}

private:
	Datum mIntDatum;
	Datum mFloatDatum;
	Datum mVectorDatum;
	Datum mMatrixDatum;
	Datum mStringDatum;
	Datum mRTTIDatum;
};