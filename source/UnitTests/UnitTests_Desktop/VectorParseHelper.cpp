#include "VectorParseHelper.h"
#include "XmlParseMaster.h"
#include "VectorSharedData.h"

using namespace Unit_Tests;
using namespace Library;

VectorParseHelper::VectorParseHelper() :
mMaxDepth(0), mStartElementCalled(0), mEndElementCalled(0), mCharElementCalled(0)
{
}

void VectorParseHelper::Initialize()
{
	mMaxDepth = 0;
	mStartElementCalled = 0;
	mEndElementCalled = 0;
	mCharElementCalled = 0;
}

bool VectorParseHelper::StartElementHandler(XmlParseMaster::SharedData * sharedData, std::string& name, HashMap<std::string, std::string> hashmap)
{
	++mStartElementCalled;
	VectorSharedData * data = sharedData->As<VectorSharedData>();
	if (data)
	{
		if (name.compare("Vector") == 0)
		{
			data->mVecData = glm::vec4();
			data->mState = VectorSharedData::SharedDataState::StartElement;
		}

		else if (name.compare("X") == 0)
		{
			data->mState = VectorSharedData::SharedDataState::XElement;
		}

		else if (name.compare("Y") == 0)
		{
			data->mState = VectorSharedData::SharedDataState::YElement;
		}

		else if (name.compare("Z") == 0)
		{
			data->mState = VectorSharedData::SharedDataState::ZElement;
		}

		else if (name.compare("W") == 0)
		{
			data->mState = VectorSharedData::SharedDataState::WElement;
		}

		if (name.compare("Vector") == 0 || name.compare("X") == 0 || name.compare("Y") == 0 || name.compare("Z") == 0 || name.compare("W") == 0)
		{
			if (data->Depth() > mMaxDepth)
			{
				mMaxDepth = data->Depth();
			}

			for (auto it : hashmap)
			{
				if (it.first.compare("X") == 0)
				{
					data->mVecData.x = static_cast<std::float_t>(std::atof(it.second.c_str()));
				}
				else if (it.first.compare("Y") == 0)
				{
					data->mVecData.y = static_cast<std::float_t>(std::atof(it.second.c_str()));
				}
				else if (it.first.compare("Z") == 0)
				{
					data->mVecData.z = static_cast<std::float_t>(std::atof(it.second.c_str()));
				}
				if (it.first.compare("W") == 0)
				{
					data->mVecData.w = static_cast<std::float_t>(std::atof(it.second.c_str()));
				}
			}
			return true;
		}
	}
	return false;

}

bool VectorParseHelper::EndElementHandler(XmlParseMaster::SharedData * sharedData, std::string& name)
{
	++mEndElementCalled;
	VectorSharedData * data = sharedData->As<VectorSharedData>();
	if (data)
	{
		if (name.compare("Vector") == 0)
		{
			data->mData.PushBack(data->mVecData);
		}
	}
	return false;
}

bool VectorParseHelper::CharDataHandler(XmlParseMaster::SharedData * sharedData, std::string& name, std::uint32_t length)
{
	++mCharElementCalled;
	VectorSharedData * data = sharedData->As<VectorSharedData>();
	if (data)
	{
		switch (data->mState)
		{
		case VectorSharedData::SharedDataState::StartElement:
			break;
		case VectorSharedData::SharedDataState::XElement:
			data->mVecData.x = static_cast<std::float_t>(std::atof(name.c_str()));
			data->mState = VectorSharedData::SharedDataState::CharElement;
			break;
		case VectorSharedData::SharedDataState::YElement:
			data->mVecData.y = static_cast<std::float_t>(std::atof(name.c_str()));
			data->mState = VectorSharedData::SharedDataState::CharElement;
			break;
		case VectorSharedData::SharedDataState::ZElement:
			data->mVecData.z = static_cast<std::float_t>(std::atof(name.c_str()));
			data->mState = VectorSharedData::SharedDataState::CharElement;
			break;
		case VectorSharedData::SharedDataState::WElement:
			data->mVecData.w = static_cast<std::float_t>(std::atof(name.c_str()));
			data->mState = VectorSharedData::SharedDataState::CharElement;
			break;
		default:
			break;
		};
	}
	return false;
}

IXmlParseHelper* VectorParseHelper::Clone()
{
	return new VectorParseHelper();
}
