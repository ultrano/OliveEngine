
#ifdef _DEBUG
#pragma comment(lib,"..\\..\\vld\\lib_d\\vldmtdll.lib");
#pragma comment(lib,"..\\..\\vld\\lib_d\\vldmt.lib");
#pragma comment(lib,"..\\..\\vld\\lib_d\\vld.lib");
#pragma comment(lib,"..\\..\\zlib\\lib\\zdll.lib");
#include "vld.h"

#endif
#include <windows.h>
#include "OvMain.h"
#include "OvObjectCollector.h"
#include "OvCoreCommander.h"
#include "OvMassBuilder.h"
#include "OvCoreCommandProxy.h"

#include "OvRenderTarget.h"
#include "OvTexture.h"
#include "OvSurface.h"

// 단위 테스트 (쉐이더)
#include "OvVertexShader.h"
#include "OvPixelShader.h"
#include "OvMesh.h"
#include "OvMaterial.h"
#include "OvXMLImportUtility.h"
#include "OvMaterialManager.h"
#include "OvRenderableObject.h"
#include "OvStorage.h"
//
// 압축 라이브러리 테스트
#include "zlib.h"
//
#include "OvCameraController.h"


#pragma comment(lib,"..\\..\\..\\output\\lib_d\\OliveG.lib");
#pragma comment(lib,"..\\..\\TinyXMLLib\\lib\\tinyxmld.lib");


#include "tinyxml.h"

#include "luabind/class.hpp"
#include "luabind/detail/constructor.hpp"
#include "luabind/luabind.hpp"
using namespace luabind;

LRESULT	CALLBACK	WindowCallback(HWND _hWnd,UINT _iMessage,WPARAM _wParam,LPARAM _lParam)
{
	return 0;

};

template<typename T>
struct SSafeRelease
{
	SSafeRelease(T* pT):mT(pT){};
	~SSafeRelease()
	{
		if (mT)
		{
			mT->Release();
		}
	}
	T* mT;
};
#include "OvPropertyBag.h"
#include "OvPropertyNode.h"
#include "OvProperty.h"
int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	OvSingletonPool::StartUp();
	{
		OvXNodeSPtr kpNode = new OvXNode;
		kpNode->SetName("써너버 비취");
		kpNode->AttachChild(new OvXNode);
		
		OvRTTI* kpRTTI = const_cast<OvRTTI*>(kpNode->QueryRTTI());
		while (kpRTTI)
		{
			OvPropertyBag* kpPropBag = kpRTTI->PropertyBag();
			if (kpPropBag)
			{
				OvPropertyNode* kpPropList = kpPropBag->BeginProperty();
				while (kpPropList)
				{
					TiXmlElement kElement("Unknown");
					OvProperty* kpProperty = kpPropList->GetProperty();
					kpProperty->Store(kpNode.GetRear(),kElement);
					kpPropList = kpPropList->GetNext();
				}
			}
			kpRTTI = const_cast<OvRTTI*>(kpRTTI->GetBaseRTTI());
		}
		
		

	}
	OvSingletonPool::ShutDown();
};
