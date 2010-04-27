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


	//! �̱��� �Ҹ��� ȣ��� �ӽ÷� ��� �ִ� ī�޶��� �����ʹ� �̹� �׾� �ִ� ���̱� ������
	//! NULL�� �����Ϸ� �Ѵ� �ص� ����Ʈ �����Ͱ� ���������� �����ϴ� �������� ������ �����Ѵ�.
	//! �̸� �ذ��� ����� �̱����� �Ѱ��ϴ� Ŭ������ ����� ������� �͹̳������� ������Ұ� ����.
	//! Ȥ�� �޸�Ǯ���� ���� NULL�� ���� �ϸ� �ǰ�����, �� �ñⰡ �ָ��ϱ⶧���� ���� Ȯ���� �ع��� �ʿ� �Ұ� ����.

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


