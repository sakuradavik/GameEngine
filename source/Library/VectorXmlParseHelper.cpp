#include "pch.h"
#include "VectorXmlParseHelper.h"
#include "ScopeSharedData.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string VectorXmlParseHelper::VectorString = "Vector";
const std::string VectorXmlParseHelper::ValueString = "value";
const std::string VectorXmlParseHelper::NameString = "name";
const std::string VectorXmlParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

VectorXmlParseHelper::VectorXmlParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void VectorXmlParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool VectorXmlParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
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
			if (name == VectorString)
			{
				auto providedName = hashmap.Find(NameString);
				bIsParsing = true;
				if (providedName != hashmap.end())
				{

					data->GetScope()->Append(providedName->second, DatumType::Vector);
					mDatumName = providedName->second;
					return true;

				}
				else
				{
					throw std::exception("You must provide a name for this Vector");
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

			if (name == VectorString)
			{
				throw std::exception("This is not a valid Xml format");
			}
		}
	}
	return false;

}

bool VectorXmlParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
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
			if (name == VectorString)
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

bool VectorXmlParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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

IXmlParseHelper* VectorXmlParseHelper::Clone()
{
	return new VectorXmlParseHelper();;
}
