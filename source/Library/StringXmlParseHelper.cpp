#include "pch.h"
#include "StringXmlParseHelper.h"
#include "ScopeSharedData.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string StringXmlParseHelper::StringString = "String";
const std::string StringXmlParseHelper::ValueString = "value";
const std::string StringXmlParseHelper::NameString = "name";
const std::string StringXmlParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

StringXmlParseHelper::StringXmlParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void StringXmlParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool StringXmlParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
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
			if (name == StringString)
			{
				auto providedName = hashmap.Find(NameString);
				bIsParsing = true;
				if (providedName != hashmap.end())
				{

					data->GetScope()->Append(providedName->second, DatumType::String);
					mDatumName = providedName->second;
					return true;

				}
				else
				{
					throw std::exception("You must provide a name for this String");
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

bool StringXmlParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
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
			if (name == StringString)
			{
				bIsParsing = false;
			}
			else if (name == ValueString)
			{
				Datum * datum = data->GetScope()->Find(mDatumName);
				if (datum)
				{
					RemoveSpaces(mStringData);
					datum->SetFromString(mStringData, mIndex);
					mStringData = std::string();
					return true;
				}
			}
		}
	}
	return false;
}

bool StringXmlParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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

IXmlParseHelper* StringXmlParseHelper::Clone()
{
	return new StringXmlParseHelper();;
}

void StringXmlParseHelper::RemoveSpaces(std::string& string)
{
	//TODO: Remove space before and after not in all of the string
	for (std::uint32_t i = 0; i < string.length(); ++i)
	{
		if (string[i] == ' ')
		{
			string.erase(i, 1);
		}
	}
}