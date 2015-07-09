#pragma once
#include "XmlParseMaster.h"
#include "Attribute.h"

namespace Library
{

	class WorldSharedData : public XmlParseMaster::SharedData
	{

		RTTI_DECLARATIONS(WorldSharedData, XmlParseMaster::SharedData);

	public:
		explicit WorldSharedData(Attribute* data);
		~WorldSharedData();

		virtual XmlParseMaster::SharedData* Clone() override;
		virtual void Reset() override;

		Scope* GetScope();
		void SetScope(Attribute * data);

	protected:
		Attribute *mData;
		bool bIsClone;
	};

}