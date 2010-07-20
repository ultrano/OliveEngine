#include "tinyxml.h"

GL_TEST_CASE_FUNC( cdata_parse_test )
{
	TiXmlDocument doc("cdata_parse");
	doc.LoadFile("../../resource/script/xml/cdata_test.xml");
	string text = doc.RootElement()->GetText();
}