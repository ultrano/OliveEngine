#pragma once
#include "OvMemObject.h"
#include "OvUtility.h"

// 이 클레스는 안정성 보단 사용상의 직관성과 편리를
// 최우선으로 한다. 그만큼 복잡하지 않은 인터페이스와
// 간단한 사용법으로 어긋날수 있는 안전성을 보장하는 쪽으로 한다.
// PowerShell 에서의 Xml 을 다루는 형식을 보고 인용하기로 했다.
class OvXmlStreamer : public OvMemObject
{
	OvRTTI_DECL_ROOT(OvXmlStreamer);

public:

	OvXmlStreamer( std::string& file );
	virtual ~OvXmlStreamer();



private:


};