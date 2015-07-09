#pragma once
#include "XmlParseMaster.h"
#include "Scope.h"
#include "Stack.h"

namespace Library
{
	class Attribute;
	class ScopeSharedData : public XmlParseMaster::SharedData
	{
		
		RTTI_DECLARATIONS(ScopeSharedData, XmlParseMaster::SharedData);

	public:
		explicit ScopeSharedData(Scope* data);
		explicit ScopeSharedData(Attribute* data);
		~ScopeSharedData();

		virtual XmlParseMaster::SharedData* Clone() override;
		virtual void Reset() override;

		Scope* GetScope();
		Attribute* GetWorld();
		void SetScope(Scope * data);
		void SetWorld(Attribute* world);

	protected:
		Scope *mData;
		Attribute* mWorld;
		bool bIsClone;
	};

}