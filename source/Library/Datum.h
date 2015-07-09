#pragma once
#include "glm.hpp"
#include "gtx/string_cast.hpp"

namespace Library
{
	class Scope;
	class RTTI;

	class Datum
	{
	public:
		/**
		* Enum of Data Types permitted
		*/
		enum class DatumType
		{
			Unknown = 0,
			Integer,
			Float,
			Vector,
			Matrix,
			String,
			Pointer,
			Table,
			Maximum
		};

		/**
		* Default Constructor
		*/
		explicit Datum(DatumType dataType = DatumType::Unknown, std::uint32_t size = 0U);

		/**
		* Copy Constructor
		*/
		Datum(const Datum& rhs);

		

#pragma region AssignmentOperator
		/**
		* Assignment Operator for Datum Type and each data type
		*/
		Datum& operator=(const Datum& rhs);

		Datum& operator=(const std::int32_t& rhs);
		Datum& operator=(const std::float_t& rhs);
		Datum& operator=(const glm::vec4& rhs);
		Datum& operator=(const glm::mat4& rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(RTTI* rhs);
		Datum& operator=(Scope* rhs);

#pragma endregion

		/**
		* Deconstructor for Datum
		*/
		~Datum();

		/**
		* Will take a Datum Type and assign it to this datum if a type has not already been assigned
		*/
		void SetType(const DatumType datumType);

		/**
		* Returns the type of the datum
		*/
		DatumType GetType() const;

		/**
		* Returns the Size of the Datum
		*/
		std::uint32_t Size() const;

		/**
		* Sets the size of the array of data
		*/
		void SetSize(const std::uint32_t newSize);

		/**
		* Clears the datum's data, will delete the underlying data
		*/
		void Clear();

#pragma region SetStorage
		/**
		* Will allow this datum to become external and store the data of an external type
		* It will not allow us to change the data's memorie or expand it, only shrink it
		*/

		void SetStorage(std::int32_t* data, std::uint32_t size);
		void SetStorage(std::float_t* data, std::uint32_t size);
		void SetStorage(glm::vec4* data, std::uint32_t size);
		void SetStorage(glm::mat4* data, std::uint32_t size);
		void SetStorage(std::string* data, std::uint32_t size);
		void SetStorage(RTTI** data, std::uint32_t size);
		void SetStorage(Scope** data, std::uint32_t size);

#pragma endregion

#pragma region EqualOperator
		/**
		* Will compare the data between this datum and the one on th rhs. Will do a logical compare
		* Will return true if they are equal to each other
		*/
		bool operator==(const Datum& rhs) const;
		bool operator==(const std::int32_t& rhs) const;
		bool operator==(const std::float_t& rhs) const;
		bool operator==(const glm::vec4& rhs) const;
		bool operator==(const glm::mat4& rhs) const;
		bool operator==(const std::string& rhs) const;
		bool operator==(const RTTI* rhs) const;
		bool operator==(const Scope* rhs) const;

#pragma endregion
		
#pragma region NoEqualOperator
		/**
		* Will compare the data between this datum and the one on th rhs. Will do a logical compare
		* Will return true if they are not equal to each other
		*/

		bool operator!=(const Datum& rhs) const;
		bool operator!=(const std::int32_t& rhs) const;
		bool operator!=(const std::float_t& rhs) const;
		bool operator!=(const glm::vec4& rhs) const;
		bool operator!=(const glm::mat4& rhs) const;
		bool operator!=(const std::string& rhs) const;
		bool operator!=(const RTTI* rhs) const;
		bool operator!=(const Scope* rhs) const;
#pragma endregion

#pragma region Set
		/**
		* Will set the value of the datum at the given index
		*/

		void Set(const std::int32_t& data, std::uint32_t size = 0U);
		void Set(const std::float_t& data, std::uint32_t size = 0U);
		void Set(const glm::vec4& data, std::uint32_t size = 0U);
		void Set(const glm::mat4& data, std::uint32_t size = 0U);
		void Set(const std::string& data, std::uint32_t size = 0U);
		void Set(RTTI* data, std::uint32_t size = 0U);
		void Set(Scope* data, std::uint32_t size = 0U);

#pragma endregion

#pragma region Get
		/**
		* Will return the data at the given index
		*/
		std::int32_t& GetInteger(std::uint32_t index = 0);
		std::float_t&GetFloat(std::uint32_t index = 0);
		glm::vec4& GetVector(std::uint32_t index = 0);
		glm::mat4& GetMatrix(std::uint32_t index = 0);
		std::string& GetString(std::uint32_t index = 0);
		RTTI* GetRTTI(std::uint32_t index = 0);
		Scope* GetScope(std::uint32_t index = 0);

#pragma endregion

		Scope& operator[](std::uint32_t index);

		/**
		* Will take a string and convert it the appropriate datum type and initialize the data
		*/
		void SetFromString(const std::string data, const std::uint32_t size = 0U);

		/**
		* Will return a string representation of the data
		*/
		std::string ToString(std::uint32_t size= 0) const;

		bool IsExternal();

	private:
		union DatumValue
		{
			std::int32_t* Integer;
			std::float_t* Float;
			glm::vec4* Vector;
			glm::mat4* Matrix;
			std::string* String;
			RTTI** RTTI;
			Scope** Scope;
			void* Void;

			DatumValue() : Integer(nullptr){}
		};

#pragma region FunctionTypes

		typedef void(*AllocFunction)(Datum&, std::uint32_t);
		typedef void(*CopyFunction)(const DatumValue&, DatumValue&, std::uint32_t);
		typedef void(*DeAllocFunction)(Datum&);
		typedef std::string(*ToStringFunction)(const Datum&, std::uint32_t);
		typedef bool(*CompareTo)(const Datum&, const Datum&);
		typedef void(*StringToData)(const std::string, const std::uint32_t, Datum& );

#pragma endregion

#pragma region FunctionPointerDecleration

		static void AllocUnknown(Datum& data, std::uint32_t size);
		static void AllocInteger(Datum& data, std::uint32_t size);
		static void AllocFloat(Datum& data, std::uint32_t size);
		static void AllocVector(Datum& data, std::uint32_t size);
		static void AllocMatrix(Datum& data, std::uint32_t size);
		static void AllocString(Datum& data, std::uint32_t size);
		static void AllocRTTI(Datum& data, std::uint32_t size);
		static void AllocScope(Datum& data, std::uint32_t size);

		static void CopyUnknown(const DatumValue& rhs, DatumValue& value, std::uint32_t size);
		static void CopyInteger(const DatumValue& rhs, DatumValue& value, std::uint32_t size);
		static void CopyFloat(const DatumValue& rhs, DatumValue& value, std::uint32_t size);
		static void CopyVector(const DatumValue& rhs, DatumValue& value, std::uint32_t size);
		static void CopyMatrix(const DatumValue& rhs, DatumValue& value, std::uint32_t size);
		static void CopyString(const DatumValue& rhs, DatumValue& value, std::uint32_t size);
		static void CopyRTTI(const DatumValue& rhs, DatumValue& value, std::uint32_t size);

		static void DeAllocUnknown(Datum& data);
		static void DeAllocInteger(Datum& data);
		static void DeAllocFloat(Datum& data);
		static void DeAllocVector(Datum& data);
		static void DeAllocMatrix(Datum& data);
		static void DeAllocString(Datum& data);
		static void DeAllocRTTI(Datum& data);

		static std::string ToStringUnknown(const Datum& data, std::uint32_t size);
		static std::string ToStringInteger(const Datum& data, std::uint32_t size);
		static std::string ToStringFloat(const Datum& data, std::uint32_t size);
		static std::string ToStringVector(const Datum& data, std::uint32_t size);
		static std::string ToStringMatrix(const Datum& data, std::uint32_t size);
		static std::string ToStringString(const Datum& data, std::uint32_t size);
		static std::string ToStringRTTI(const Datum& data, std::uint32_t size);

		static bool CompateToUnknown(const Datum& rhs, const Datum& data);
		static bool CompateToInteger(const Datum& rhs, const Datum& data);
		static bool CompateToFloat(const Datum& rhs, const Datum& data);
		static bool CompateToVector(const Datum& rhs, const Datum& data);
		static bool CompateToMatrix(const Datum& rhs, const Datum& data);
		static bool CompateToString(const Datum& rhs, const Datum& data);
		static bool CompateToRTTI(const Datum& rhs, const Datum& data);
		static bool CompateToScope(const Datum& rhs, const Datum& data);
		
		static void StringToDataUnknown(const std::string data, const std::uint32_t size, Datum& datum);
		static void StringToDataInteger(const std::string data, const std::uint32_t size, Datum& datum);
		static void StringToDataFloat(const std::string data, const std::uint32_t size, Datum& datum);
		static void StringToDataVector(const std::string data, const std::uint32_t size, Datum& datum);
		static void StringToDataMatrix(const std::string data, const std::uint32_t size, Datum& datum);
		static void StringToDataString(const std::string data, const std::uint32_t size, Datum& datum);
		static void StringToDataRTTI(const std::string data, const std::uint32_t size, Datum& datum);

#pragma endregion

		DatumType mDatumType;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		DatumValue mContainer;
		bool bIsExternal;

		static const AllocFunction sAllocFunctions[];
		static const CopyFunction sCopyFunctions[];
		static const DeAllocFunction sDeAllocFunctions[];
		static const ToStringFunction sToStringFunction[];
		static const CompareTo sCompareToFunction[];
		static const StringToData sStringToData[];
	};
}