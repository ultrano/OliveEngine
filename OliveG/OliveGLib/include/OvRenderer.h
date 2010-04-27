#pragma once
#include "OvUtility.h"
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvSingleton.h"

// Class Predeclare
class OvMatrix;
class OvGeometry;
class OvValueStream;
class OvPoint2;
OvREF_POINTER(OvCamera);
OvREF_POINTER(OvXObject);
OvREF_POINTER(OvGeometry);
OvREF_POINTER(OvMesh);
OvREF_POINTER(OvTexture);
OvREF_POINTER(OvSurface);
OvREF_POINTER(OvRenderTarget);
//

class OvRenderer : public OvMemObject
{
	OvRTTI_DECL(OvRenderer);
	OvSingletonEx_DECL(OvRenderer);
public:


	bool		GenerateRenderer(HWND _hTargetWindowHangle);


	//! 싱글톤 소멸자 호출시 임시로 잡고 있는 카메라의 포인터는 이미 죽어 있는 것이기 때문에
	//! NULL로 셋팅하려 한다 해도 스마트 포인터가 내부적으로 접근하는 과정에서 덤프를 유발한다.
	//! 이를 해결할 방법은 싱글톤을 총괄하는 클레스를 만들고 명시적인 터미네이팅을 해줘야할것 같다.
	//! 혹은 메모리풀보다 먼저 NULL을 셋팅 하면 되겠지만, 그 시기가 애매하기때문에 좀더 확실한 해법이 필요 할것 같다.

	void			DrawMesh(OvMeshSPtr pMesh);

	bool			ClearTarget();
	bool			BeginTarget();
	bool			EndTarget();
	bool			PresentTarget();

	DWORD			GetRenderWindowHeight();
	DWORD			GetRenderWindowWidth();

	bool			ExtentionVertexBuffer(DWORD dBufferSize);
	bool			ExtentionIndexBuffer(DWORD dBufferSize);

	OvTextureSPtr	LoadTexture(const char* pFile);
	OvTextureSPtr	CreateTexture(size_t stWidth,size_t stHeight,size_t stMipLevel,DWORD dUsage,DWORD dFormat);
	OvSurfaceSPtr	CreateDepthStencilSurface(size_t stWidth,size_t stHeight,DWORD dFormat,DWORD dMultiSample,DWORD dMultiSampleQuality,bool bIdDiscard);



	void*			GetDevice();

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};


