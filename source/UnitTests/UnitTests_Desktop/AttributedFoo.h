#pragma once
#include "Attribute.h"

namespace Unit_Tests
{
	using namespace Library;

	class AttributedFoo :public  Attribute
	{
		RTTI_DECLARATIONS(AttributedFoo, Attribute)

	public:
		AttributedFoo();
		~AttributedFoo();

		std::int32_t mExternalInteger;
		std::float_t mExternalFloat;
		glm::vec4 mExternalVector;
		glm::mat4 mExternalMatrix;
		std::string mExternalString;
		RTTI* mExternalRTTI;
		Scope* mExternalTable;
	};
}