#include "pch.h"
#include "Datum.h"
#include "Scope.h"

using namespace Library;

#pragma region Datum

#pragma region FunctionPointerArrays

const Datum::AllocFunction Datum::sAllocFunctions[] = {
	Datum::AllocUnknown,
	Datum::AllocInteger,
	Datum::AllocFloat,
	Datum::AllocVector,
	Datum::AllocMatrix,
	Datum::AllocString,
	Datum::AllocRTTI,
	Datum::AllocScope
};

const Datum::CopyFunction Datum::sCopyFunctions[] = {
	CopyUnknown,
	CopyInteger,
	CopyFloat,
	CopyVector,
	CopyMatrix,
	CopyString,
	CopyRTTI,
	CopyRTTI
};

const Datum::DeAllocFunction Datum::sDeAllocFunctions[] = {
	DeAllocUnknown,
	DeAllocInteger,
	DeAllocFloat,
	DeAllocVector,
	DeAllocMatrix,
	DeAllocString,
	DeAllocRTTI,
	DeAllocRTTI
};

const Datum::ToStringFunction Datum::sToStringFunction[] = {
	ToStringUnknown,
	ToStringInteger,
	ToStringFloat,
	ToStringVector,
	ToStringMatrix,
	ToStringString,
	ToStringRTTI,
	ToStringRTTI
};

const Datum::CompareTo Datum::sCompareToFunction[] = {
	CompateToUnknown,
	CompateToInteger,
	CompateToFloat,
	CompateToVector,
	CompateToMatrix,
	CompateToString,
	CompateToRTTI,
	CompateToScope
};

const Datum::StringToData Datum::sStringToData[] = {
	StringToDataUnknown,
	StringToDataInteger,
	StringToDataFloat,
	StringToDataVector,
	StringToDataMatrix,
	StringToDataString,
	StringToDataRTTI,
	StringToDataRTTI
};

#pragma endregion

#pragma region FunctionPointerAlloc

void Datum::AllocUnknown(Datum& data, std::uint32_t size)
{

}

void Datum::AllocInteger(Datum& data, std::uint32_t size)
{
	std::int32_t* temp = data.mContainer.Integer;
	data.mContainer.Integer = new std::int32_t[size];

	if (temp)
	{
		for (std::uint32_t i = 0; i < data.mSize; ++i)
		{
			data.mContainer.Integer[i] = temp[i];
		}
		data.mCapacity = size;

		delete[] temp;
	}
}

void Datum::AllocFloat(Datum& data, std::uint32_t size)
{
	std::float_t* temp = data.mContainer.Float;
	data.mContainer.Float = new std::float_t[size];

	if (temp)
	{
		for (std::uint32_t i = 0; i < data.mSize; ++i)
		{
			data.mContainer.Float[i] = temp[i];
		}
		data.mCapacity = size;
		delete[] temp;
	}
}

void Datum::AllocVector(Datum& data, std::uint32_t size)
{
	glm::vec4* temp = data.mContainer.Vector;
	data.mContainer.Vector = new glm::vec4[size];

	if (temp)
	{
		for (std::uint32_t i = 0; i < data.mSize; ++i)
		{
			data.mContainer.Vector[i] = temp[i];
		}
		data.mCapacity = size;

		delete[] temp;
	}
}

void Datum::AllocMatrix(Datum& data, std::uint32_t size)
{
	glm::mat4* temp = data.mContainer.Matrix;
	data.mContainer.Matrix = new glm::mat4[size];

	if (temp)
	{
		for (std::uint32_t i = 0; i < data.mSize; ++i)
		{
			data.mContainer.Matrix[i] = temp[i];
		}
		data.mCapacity = size;
		delete[] temp;
	}
}

void Datum::AllocString(Datum& data, std::uint32_t size)
{
	std::string* temp = data.mContainer.String;
	data.mContainer.String = new std::string[size];

	if (temp)
	{
		for (std::uint32_t i = 0; i < data.mSize; ++i)
		{
			data.mContainer.String[i] = temp[i];
		}
		data.mCapacity = size;

		delete[] temp;
	}
}

void Datum::AllocRTTI(Datum& data, std::uint32_t size)
{
	RTTI** temp = data.mContainer.RTTI;
	data.mContainer.RTTI = new RTTI*[size];

	if (temp)
	{
		for (std::uint32_t i = 0; i < data.mSize; ++i)
		{
			data.mContainer.RTTI[i] = temp[i];
		}
		data.mCapacity = size;

		delete[] temp;
	}
}

void Datum::AllocScope(Datum& data, std::uint32_t size)
{
	Scope** temp = data.mContainer.Scope;
	data.mContainer.Scope = new Scope*[size];

	if (temp)
	{
		for (std::uint32_t i = 0; i < data.mSize; ++i)
		{
			data.mContainer.Scope[i] = temp[i];
		}
		data.mCapacity = size;

		delete[] temp;
	}
}

#pragma endregion

#pragma region FunctionPointerCopy

void Datum::CopyUnknown(const DatumValue& rhs, DatumValue& value, std::uint32_t size)
{

}

void Datum::CopyInteger(const DatumValue& rhs, DatumValue& value, std::uint32_t size)
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		value.Integer[i] = rhs.Integer[i];
	}
}

void Datum::CopyFloat(const DatumValue& rhs, DatumValue& value, std::uint32_t size)
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		value.Float[i] = rhs.Float[i];
	}
}

void Datum::CopyVector(const DatumValue& rhs, DatumValue& value, std::uint32_t size)
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		value.Vector[i] = rhs.Vector[i];
	}
}

void Datum::CopyMatrix(const DatumValue& rhs, DatumValue& value, std::uint32_t size)
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		value.Matrix[i] = rhs.Matrix[i];
	}
}

void Datum::CopyString(const DatumValue& rhs, DatumValue& value, std::uint32_t size)
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		value.String[i] = rhs.String[i];
	}
}

void Datum::CopyRTTI(const DatumValue& rhs, DatumValue& value, std::uint32_t size)
{
	for (std::uint32_t i = 0; i < size; ++i)
	{
		value.RTTI[i] = rhs.RTTI[i];
	}
}

#pragma endregion

#pragma region FunctionPointerDelloc

void Datum::DeAllocUnknown(Datum& data)
{
}

void Datum::DeAllocInteger(Datum& data)
{
	if (!data.bIsExternal)
	{
		delete[] data.mContainer.Integer;
	}
	data.mContainer.Integer = nullptr;
}

void Datum::DeAllocFloat(Datum& data)
{
	if (!data.bIsExternal)
	{
		delete[] data.mContainer.Float;
	}
	data.mContainer.Float = nullptr;
}

void Datum::DeAllocVector(Datum& data)
{
	if (!data.bIsExternal)
	{
		delete[] data.mContainer.Vector;
	}
	data.mContainer.Vector = nullptr;
}

void Datum::DeAllocMatrix(Datum& data)
{
	if (!data.bIsExternal)
	{
		delete[] data.mContainer.Matrix;
	}
	data.mContainer.Matrix = nullptr;
}

void Datum::DeAllocString(Datum& data)
{
	if (!data.bIsExternal)
	{
		delete[] data.mContainer.String;
	}
	data.mContainer.String = nullptr;
}

void Datum::DeAllocRTTI(Datum& data)
{
	if (!data.bIsExternal)
	{
		delete[](data.mContainer.RTTI);
	}
	data.mContainer.RTTI = nullptr;
}

#pragma endregion

#pragma region FunctionPointerToString

std::string Datum::ToStringUnknown(const Datum& data, std::uint32_t size)
{
	throw std::exception("You are trying to turn an unknown type to a string");
}

std::string Datum::ToStringInteger(const Datum& data, std::uint32_t size)
{
	return std::to_string(data.mContainer.Integer[size]);
}

std::string Datum::ToStringFloat(const Datum& data, std::uint32_t size)
{
	return std::to_string(data.mContainer.Float[size]);
}

std::string Datum::ToStringVector(const Datum& data, std::uint32_t size)
{
	return glm::to_string(data.mContainer.Vector[size]);
}

std::string Datum::ToStringMatrix(const Datum& data, std::uint32_t size)
{
	return glm::to_string(data.mContainer.Matrix[size]);
}

std::string Datum::ToStringString(const Datum& data, std::uint32_t size)
{
	return data.mContainer.String[size];
}

std::string Datum::ToStringRTTI(const Datum& data, std::uint32_t size)
{
	return "This points to an RTTI";
}

#pragma endregion

#pragma region FunctionPointerCompareTo

bool Datum::CompateToUnknown(const Datum& rhs, const Datum& data)
{
	return false;
}

bool Datum::CompateToInteger(const Datum& rhs, const Datum& data)
{
	for (std::uint32_t i = 0; i < data.mSize; ++i)
	{
		if (rhs.mContainer.Integer[i] != data.mContainer.Integer[i])
		{
			return false;
		}
	}
	return true;
}

bool Datum::CompateToFloat(const Datum& rhs, const Datum& data)
{
	for (std::uint32_t i = 0; i < data.mSize; ++i)
	{
		if (rhs.mContainer.Float[i] != data.mContainer.Float[i])
		{
			return false;
		}
	}
	return true;
}

bool Datum::CompateToVector(const Datum& rhs, const Datum& data)
{
	for (std::uint32_t i = 0; i < data.mSize; ++i)
	{
		if (rhs.mContainer.Vector[i] != data.mContainer.Vector[i])
		{
			return false;
		}
	}
	return true;
}

bool Datum::CompateToMatrix(const Datum& rhs, const Datum& data)
{
	for (std::uint32_t i = 0; i < data.mSize; ++i)
	{
		if (rhs.mContainer.Matrix[i] != data.mContainer.Matrix[i])
		{
			return false;
		}
	}
	return true;
}

bool Datum::CompateToString(const Datum& rhs, const Datum& data)
{
	for (std::uint32_t i = 0; i < data.mSize; ++i)
	{
		if (rhs.mContainer.String[i] != data.mContainer.String[i])
		{
			return false;
		}
	}
	return true;
}

bool Datum::CompateToRTTI(const Datum& rhs, const Datum& data)
{
	for (std::uint32_t i = 0; i < data.mSize; ++i)
	{
		if (rhs.mContainer.RTTI[i] != data.mContainer.RTTI[i])
		{
			return false;
		}
	}
	return true;
}

bool Datum::CompateToScope(const Datum& rhs, const Datum& data)
{
	for (std::uint32_t i = 0; i < data.mSize; ++i)
	{
		if (*(rhs.mContainer.Scope[i]) != *(data.mContainer.Scope[i]))
		{
			return false;
		}
	}
	return true;
}

#pragma endregion

#pragma region FunctionPointerStringToData

void Datum::StringToDataUnknown(const std::string data, const std::uint32_t size, Datum& datum)
{

}

void Datum::StringToDataInteger(const std::string data, const std::uint32_t size, Datum& datum)
{
	std::int32_t temp = std::atoi(data.c_str());
	datum.Set(temp, size);
}

void Datum::StringToDataFloat(const std::string data, const std::uint32_t size, Datum& datum)
{
	std::float_t temp = static_cast<std::float_t>(std::atof(data.c_str()));
	datum.Set(temp, size);
}

void Datum::StringToDataVector(const std::string data, const std::uint32_t size, Datum& datum)
{
	float a, b, c, d = 0.0f;
	sscanf_s(data.c_str(), "%f, %f, %f, %f", &a, &b, &c, &d);
	auto temp = glm::vec4(a, b, c, d);
	datum.Set(temp, size);
}

void Datum::StringToDataMatrix(const std::string data, const std::uint32_t size, Datum& datum)
{
	//TODO: Fix this
	if (data.length() < 4)
		datum.mContainer.Matrix[size] = glm::mat4(static_cast<std::float_t>(std::atof(data.c_str())));

	else
	{
		float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p = 0.0f;
		sscanf_s(data.c_str(), "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p);
		auto temp = glm::mat4(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
		datum.Set(temp, size);
	}
}

void Datum::StringToDataString(const std::string data, const std::uint32_t size, Datum& datum)
{
	datum.Set(data,size);
}

void Datum::StringToDataRTTI(const std::string data, const std::uint32_t size, Datum& datum)
{

}

#pragma endregion

#pragma region Constructors

Datum::Datum(DatumType dataType, std::uint32_t size)
	:mDatumType(dataType), mSize(size), mCapacity(0), bIsExternal(false), mContainer()
{
	if (dataType != DatumType::Unknown)
	{
		SetSize(size);
	}
}

Datum::Datum(const Datum& rhs)
	: Datum()
{
	operator=(rhs);
}

#pragma endregion

#pragma region AssignmentOperator

Datum& Datum::operator=(const Datum& rhs)
{
	if (this != &rhs)
	{
		Clear();
		mDatumType = rhs.mDatumType;
		if (rhs.bIsExternal)
		{
			mContainer = rhs.mContainer;
			mCapacity = rhs.mCapacity;
		}
		else
		{
			if (rhs.mDatumType != DatumType::Unknown)
			{
				SetSize(rhs.mSize);
				sCopyFunctions[(int)rhs.mDatumType](rhs.mContainer, mContainer, rhs.mSize);
			}
		}


		mSize = rhs.mSize;
		bIsExternal = rhs.bIsExternal;
	}
	return *this;
}

Datum& Datum::operator=(const std::int32_t& rhs)
{
	if (mContainer.Integer != &rhs)
	{
		Set(rhs);
		mSize = 1;
	}
	return *this;
}

Datum& Datum::operator=(const std::float_t& rhs)
{
	if (mContainer.Float != &rhs)
	{
		Set(rhs);
		mSize = 1;
	}
	return *this;
}

Datum& Datum::operator=(const glm::vec4& rhs)
{
	if (mContainer.Vector != &rhs)
	{
		Set(rhs);
		mSize = 1;
	}
	return *this;
}

Datum& Datum::operator=(const glm::mat4& rhs)
{
	if (mContainer.Matrix != &rhs)
	{
		Set(rhs);
		mSize = 1;
	}
	return *this;
}

Datum& Datum::operator=(const std::string& rhs)
{
	if (mContainer.String != &rhs)
	{
		Set(rhs);
		mSize = 1;
	}
	return *this;
}

Datum& Datum::operator=(RTTI* rhs)
{
	if ((mContainer.RTTI) != &rhs)
	{
		Set(rhs);
		mSize = 1;
	}
	return *this;
}

Datum& Datum::operator=(Scope* rhs)
{
	if ((*mContainer.Scope) != rhs)
	{
		Set(rhs);
		mSize = 1;
	}
	return *this;
}

#pragma endregion

#pragma region SetStorage

void Datum::SetStorage(std::int32_t* data, std::uint32_t size)
{
	if (!bIsExternal && mSize > 0)
	{
		throw std::exception("This data is internal");
	}

	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Integer;
	}

	if (mDatumType != DatumType::Integer)
	{
		throw std::exception("You are trying to set a non-integer to an integer");
	}
	mContainer.Integer = data;
	mSize = size;
	mCapacity = size;
	bIsExternal = true;
}

void Datum::SetStorage(std::float_t* data, std::uint32_t size)
{
	if (!bIsExternal && mSize > 0)
	{
		throw std::exception("This data is internal");
	}

	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Float;
	}

	if (mDatumType != DatumType::Float)
	{
		throw std::exception("You are trying to set a non-integer to an integer");
	}
	mContainer.Float = data;
	mSize = size;
	mCapacity = size;
	bIsExternal = true;
}

void Datum::SetStorage(glm::vec4* data, std::uint32_t size)
{
	if (!bIsExternal && mSize > 0)
	{
		throw std::exception("This data is internal");
	}

	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Vector;
	}

	if (mDatumType != DatumType::Vector)
	{
		throw std::exception("You are trying to set a non-integer to an integer");
	}
	mContainer.Vector = data;
	mSize = size;
	mCapacity = size;
	bIsExternal = true;
}

void Datum::SetStorage(glm::mat4* data, std::uint32_t size)
{
	if (!bIsExternal && mSize > 0)
	{
		throw std::exception("This data is internal");
	}

	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Matrix;
	}

	if (mDatumType != DatumType::Matrix)
	{
		throw std::exception("You are trying to set a non-integer to an integer");
	}
	mContainer.Matrix = data;
	mSize = size;
	mCapacity = size;
	bIsExternal = true;
}

void Datum::SetStorage(std::string* data, std::uint32_t size)
{
	if (!bIsExternal && mSize > 0)
	{
		throw std::exception("This data is internal");
	}

	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::String;
	}

	if (mDatumType != DatumType::String)
	{
		throw std::exception("You are trying to set a non-integer to an integer");
	}
	mContainer.String = data;
	mSize = size;
	mCapacity = size;
	bIsExternal = true;
}

void Datum::SetStorage(RTTI** data, std::uint32_t size)
{
	if (!bIsExternal && mSize > 0)
	{
		throw std::exception("This data is internal");
	}
	mContainer.RTTI = data;
	mSize = size;
	mCapacity = size;
	bIsExternal = true;
}

void Datum::SetStorage(Scope** data, std::uint32_t size)
{
	if (!bIsExternal && mSize > 0)
	{
		throw std::exception("This data is internal");
	}
	mContainer.Scope = data;
	mSize = size;
	mCapacity = size;
	bIsExternal = true;
}

#pragma endregion

#pragma region EqualOperator

bool Datum::operator==(const Datum& rhs) const
{
	if ((mSize == rhs.mSize) && (mCapacity == rhs.mCapacity) && (bIsExternal == rhs.bIsExternal))
	{
		if (mDatumType != DatumType::Unknown)
		{
			return sCompareToFunction[(std::uint32_t)mDatumType](rhs, *this);
		}
	}
	return false;
}

bool Datum::operator==(const std::int32_t& rhs) const
{
	if (DatumType::Integer != mDatumType)
	{
		return false;
	}
	return (rhs == mContainer.Integer[0]);
}

bool Datum::operator==(const std::float_t& rhs) const
{
	if (DatumType::Float != mDatumType)
	{
		return false;
	}
	return (rhs == mContainer.Float[0]);
}

bool Datum::operator==(const glm::vec4& rhs) const
{
	if (DatumType::Vector != mDatumType)
	{
		return false;
	}
	return (rhs == mContainer.Vector[0]);
}

bool Datum::operator==(const glm::mat4& rhs) const
{
	if (DatumType::Matrix != mDatumType)
	{
		return false;
	}
	return (rhs == mContainer.Matrix[0]);
}

bool Datum::operator==(const std::string& rhs) const
{
	if (DatumType::String != mDatumType)
	{
		return false;
	}
	return (((rhs.compare(mContainer.String[0]) == 0)));
}

bool Datum::operator==(const RTTI* rhs) const
{
	return (rhs == *mContainer.RTTI);
}

bool Datum::operator==(const Scope* rhs) const
{
	return (rhs == *mContainer.Scope);
}

#pragma endregion

#pragma region NotEqualOperator

bool Datum::operator!=(const Datum& rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(const std::int32_t& rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(const std::float_t& rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(const glm::vec4& rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(const glm::mat4& rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(const std::string& rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(const RTTI* rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(const Scope* rhs) const
{
	return !(operator==(rhs));
}

#pragma endregion

#pragma region Set

void Datum::Set(const std::int32_t& data, std::uint32_t index)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Integer;
	}

	if (mDatumType != DatumType::Integer)
	{
		throw std::exception("You are trying to set a non-integer to an integer");
	}

	if (bIsExternal)
	{
		if (index >= mCapacity)
		{
			throw std::exception("You are trying to access an index greater than the capacity of an external type");
		}
		else
		{
			mContainer.Integer[index] = data;
		}
	}
	else
	{
		if (index < mCapacity)
		{
			mContainer.Integer[index] = data;

			if (mSize <= index)
			{
				mSize = index + 1;
			}
		}
		else
		{
			SetSize(index + 1);
			mContainer.Integer[index] = data;
		}
	}
}

void Datum::Set(const std::float_t& data, std::uint32_t index)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Float;
	}

	if (mDatumType != DatumType::Float)
	{
		throw std::exception("You are trying to set a non-Float to a Float");
	}

	if (bIsExternal)
	{
		if (index >= mCapacity)
		{
			throw std::exception("You are trying to access an index greater than the capacity of an external type");
		}
		else
		{
			mContainer.Float[index] = data;
		}
	}
	else
	{
		if (index < mCapacity)
		{
			mContainer.Float[index] = data;

			if (mSize <= index)
			{
				mSize = index + 1;
			}
		}
		else
		{
			SetSize(index + 1);
			mContainer.Float[index] = data;
		}
	}
}

void Datum::Set(const glm::vec4& data, std::uint32_t index)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Vector;
	}

	if (mDatumType != DatumType::Vector)
	{
		throw std::exception("You are trying to set a non-Float to a Float");
	}

	if (bIsExternal)
	{
		if (index >= mCapacity)
		{
			throw std::exception("You are trying to access an index greater than the capacity of an external type");
		}
		else
		{
			mContainer.Vector[index] = data;
		}
	}
	else
	{
		if (index < mCapacity)
		{
			mContainer.Vector[index] = data;

			if (mSize <= index)
			{
				mSize = index + 1;
			}
		}
		else
		{
			SetSize(index + 1);
			mContainer.Vector[index] = data;
		}
	}
}

void Datum::Set(const glm::mat4& data, std::uint32_t index)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Matrix;
	}

	if (mDatumType != DatumType::Matrix)
	{
		throw std::exception("You are trying to set a non-Matrix to a Matrix");
	}

	if (bIsExternal)
	{
		if (index >= mCapacity)
		{
			throw std::exception("You are trying to access an index greater than the capacity of an external type");
		}
		else
		{
			mContainer.Matrix[index] = data;
		}
	}
	else
	{
		if (index < mCapacity)
		{
			mContainer.Matrix[index] = data;

			if (mSize <= index)
			{
				mSize = index + 1;
			}
		}
		else
		{
			SetSize(index + 1);
			mContainer.Matrix[index] = data;
		}
	}
}

void Datum::Set(const std::string& data, std::uint32_t index)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::String;
	}

	if (mDatumType != DatumType::String)
	{
		throw std::exception("You are trying to set a non-String to a String");
	}

	if (bIsExternal)
	{
		if (index >= mCapacity)
		{
			throw std::exception("You are trying to access an index greater than the capacity of an external type");
		}
		else
		{
			mContainer.String[index] = data;
		}
	}
	else
	{
		if (index < mCapacity)
		{
			mContainer.String[index] = data;

			if (mSize <= index)
			{
				mSize = index + 1;
			}
		}
		else
		{
			SetSize(index + 1);
			mContainer.String[index] = data;
		}
	}
}

void Datum::Set(RTTI* data, std::uint32_t index)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Pointer;
	}

	if (mDatumType != DatumType::Pointer)
	{
		throw std::exception("You are trying to set a non-RTTI to a RTTI");
	}

	if (bIsExternal)
	{
		if (index >= mCapacity)
		{
			throw std::exception("You are trying to access an index greater than the capacity of an external type");
		}
		else
		{
			mContainer.RTTI[index] = data;
		}
	}
	else
	{
		if (index < mCapacity)
		{
			mContainer.RTTI[index] = data;

			if (mSize <= index)
			{
				mSize = index + 1;
			}
		}
		else
		{
			SetSize(index + 1);
			mContainer.RTTI[index] = data;
		}
	}
}

void Datum::Set(Scope* data, std::uint32_t index)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = DatumType::Table;
	}

	if (mDatumType != DatumType::Table)
	{
		throw std::exception("You are trying to set a non-RTTI to a RTTI");
	}

	if (bIsExternal)
	{
		if (index >= mCapacity)
		{
			throw std::exception("You are trying to access an index greater than the capacity of an external type");
		}
		else
		{
			mContainer.Scope[index] = data;
		}
	}
	else
	{
		if (index < mCapacity)
		{
			mContainer.Scope[index] = data;

			if (mSize <= index)
			{
				mSize = index + 1;
			}
		}
		else
		{
			SetSize(index + 1);
			mContainer.Scope[index] = data;
		}
	}
}

#pragma endregion

#pragma region Get

std::int32_t& Datum::GetInteger(std::uint32_t index)
{
	if (mDatumType != DatumType::Integer)
	{
		throw std::exception("Not an integer");
	}
	if (index < mSize)
	{
		return mContainer.Integer[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

std::float_t& Datum::GetFloat(std::uint32_t index)
{
	if (mDatumType != DatumType::Float)
	{
		throw std::exception("Not an float");
	}
	if (index < mSize)
	{
		return mContainer.Float[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

glm::vec4& Datum::GetVector(std::uint32_t index)
{
	if (mDatumType != DatumType::Vector)
	{
		throw std::exception("Not an integer");
	}
	if (index < mSize)
	{
		return mContainer.Vector[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

glm::mat4& Datum::GetMatrix(std::uint32_t index)
{
	if (mDatumType != DatumType::Matrix)
	{
		throw std::exception("Not an integer");
	}
	if (index < mSize)
	{
		return mContainer.Matrix[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

std::string& Datum::GetString(std::uint32_t index)
{
	if (mDatumType != DatumType::String)
	{
		throw std::exception("Not an integer");
	}
	if (index < mSize)
	{
		return mContainer.String[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

RTTI* Datum::GetRTTI(std::uint32_t index)
{
	if (mDatumType != DatumType::Pointer)
	{
		throw std::exception("Not an integer");
	}
	if (index < mSize)
	{
		return mContainer.RTTI[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

Scope* Datum::GetScope(std::uint32_t index)
{
	if (mDatumType != DatumType::Table)
	{
		throw std::exception("Not an integer");
	}
	if (index < mSize)
	{
		return mContainer.Scope[index];
	}
	else
	{
		throw std::exception("Index out of bounds");
	}
}

#pragma endregion

Scope& Datum::operator[](std::uint32_t index)
{
	return *GetScope(index);
}

Datum::~Datum()
{
	Clear();
}

void Datum::SetType(const DatumType datumType)
{
	if (mDatumType == DatumType::Unknown)
	{
		mDatumType = datumType;
	}
	else
	{
		throw std::exception("Type has already been set");
	}
}

Datum::DatumType Datum::GetType() const
{
	return mDatumType;
}

std::uint32_t Datum::Size() const
{
	return mSize;
}

void Datum::SetSize(const std::uint32_t newSize)
{
	if (bIsExternal)
	{
		throw std::exception("This Datum is External.");
	}

	if (mDatumType == DatumType::Unknown)
	{
		throw std::exception("Your data is unknown");
	}

	if (mDatumType != DatumType::Unknown)
	{
		if (newSize < mCapacity)
		{
			mSize = newSize;
		}
		else
		{
			sAllocFunctions[(int)mDatumType](*this, newSize);
			mSize = newSize;
			mCapacity = newSize;
		}
	}
}

void Datum::Clear()
{
	sDeAllocFunctions[(int)mDatumType](*this);
	mSize = 0;
	mCapacity = 0;
	bIsExternal = false;
}

void Datum::SetFromString(const std::string data, const std::uint32_t size)
{
	if (mDatumType == DatumType::Unknown)
	{
		throw std::exception("Your data is unknown");
	}
	if (size > mSize)
	{
		throw std::exception("index out of bound");
	}
	sStringToData[(int)mDatumType](data, size, *this);
}

std::string Datum::ToString(std::uint32_t size) const
{
	if (size >= mSize)
	{
		throw std::exception("Index out of bound");
	}
	return sToStringFunction[(int)mDatumType](*this, size);
}

bool Datum::IsExternal()
{
	return bIsExternal;
}

#pragma endregion