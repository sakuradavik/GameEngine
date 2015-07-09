#include "AttributedFoo.h"
#include "Foo.h"

using namespace Unit_Tests;

RTTI_DEFINITIONS(AttributedFoo)

AttributedFoo::AttributedFoo() :
Attribute(), mExternalInteger(7), mExternalFloat(7.0f), mExternalVector(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f)), mExternalMatrix(glm::mat4(7.0f)), mExternalString("Hi"), mExternalTable(nullptr), mExternalRTTI(nullptr)
{
	bool inserted;
	Vector<Signature> mVector;
	auto& signatureVector = mSignatures.Insert(TypeIdClass(), mVector, inserted)->second;
	int size = 2;

	if (!inserted)
	{
		std::uint32_t size = signatureVector.Size();
		signatureVector.Clear();
		signatureVector.Reserve(size);
	}

	signatureVector.PushBack(Signature("InternalInteger", Datum::DatumType::Integer, &mExternalInteger, size, nullptr));
	signatureVector.PushBack(Signature("InternalFloat", Datum::DatumType::Float, &mExternalFloat, size, nullptr));
	signatureVector.PushBack(Signature("InternalVector", Datum::DatumType::Vector, &mExternalVector, size, nullptr));
	signatureVector.PushBack(Signature("InternalMatrix", Datum::DatumType::Matrix, &mExternalMatrix, size, nullptr));
	signatureVector.PushBack(Signature("InternalString", Datum::DatumType::String, &mExternalString, size, nullptr));
	signatureVector.PushBack(Signature("InternalRTTI", Datum::DatumType::Pointer, &mExternalTable, size, nullptr));
	signatureVector.PushBack(Signature("InternalScope", Datum::DatumType::Table, &mExternalRTTI, size, nullptr));

	signatureVector.PushBack(Signature("ExternalInteger", Datum::DatumType::Integer, nullptr, size, &mExternalInteger));
	signatureVector.PushBack(Signature("ExternalFloat", Datum::DatumType::Float, nullptr, size, &mExternalFloat));
	signatureVector.PushBack(Signature("ExternalVector", Datum::DatumType::Vector, nullptr, size, &mExternalVector));
	signatureVector.PushBack(Signature("ExternalMatrix", Datum::DatumType::Matrix, nullptr, size, &mExternalMatrix));
	signatureVector.PushBack(Signature("ExternalString", Datum::DatumType::String, nullptr, size, &mExternalString));
	signatureVector.PushBack(Signature("ExternalRTTI", Datum::DatumType::Pointer, nullptr, size, &mExternalRTTI));

	Populate();
}


AttributedFoo::~AttributedFoo()
{

}
