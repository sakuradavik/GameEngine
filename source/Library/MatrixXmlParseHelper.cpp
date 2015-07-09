#include "pch.h"
#include "MatrixXmlParseHelper.h"
#include "ScopeSharedData.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string MatrixXmlParseHelper::MatrixString = "Matrix";
const std::string MatrixXmlParseHelper::ValueString = "value";
const std::string MatrixXmlParseHelper::NameString = "name";
const std::string MatrixXmlParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

MatrixXmlParseHelper::MatrixXmlParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void MatrixXmlParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool MatrixXmlParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		mStringData = std::string();

		if (!bIsParsing)
		{
			if (name == MatrixString)
			{
				auto providedName = hashmap.Find(NameString);
				bIsParsing = true;
				if (providedName != hashmap.end())
				{

					data->GetScope()->Append(providedName->second, DatumType::Matrix);
					mDatumName = providedName->second;
					return true;

				}
				else
				{
					throw std::exception("You must provide a name for this Matrix");
				}
			}
		}
		else
		{
			if (name == ValueString)
			{
				auto providedName = hashmap.Find(IndexString);
				mIndex = 0;
				if ((providedName != hashmap.end()) && (providedName->first == IndexString))
				{
					mIndex = std::atoi(providedName->second.c_str());
				}
				return true;
			}

			else
			{
				throw std::exception("This is not a valid Xml format");
			}
		}
	}
	return false;

}

bool MatrixXmlParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		if (bIsParsing)
		{
			if (name == MatrixString)
			{
				bIsParsing = false;
			}
			else if (name == ValueString)
			{
				Datum * datum = data->GetScope()->Find(mDatumName);
				if (datum)
				{
					datum->SetFromString(mStringData, mIndex);
					mStringData = std::string();
					return true;
				}
			}
		}
	}
	return false;
}

bool MatrixXmlParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * sharedScopeData = sharedData->As<ScopeSharedData>();
	if (sharedScopeData)
	{
		if (bIsParsing)
		{
			mStringData.append(data.c_str(), length);
			return true;
		}
	}
	return false;
}

IXmlParseHelper* MatrixXmlParseHelper::Clone()
{
	return new MatrixXmlParseHelper();;
}
