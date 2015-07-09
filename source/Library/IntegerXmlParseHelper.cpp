#include "pch.h"
#include "IntegerXmlParseHelper.h"
#include "ScopeSharedData.h"
#include "World.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string IntegerXmlParseHelper::IntegerString = "Integer";
const std::string IntegerXmlParseHelper::ValueString = "value";
const std::string IntegerXmlParseHelper::NameString = "name";
const std::string IntegerXmlParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

IntegerXmlParseHelper::IntegerXmlParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void IntegerXmlParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool IntegerXmlParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
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
			if (name == IntegerString)
			{
				auto providedName = hashmap.Find(NameString);
				bIsParsing = true;
				if (providedName != hashmap.end())
				{
					if (data->GetScope())
						data->GetScope()->Append(providedName->second, DatumType::Integer);

					if (data->GetWorld())
						data->GetWorld()->Append(providedName->second, DatumType::Integer);

					mDatumName = providedName->second;
					return true;

				}
				else
				{
					throw std::exception("You must provide a name for this integer");
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

bool IntegerXmlParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
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
			if (name == IntegerString)
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

bool IntegerXmlParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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
			mStringData.append(data.c_str(),length);
			return true;
		}
	}
	return false;
}

IXmlParseHelper* IntegerXmlParseHelper::Clone()
{
	return new IntegerXmlParseHelper();;
}
