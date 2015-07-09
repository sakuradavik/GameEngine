#pragma once
#include "Scope.h"

namespace Library
{
	class Datum;

	class Attribute : public Scope
	{
		RTTI_DECLARATIONS(Attribute, RTTI)
			
	public:
		/**
		* Constructor
		*/
		Attribute();

		/**
		* Destructor
		*/
		virtual ~Attribute() = default;

		/**
		* Copy Constructor
		*/
		Attribute(const Attribute& rhs);

		/**
		* Assignmment Operator
		*/
		Attribute& operator=(const Attribute& rhs);

		/**
		* @brief Populate the Scope with prescribed members
		* @param none
		* @return void
		*/
		void Populate();

		/**
		* @brief Given a string, will return a bool indicating whether it is
		* the name of a presccribed attribute for this class
		* @param const string reference of the desired prescribed Attribute
		* @return A bool of whether this prescribed attribute was found
		*/
		bool IsPrescribedAttribute(const std::string& prescribedAttribute);

		/**
		* @brief Given a string, will return whether it is a name of an auxiliary
		* attribute for this object
		* @param const string reference of the desired auxiliary Attribute
		* @return A bool of whether this auxiliary attribute was found
		*/
		bool IsAuxiliaryAttribute(const std::string& auxiliaryAttribute);

		/**
		* @brief Given a string will return whether it is a name of sn attribute of this object
		* @param const string reference of the desired attribute
		* @return A bool of whether this attribute was found
		*/
		bool IsAttribute(const std::string& attributeName);

		/**
		* @brief Given a string, append a Datum to this Scope with the given name. Returns a reference to that Datum
		* @param const string reference of the desired Datum
		* @return A reference to the Datum appended
		*/
		Datum& AppendAuxiliaryAttribute(const std::string& value);

		/**
		* @brief Return an unsigned integer which is the index of the first auxiliary attributes
		* @param none
		* @return an unsigned integer which is the index of the first auxiliary sttribute
		*/
		std::uint32_t AuxiliaryBegin() const;

		virtual void Clear() override;

		const Vector<PairType*>& GetOrderVector() const;

	protected:
		union DatumValue
		{
			std::int32_t* Integer;
			std::float_t* Float;
			glm::vec4* Vector;
			glm::mat4* Matrix;
			std::string* String;
			RTTI** Pointer;
			Scope** Table;

			DatumValue() : Integer(nullptr){}
			DatumValue(std::int32_t* data) : Integer(data){}
			DatumValue(std::float_t* data) : Float(data){}
			DatumValue(glm::vec4* data) : Vector(data){}
			DatumValue(glm::mat4* data) : Matrix(data){}
			DatumValue(std::string* data) : String(data){}
			DatumValue(RTTI** data) : Pointer(data){}
			DatumValue(Scope** data) : Table(data){}
		};

		class Signature
		{
		public:
			Signature();
			Signature(const std::string name, Datum::DatumType datumType, DatumValue initialValue, std::uint32_t size, DatumValue address);

			Signature(const std::string name, Datum::DatumType datumType, std::int32_t* initialValue, std::uint32_t size, std::int32_t* address);
			Signature(const std::string name, Datum::DatumType datumType, std::float_t* initialValue, std::uint32_t size, std::float_t* address);
			Signature(const std::string name, Datum::DatumType datumType, glm::vec4* initialValue, std::uint32_t size, glm::vec4* address);
			Signature(const std::string name, Datum::DatumType datumType, glm::mat4* initialValue, std::uint32_t size, glm::mat4* address);
			Signature(const std::string name, Datum::DatumType datumType, std::string* initialValue, std::uint32_t size, std::string* address);
			Signature(const std::string name, Datum::DatumType datumType, RTTI** initialValue, std::uint32_t size, RTTI** address);
			Signature(const std::string name, Datum::DatumType datumType, Scope** initialValue, std::uint32_t size, Scope** address);

			std::string mName;
			Datum::DatumType mDatumType;
			DatumValue mInitialValue;
			std::uint32_t mSize;
			DatumValue mAddress;
		};

		static HashMap<std::uint32_t, Vector<Signature>> mSignatures;

	private:

#pragma region FunctionPointers
		typedef void(*InternalSet)(Datum&, const Signature&, const std::uint32_t&, const std::uint32_t, Scope*);
		typedef void(*ExternalSetStorage)(Datum&, const DatumValue&, const std::uint32_t);

		static void InternalUnknwon(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);
		static void InternalInteger(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);
		static void InternalFloat(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);
		static void InternalVector(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);
		static void InternalMatrix(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);
		static void InternalString(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);
		static void InternalRTTI(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);
		static void InternalScope(Datum& datum, const Signature& signature, const std::uint32_t& index, const std::uint32_t size, Scope* parent);

		static void ExternalUnknown(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);
		static void ExternalInteger(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);
		static void ExternalFloat(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);
		static void ExternalVector(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);
		static void ExternalMatrix(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);
		static void ExternalString(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);
		static void ExternalRTTI(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);
		static void ExternalScope(Datum& datum, const DatumValue& datumValue, const std::uint32_t size);

#pragma endregion

		static const InternalSet sInternalSet[];
		static const ExternalSetStorage sExternalSetStorage[];

		//TODO: add this to populate and AuxiliaryBegin() and AppendAuxiliaryAppend()
		bool bIsPopulated;

	};
}

#define InternalSignature(Name, Type, InitialValue, Size) \
{                             \
Signature s(Name, Type, InitialValue, Size, nullptr);   \
auto& it = mSignatures[TypeIdClass()];                    \
it.PushBack(s);                                           \
}

#define ExternalSignature(Name, Type, InitialValue, Size) \
{                             \
Signature s(Name, Type, nullptr, Size, InitialValue);   \
auto& it = mSignatures[TypeIdClass()];                    \
it.PushBack(s);                                           \
}