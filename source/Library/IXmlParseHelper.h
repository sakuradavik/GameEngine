#pragma once
#include "HashMap.h"
#include "XmlParseMaster.h"

namespace Library
{
	class IXmlParseHelper
	{
	public:
		/**
		* Constructor
		*/
		IXmlParseHelper() = default;

		/**
		* Virtual Destructor
		*/
		virtual ~IXmlParseHelper() = default;

		/**
		* @brief Initializes this helper. Will get called just before each file is parsed.
		* This method is pure virtual and must be overridden by the derived classes
		* @param none
		* @return void
		*/
		virtual void Initialize();

		/**
		* Copy Constructor. This method is not allowed to be used
		*/
		IXmlParseHelper(const IXmlParseHelper& rhs) = delete;

		/**
		* Assignment Operator. This method is not allowed to be used
		*/
		IXmlParseHelper& operator=(const IXmlParseHelper& rhs) = delete;

		/**
		* @brief Given a string for the element name and a hashmap of attributes name-value pairs,
		* attempt to handle the element start. If it is handled by this helper return true, else return false
		* This method is pure virtual and must be overridden
		* @param String name reference and a Hashmap of name-value pairs
		* @return void
		*/
		virtual bool StartElementHandler(XmlParseMaster::SharedData * sharedData, std::string& name, HashMap<std::string, std::string> hashmap) = 0;

		/**
		* @brief Given a string for the element name, attempt to handle the element end. If this helper cannot
		* handle the element end it returns false, else it returns true
		* This method is pure virtual and must be overridden
		* @param String name of the element
		* @return void
		*/
		virtual bool EndElementHandler(XmlParseMaster::SharedData * sharedData, std::string& name) = 0;

		/**
		* @brief Duplicates this helper. This can be used instead of the copy constructor.
		* This method is pure virtual and must be overridden
		* @param none
		* @return void
		*/
		virtual IXmlParseHelper* Clone() = 0;

		/**
		* @brief Given a string buffer of character data and an integer length attempts to handle the character data.
		* The default implementation of this method returns false unless overridden by the derived classes
		* @param A string buffer of character data and an integer length, the number off bytes in the character data buffer
		* @return void
		*/
		virtual bool CharDataHandler(XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length);

	};
}
