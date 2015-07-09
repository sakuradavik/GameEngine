#pragma once
#include "IXmlParseHelper.h"

namespace Library
{
	class ScopeXmlParseHelper : public IXmlParseHelper
	{

	public:
		/**
		* Constructor
		*/
		ScopeXmlParseHelper();

		/**
		* Virtual Destructor
		*/
		~ScopeXmlParseHelper() = default;

		/**
		* Copy Constructor. This method is not allowed to be used
		*/
		ScopeXmlParseHelper(const ScopeXmlParseHelper& rhs) = delete;

		/**
		* Assignment Operator. This method is not allowed to be used
		*/
		ScopeXmlParseHelper& operator=(const ScopeXmlParseHelper& rhs) = delete;

		/**
		* @brief Given a string for the element name and a hashmap of attributes name-value pairs,
		* attempt to handle the element start. If it is handled by this helper return true, else return false
		* This method is pure virtual and must be overridden
		* @param String name reference and a Hashmap of name-value pairs
		* @return void
		*/
		virtual bool StartElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name, Library::HashMap<std::string, std::string> hashmap) override;
		
		/**
		* @brief Given a string for the element name, attempt to handle the element end. If this helper cannot
		* handle the element end it returns false, else it returns true
		* This method is pure virtual and must be overridden
		* @param String name of the element
		* @return void
		*/
		virtual bool EndElementHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& name) override;
		
		/**
		* @brief Given a string buffer of character data and an integer length attempts to handle the character data.
		* The default implementation of this method returns false unless overridden by the derived classes
		* @param A string buffer of character data and an integer length, the number off bytes in the character data buffer
		* @return void
		*/
		virtual bool CharDataHandler(Library::XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length) override;
		
		/**
		* @brief Duplicates this helper. This can be used instead of the copy constructor.
		* This method is pure virtual and must be overridden
		* @param none
		* @return void
		*/
		virtual Library::IXmlParseHelper* Clone() override;

		/**
		* @brief Initializes this helper. Will get called just before each file is parsed.
		* This method is pure virtual and must be overridden by the derived classes
		* @param none
		* @return void
		*/
		virtual void Initialize();

		//String that holds the DatumName 
		std::string mDatumName;

		//String that holds the Datum Data
		std::string mStringData;

		//Boolean indicating if we are currently parsing
		bool bIsParsing;

		//Index indicating where in the Datum to insert the data
		std::int32_t mIndex;

		//Strings that the helper is looking for in order to be able to parse
		static const std::string ScopeString;
		static const std::string NameString;
		static const std::string IndexString;
	};
}
