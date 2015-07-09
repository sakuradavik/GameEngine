#include "pch.h"
#include "XmlParseMaster.h"
#include "IXmlParseHelper.h"
#include <fstream>
#include <iostream>

using namespace Library;

typedef XmlParseMaster::SharedData SharedData;

#pragma region SharedData

RTTI_DEFINITIONS(XmlParseMaster::SharedData);

SharedData::SharedData() :
mParseMaster(nullptr), mDepth(0)
{

}

SharedData::~SharedData()
{
	mParseMaster = nullptr;
}

SharedData* SharedData::Clone()
{
	return new SharedData();
}

void SharedData::SetXmlParseMaster(XmlParseMaster* parseMaster)
{
	mParseMaster = parseMaster;
}

XmlParseMaster* SharedData::GetXmlParseMaster()
{
	return mParseMaster;
}

void SharedData::IncrementDepth()
{
	++mDepth;
}

void SharedData::DecrementDepth()
{
	--mDepth;
}

std::int32_t SharedData::Depth()
{
	return mDepth;
}

void SharedData::Reset()
{
	mDepth = 0;
}
#pragma endregion

#pragma region XmlParseMaster

XmlParseMaster::XmlParseMaster(SharedData* sharedData) :
mParseHelpers(), mParser(XML_ParserCreate("UTF-8")), bIsClone(false), mFileName("none")
{
	SetSharedData(sharedData);
	XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
	XML_SetCharacterDataHandler(mParser, CharDataHandler);
	XML_SetUserData(mParser, mSharedData);
}

XmlParseMaster::~XmlParseMaster()
{
	if (bIsClone)
	{
		for (auto it = mParseHelpers.begin(); it != mParseHelpers.end(); ++it)
		{
			delete (*it);
			(*it) = nullptr;
		}
		mParseHelpers.Clear();
		delete mSharedData;
	}
	mSharedData = nullptr;
	XML_ParserFree(mParser);
}

XmlParseMaster* XmlParseMaster::Clone()
{
	SharedData* sharedData;

	if (mSharedData)
	{
		sharedData = mSharedData->Clone();
	}
	else
	{
		sharedData = nullptr;
	}

	XmlParseMaster* parseMaster = new XmlParseMaster(sharedData);
	sharedData->SetXmlParseMaster(parseMaster);
	parseMaster->bIsClone = true;

	for (auto it = mParseHelpers.begin(); it != mParseHelpers.end(); ++it)
	{
		parseMaster->AddHelper(*((*it)->Clone()));
	}

	return parseMaster;
}

void XmlParseMaster::AddHelper(IXmlParseHelper& parseHelper)
{
	mParseHelpers.PushBack(&parseHelper);
	parseHelper.Initialize();
}

void XmlParseMaster::RemoveHelper(IXmlParseHelper& parseHelper)
{
	mParseHelpers.Remove(&parseHelper);
}

void XmlParseMaster::Parse(const char* data, std::uint32_t length, bool firstChunk, bool lastChunk)
{
	if (firstChunk)
	{
		Reset();
	}
	if (XML_Parse(mParser, data, length, lastChunk) == XML_STATUS_ERROR)
	{
		throw std::exception("Expat has encountered a problem with your data");
	}
}

void XmlParseMaster::ParseFromFile(std::string& filename)
{
	if (filename.size() == 0)
	{
		throw std::exception("Invalid filename");
	}

	mFileName = filename;
	std::ifstream in(filename);

	if (in.bad())
	{
		throw std::exception("This is an invalid file");
	}

	std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	Parse(s.c_str(), s.length(), true, true);

	in.close();
}

std::string XmlParseMaster::GetFileName() const
{
	return mFileName;
}

SharedData* XmlParseMaster::GetSharedData()
{
	return mSharedData;
}

void XmlParseMaster::SetSharedData(SharedData* sharedData)
{
	mSharedData = sharedData;
	mSharedData->SetXmlParseMaster(this);
}

void XmlParseMaster::StartElementHandler(void *userData, const XML_Char *name, const XML_Char **atts)
{
	SharedData * sharedData = reinterpret_cast<SharedData*>(userData);
	XmlParseMaster* parseMaster = sharedData->GetXmlParseMaster();

	if (parseMaster)
	{
		//Populate a hashmap with the attributes the Epact gives us
		HashMap<std::string, std::string> attributeHashMap;
		for (std::uint32_t i = 0; atts[i] != '\0'; i += 2)
		{
			bool inserted;
			attributeHashMap.Insert(std::string(atts[i]),std::string(atts[i+1]),inserted);
		}

		sharedData->IncrementDepth();
		for (auto it = parseMaster->mParseHelpers.begin(); it != parseMaster->mParseHelpers.end(); ++it)
		{
			std::string stringName = std::string(name);
			if ((*it)->StartElementHandler(sharedData, stringName, attributeHashMap))
			{
				break;
			}
		}
	}
}

void XmlParseMaster::EndElementHandler(void *userData, const XML_Char *name)
{
	SharedData * sharedData = reinterpret_cast<SharedData*>(userData);
	XmlParseMaster* parseMaster = sharedData->GetXmlParseMaster();

	if (parseMaster)
	{
		for (auto it = parseMaster->mParseHelpers.begin(); it != parseMaster->mParseHelpers.end(); ++it)
		{
			std::string stringName = std::string(name);
			if ((*it)->EndElementHandler(sharedData, stringName))
			{
				break;
			}
		}
		sharedData->DecrementDepth();
	}
}

void XmlParseMaster::CharDataHandler(void *userData, const XML_Char *s, int len)
{
	SharedData * sharedData = reinterpret_cast<SharedData*>(userData);
	XmlParseMaster* parseMaster = sharedData->GetXmlParseMaster();

	if (parseMaster)
	{
		for (auto it = parseMaster->mParseHelpers.begin(); it != parseMaster->mParseHelpers.end(); ++it)
		{
			std::string stringName = std::string(s);
			if ((*it)->CharDataHandler(sharedData,stringName, len))
			{
				break;
			}
		}
	}
}

void XmlParseMaster::Reset()
{
	
	for (auto it = mParseHelpers.begin(); it != mParseHelpers.end(); ++it)
	{
		(*it)->Initialize();
	}

	if (bIsClone)
	{
		auto newSharedData = mSharedData->Clone();
		delete mSharedData;
		SetSharedData(newSharedData);
	}
	else
	{
		if (mSharedData)
		{
			mSharedData->Reset();
		}
	}

	XML_ParserReset(mParser, "UTF-8");
	XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
	XML_SetCharacterDataHandler(mParser, CharDataHandler);
	XML_SetUserData(mParser, mSharedData);

}
#pragma endregion
