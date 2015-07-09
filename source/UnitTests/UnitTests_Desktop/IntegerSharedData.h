#pragma once
#include "XmlParseMaster.h"
#include "Vector.h"

namespace Unit_Tests
{
	class IntegerSharedData : public Library::XmlParseMaster::SharedData
	{
		RTTI_DECLARATIONS(IntegerSharedData, Library::XmlParseMaster::SharedData);

	public:
		IntegerSharedData();
		~IntegerSharedData() = default;

		virtual Library::XmlParseMaster::SharedData* Clone() override;
		virtual void Reset() override; 

		enum class SharedDataState
		{
			Invalid,
			StartElement,
			CharElement,
			EndElement,
			Maximum
		};

		SharedDataState mState;
		std::string mStringData;
		Library::Vector<std::int32_t> mData;
	};

}