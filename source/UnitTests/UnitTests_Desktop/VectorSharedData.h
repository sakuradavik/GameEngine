#pragma once
#pragma once
#include "XmlParseMaster.h"
#include "Vector.h"
#include "glm.hpp"

namespace Unit_Tests
{
	class VectorSharedData : public Library::XmlParseMaster::SharedData
	{
		RTTI_DECLARATIONS(VectorSharedData, Library::XmlParseMaster::SharedData);

	public:
		VectorSharedData(Library::Vector<glm::vec4> data = Library::Vector<glm::vec4>());
		~VectorSharedData() = default;

		virtual Library::XmlParseMaster::SharedData* Clone() override;
		virtual void Reset() override;

		enum class SharedDataState
		{
			Invalid,
			StartElement,
			CharElement,
			EndElement,
			XElement,
			YElement,
			ZElement,
			WElement,
			Maximum
		};

		SharedDataState mState;
		Library::Vector<glm::vec4> mData;
		glm::vec4 mVecData;
	};
}
