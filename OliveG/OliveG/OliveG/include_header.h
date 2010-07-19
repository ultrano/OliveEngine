#pragma once
#ifdef _DEBUG
#pragma comment(lib,"..\\..\\vld\\lib_d\\vldmtdll.lib");
#pragma comment(lib,"..\\..\\vld\\lib_d\\vldmt.lib");
#pragma comment(lib,"..\\..\\vld\\lib_d\\vld.lib");
#pragma comment(lib,"..\\..\\zlib\\lib\\zdll.lib");
#include "vld.h"


// #ifdef _WINDOWS
// #ifdef _DEBUG
// 		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
// 
// 		_CrtSetBreakAlloc(2828);
// #endif
// #endif


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

#include "GlTestHeader.h"

#include "OliveValue.h"

#include "OvMeshBuilder.h"
#include "OvRenderer.h"
#include <windows.h>
#include "OvMesh.h"

#include "OvShaderManager.h"
#include "OvMaterialManager.h"
#include "OvTransform.h"
#include "OvModel.h"
#include "OvTexture.h"

#include "OvInputDevice.h"

#include "OvTextureLoader.h"
#include "OvXmlMeshLoader.h"
#include "OvFileMeshLoader.h"
#include "OvResourceManager.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"