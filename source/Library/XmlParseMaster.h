#pragma once
#include "RTTI.H"
#include "SList.h"
#include "expat.h"

namespace Library
{
	class IXmlParseHelper;

	class XmlParseMaster final
	{
	public:
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI);

		public:
			/**
			* Constructor
			*/
			SharedData();
			
			/**
			* Deconstructor
			*/
			virtual ~SharedData();

			/**
			* Copy Constructor. It is not allowed to be used.
			*/
			SharedData(const SharedData& rhs) = delete;

			/**
			* Copy Constructor. It is not allowed to be used.
			*/
			SharedData& operator=(const SharedData& rhs) = delete;

			/**
			* @brief “virtual constructor” which returns the address of a SharedData object which has the same 
			* internal state as “this” except ready for a fresh file
			* @param none
			* @return SharedData*
			*/
			virtual SharedData* Clone();

			/**
			* @brief given the address of an XmlParseMaster, assign it to a private member
			* @param XmlParseMaster the new XmlParseMaster for this SharedData
			* @return void
			*/
			void SetXmlParseMaster(XmlParseMaster* parseMaster);

			/**
			* @brief return the address of the XmlParseMaster associated with this object
			* @param none
			* @return XmlParseMaster the xmlParseMaster for this SharedData
			*/
			XmlParseMaster* GetXmlParseMaster();

			/**
			* @brief increment a “nesting depth” counter. This gets incremented upon the start of each element
			* @param none
			* @return void
			*/
			void IncrementDepth();

			/**
			* @brief ecrement a “nesting depth” counter. This gets decremented upon the end of each element
			* @param none
			* @return void
			*/
			void DecrementDepth();

			/**
			* @brief return the current nesting depth
			* @param none
			* @return the depth of this SharedData
			*/
			std::int32_t Depth();

			/**
			* @brief Will reset any member data in the SharedData
			* @param none
			* @return void
			*/
			virtual void Reset();

		private:
			XmlParseMaster* mParseMaster;
			std::uint32_t mDepth;
		};

		/**
		* Constructor
		*/
		XmlParseMaster(SharedData* sharedData);

		/*
		* Deconstructor
		*/
		~XmlParseMaster();

		/**
		* @brief duplicate this object and return its address. This differs from a copy constructor in that this class uses Expat, 
		* which provides no facility for exact duplication of its internal state
		* @param none
		* @return XmlParseMaster a cloned version of this XmlParseMaster
		*/
		XmlParseMaster* Clone();

		/**
		* @brief given a reference to an IXmlParseHelper object, add it to the list
		* @param parseHelper that will be registerd with this parseMaster 
		* @return void
		*/
		void AddHelper(IXmlParseHelper& parseHelper);

		/**
		* @brief given a reference to an IXmlParseHelper object, remove it from the list
		* @param parseHelper to be removed
		* @return void
		*/
		void RemoveHelper(IXmlParseHelper& parseHelper);

		/**
		* @brief a character buffer of XML data, the number of characters in that buffer 
		* and a bool indicating whether this is the last chunk of text for this file, parse the text
		* @param data to be parsed, length of the data passed in, if the parseMaster should be reset , 
		* bool indicatin if this is the last time you are reading this
		* @return void
		*/
		void Parse(const char* data, std::uint32_t length, bool firstChunk, bool lastChunk);

		/**
		* @brief given a filename, read in the file and parse it
		* @param FileName to be read
		* @return void
		*/
		void ParseFromFile(std::string& filename);

		/**
		* @brief return the path for the file being parsed, passed into ParseFromFile
		* @param void
		* @return String of the filename
		*/
		std::string GetFileName() const;

		/**
		* @brief return the address of the SharedData associated with this object
		* @param none
		* @return return the SharedData in the parse master
		*/
		SharedData* GetSharedData();

		/**
		* @brief given the address of a SharedData object, associate it with this object
		* @param SharedData of this parsemaster
		* @return void
		*/
		void SetSharedData(SharedData* sharedData);

	private:
		static void StartElementHandler(void *userData, const XML_Char *name, const XML_Char **atts);
		static void EndElementHandler(void *userData, const XML_Char *name);
		static void CharDataHandler(void *userData, const XML_Char *s, int len);

		void Reset();

		SList<IXmlParseHelper*> mParseHelpers;
		XML_Parser mParser;
		bool bIsClone;
		SharedData* mSharedData;
		std::string mFileName;
	};
}