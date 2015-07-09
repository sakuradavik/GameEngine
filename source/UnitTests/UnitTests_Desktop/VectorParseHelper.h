#pragma once
#include "IXmlParseHelper.h"

namespace Unit_Tests
{

	class VectorParseHelper : public Library::IXmlParseHelper
	{
	public:
		VectorParseHelper();
		~VectorParseHelper() = default;

		virtual bool StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap) override;
		virtual bool EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name) override;
		virtual bool CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length) override;
		virtual Library::IXmlParseHelper* Clone() override;
		virtual void Initialize();

		std::int32_t mMaxDepth;
		std::int32_t mStartElementCalled;
		std::int32_t mEndElementCalled;
		std::int32_t mCharElementCalled;
	};
}
