#include "pch.h"
#include "Attribute.h"

using namespace Library;

RTTI_DEFINITIONS(Attribute)

HashMap<std::uint32_t, Vector<Attribute::Signature>> Attribute::mSignatures = HashMap<std::uint32_t, Vector<Attribute::Signature>>();

#pragma region Attribute

Attribute::Attribute() :
Scope()
{
	Append("this") = (RTTI*)this;
}

Attribute::Attribute(const Attribute& rhs) :
Scope(rhs)
{
	operator=(rhs);
}

Attribute& Attribute::operator=(const Attribute& rhs)
{
	if (this != &rhs)
	{
		Scope::operator=(rhs);
		Append("this") = (RTTI*)this;
	}
	return *this;
}

void Attribute::Populate()
{
	//TODO: verify that the name hasn't already been added
	//Make HashMaap private and have a wrapper for it that is protected

	auto& signatures = mSignatures.Find(TypeIdInstance())->second;

	for (std::uint32_t i = 0; i < signatures.Size(); ++i)
	{
		auto& entry = signatures[i];

		Datum& d = Append(entry.mName, entry.mDatumType);

		if (entry.mInitialValue.Pointer)
		{
			sInternalSet[static_cast<std::int32_t>(entry.mDatumType)](d, entry, i, entry.mSize,this);
		}
		else if (entry.mAddress.Pointer)
		{
			sExternalSetStorage[static_cast<std::int32_t>(entry.mDatumType)](d, entry.mAddress, entry.mSize);
		}
	}
}

bool Attribute::IsPrescribedAttribute(const std::string& prescribedAttribute)
{
	if (IsAttribute(prescribedAttribute))
	{
		auto it = mSignatures.Find(TypeIdInstance());
		auto signatureVector = it->second;
		for (std::uint32_t i = 0; i < signatureVector.Size(); ++i)
		{
			if (signatureVector[i].mName.compare(prescribedAttribute) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool Attribute::IsAuxiliaryAttribute(const std::string& auxiliaryAttribute)
{
	return (IsAttribute(auxiliaryAttribute) && !IsPrescribedAttribute(auxiliaryAttribute));
}

bool Attribute::IsAttribute(const std::string& attributeName)
{
	auto* findDatum = Find(attributeName);
	if (findDatum)
	{
		return true;
	}
	return false;
}

Datum& Attribute::AppendAuxiliaryAttribute(const std::string& value)
{
	if (!IsPrescribedAttribute(value))
	{
		return Append(value);
	}
	else
	{
		throw std::exception("It is already a Prescribed Attribute");
	}
}

std::uint32_t Attribute::AuxiliaryBegin() const
{
	return mSignatures.Find(TypeIdInstance())->second.Size() + 1;
}

void Attribute::Clear()
{
	Scope::Clear();
	(*this)["this"] = (RTTI*)this;
}

const Vector<Attribute::PairType*>& Attribute::GetOrderVector() const
{
	return mOrderVector;
}

#pragma endregion

#pragma region FunctionPointerArray

const Attribute::InternalSet Attribute::sInternalSet[] = {
	Attribute::InternalUnknwon,
	Attribute::InternalInteger,
	Attribute::InternalFloat,
	Attribute::InternalVector,
	Attribute::InternalMatrix,
	Attribute::InternalString,
	Attribute::InternalRTTI,
	Attribute::InternalScope
};

const Attribute::ExternalSetStorage Attribute::sExternalSetStorage[] = {
	Attribute::ExternalUnknown,
	Attribute::ExternalInteger,
	Attribute::ExternalFloat,
	Attribute::ExternalVector,
	Attribute::ExternalMatrix,
	Attribute::ExternalString,
	Attribute::ExternalRTTI,
	Attribute::ExternalScope
};

#pragma endregion

#pragma region FunctionPointerImplementation

void Attribute::InternalUnknwon(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{

}

void Attribute::InternalInteger(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{
	datum.SetSize(size);
	for (std::uint32_t i = 0; i < size; ++i)
	{
		datum.Set(*signature.mInitialValue.Integer, i);
	}
}

void Attribute::InternalFloat(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{
	datum.SetSize(size);
	for (std::uint32_t i = 0; i < size; ++i)
	{
		datum.Set(*signature.mInitialValue.Float, i);
	}
}

void Attribute::InternalVector(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{
	datum.SetSize(size);
	for (std::uint32_t i = 0; i < size; ++i)
	{
		datum.Set(*signature.mInitialValue.Vector, i);
	}
}

void Attribute::InternalMatrix(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{
	datum.SetSize(size);
	for (std::uint32_t i = 0; i < size; ++i)
	{
		datum.Set(*signature.mInitialValue.Matrix, i);
	}
}

void Attribute::InternalString(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{
	datum.SetSize(size);
	for (std::uint32_t i = 0; i < size; ++i)
	{
		datum.Set(*signature.mInitialValue.String, i);
	}
}

void Attribute::InternalRTTI(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{
	datum.SetSize(size);
	for (std::uint32_t i = 0; i < size; ++i)
	{
		datum.Set(*signature.mInitialValue.Pointer, i);
	}
}

void Attribute::InternalScope(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent)
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		Scope** initialValue = signature.mInitialValue.Table;

		if (!(*initialValue))
		{
			*initialValue = new Scope();
		}
		if (*initialValue)
			parent->Adopt(*(*initialValue), signature.mName, i);
	}
}

void Attribute::ExternalUnknown(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{

}

void Attribute::ExternalInteger(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{
	datum.SetStorage(datumValue.Integer, size);
}

void Attribute::ExternalFloat(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{
	datum.SetStorage(datumValue.Float, size);
}

void Attribute::ExternalVector(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{
	datum.SetStorage(datumValue.Vector, size);
}

void Attribute::ExternalMatrix(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{
	datum.SetStorage(datumValue.Matrix, size);
}

void Attribute::ExternalString(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{
	datum.SetStorage(datumValue.String, size);
}

void Attribute::ExternalRTTI(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{
	datum.SetStorage(datumValue.Pointer, size);
}

void Attribute::ExternalScope(Datum& datum, const Attribute::DatumValue& datumValue, const std::uint32_t size)
{
	datum.SetStorage(datumValue.Table, size);
}

#pragma endregion

#pragma region Signature

Attribute::Signature::Signature() :
mName("None"), mDatumType(Datum::DatumType::Unknown), mInitialValue(), mSize(0), mAddress()
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, DatumValue initialValue, std::uint32_t size, DatumValue address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, std::int32_t* initialValue, std::uint32_t size, std::int32_t* address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, std::float_t* initialValue, std::uint32_t size, std::float_t* address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, glm::vec4* initialValue, std::uint32_t size, glm::vec4* address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, glm::mat4* initialValue, std::uint32_t size, glm::mat4* address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, std::string* initialValue, std::uint32_t size, std::string* address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, RTTI** initialValue, std::uint32_t size, RTTI** address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}

Attribute::Signature::Signature(const std::string name, Datum::DatumType datumType, Scope** initialValue, std::uint32_t size, Scope** address) :
mName(name), mDatumType(datumType), mInitialValue(initialValue), mSize(size), mAddress(address)
{
}
#pragma endregion
