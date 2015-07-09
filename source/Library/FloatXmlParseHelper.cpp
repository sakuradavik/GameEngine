#include "pch.h"
#include "FloatXmlParseHelper.h"
#include "ScopeSharedData.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string FloatXmlParseHelper::FloatString = "Float";
const std::string FloatXmlParseHelper::ValueString = "value";
const std::string FloatXmlParseHelper::NameString = "name";
const std::string FloatXmlParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

FloatXmlParseHelper::FloatXmlParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void FloatXmlParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool FloatXmlParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
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
			if (name == FloatString)
			{
				auto providedName = hashmap.Find(NameString);
				bIsParsing = true;
				if (providedName != hashmap.end())
				{
					data->GetScope()->Append(providedName->second, DatumType::Float);
					mDatumName = providedName->second;
					return true;
				}
				else
				{
					throw std::exception("You must provide a name for this float");
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

bool FloatXmlParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
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
			if (name == FloatString)
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

bool FloatXmlParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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

IXmlParseHelper* FloatXmlParseHelper::Clone()
{
	return new FloatXmlParseHelper();;
}