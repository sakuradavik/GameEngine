#include "pch.h"
#include "ScopeXmlParseHelper.h"
#include "ScopeSharedData.h"

using namespace Library;

#pragma region XMLStringTypes

const std::string ScopeXmlParseHelper::ScopeString = "Scope";
const std::string ScopeXmlParseHelper::NameString = "name";
const std::string ScopeXmlParseHelper::IndexString = "index";

#pragma endregion

typedef Datum::DatumType DatumType;

ScopeXmlParseHelper::ScopeXmlParseHelper() :
mDatumName(), bIsParsing(false), mIndex(0), mStringData()
{
}

void ScopeXmlParseHelper::Initialize()
{
	bIsParsing = false;
	mDatumName = std::string();
	mStringData = std::string();
	mIndex = 0;
}

bool ScopeXmlParseHelper::StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		mStringData = std::string();
		if (name == ScopeString)
		{
			if (!bIsParsing)
			{
				bIsParsing = true;
				return true;
			}
			else
			{
				auto providedName = hashmap.Find(NameString);
				if (providedName != hashmap.end())
				{
					Scope* newScope = &(data->GetScope()->AppendScope(providedName->second));
					data->SetScope(newScope);
					mDatumName = providedName->second;
					return true;
				}
				else
				{
					throw std::exception("You must provide a name for this Scope");
				}
			}
		}
	}
	return false;
}

bool ScopeXmlParseHelper::EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name)
{
	if (!sharedData)
	{
		return false;
	}

	ScopeSharedData * data = sharedData->As<ScopeSharedData>();
	if (data)
	{
		if (name == ScopeString && bIsParsing)
		{
			if (!data->GetScope()->GetParent())
			{
				bIsParsing = false;
			}
			else
			{
				Scope * parentScope = data->GetScope()->GetParent();
				data->SetScope(parentScope);
			}
			return true;
		}
	}
	return false;
}

bool ScopeXmlParseHelper::CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
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
			return true;
		}
	}
	return false;
}

IXmlParseHelper* ScopeXmlParseHelper::Clone()
{
	return new ScopeXmlParseHelper();;
}
