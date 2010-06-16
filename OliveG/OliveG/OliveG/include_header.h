
#ifdef _DEBUG
#pragma comment(lib,"..\\..\\vld\\lib_d\\vldmtdll.lib");
#pragma comment(lib,"..\\..\\vld\\lib_d\\vldmt.lib");
#pragma comment(lib,"..\\..\\vld\\lib_d\\vld.lib");
#pragma comment(lib,"..\\..\\zlib\\lib\\zdll.lib");
#include "vld.h"

#endif
#include <windows.h>
#include "OvStorage.h"
//
// 압축 라이브러리 테스트
#include "zlib.h"
//


#pragma comment(lib,"..\\..\\..\\output\\lib_d\\OliveGLib_d.lib");
#pragma comment(lib,"..\\..\\..\\output\\lib_d\\GloryUnitTestKit_d.lib");
#pragma comment(lib,"..\\..\\TinyXMLLib\\lib\\tinyxmld.lib");


// #include "tinyxml.h"
// 
// #include "luabind/class.hpp"
// #include "luabind/detail/constructor.hpp"
// #include "luabind/luabind.hpp"
//using namespace luabind;

#include "OvSingletonPool.h"
#include "OvXNode.h"
#include "OvCamera.h"
#include "OvObjectProperties.h"

#include "GlBaseTestEnviroment.h"
#include "GlTestManager.h"

#include "OvExtraProperty.h"