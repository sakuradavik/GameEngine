#include "pch.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"

using namespace Library;

void IXmlParseHelper::Initialize()
{

}


bool IXmlParseHelper::CharDataHandler(XmlParseMaster::SharedData * sharedData, std::string& data, std::uint32_t length)
{
	return false;
}