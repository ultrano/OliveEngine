#pragma once
#include "OvUtility.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
#include "OvRenderingCommon.h"
class OvShaderConstInfo;
class OvMatrix;
OvREF_POINTER(OvVertexShader);
OvREF_POINTER(OvPixelShader);
OvREF_POINTER(OvTexture);

class OvShaderManager : public OvSingletonBase< OvShaderManager >
{
public:

	OvShaderManager();
	~OvShaderManager();

	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////*  ���ؽ� ���̴� ���� �Լ��� */////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	OvBool	SetVSConstB(const OvShaderConstInfo& rConstInfo,OvBool bCheck);
	OvBool	GetVSConstB(const OvShaderConstInfo& rConstInfo,OvBool& bCheck);

	template<typename Type_0>
	OvBool	SetVSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType);
	template<typename Type_0>
	OvBool	GetVSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType);

	OvBool	SetVSConst(const OvShaderConstInfo& rConstInfo,const OvMatrix& rType);
	OvBool	GetVSConst(const OvShaderConstInfo& rConstInfo,OvMatrix& rType);

	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////*  �ȼ� ���� �Լ��� *///////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Type_0>
	OvBool	SetPSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType);
	template<typename Type_0>
	OvBool	GetPSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType);

	OvBool	SetTexture(UINT uiSamplerIndex,OvTextureSPtr pTexture);

private:

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	OvBool	_SetVSConstF(const OvShaderConstInfo& rConstInfo,OvFloat* pConst,size_t stConstSize);
	OvBool	_GetVSConstF(const OvShaderConstInfo& rConstInfo,OvFloat* pConst,size_t stConstSize);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	OvBool	_SetPSConstF(const OvShaderConstInfo& rConstInfo,OvFloat* pConst,size_t stConstSize);
	OvBool	_GetPSConstF(const OvShaderConstInfo& rConstInfo,OvFloat* pConst,size_t stConstSize);
};

class OvShaderConstInfo : public OvMemObject
{
public:
	OvShaderConstInfo();
	OvShaderConstInfo(const OvString& T, const OvString& N, UINT R,UINT C);
	OvShaderConstInfo(UINT A, const OvString& T, const OvString& N, UINT R,UINT C);
	OvShaderConstInfo operator[](const UINT uiIndex)const;
	const UINT	ArrayCount;
	const OvString	Type;
	const OvString	Name;
	const UINT	RegistIndex;
	const UINT	ConstCount;
private:
	//! ���� �����ڴ� ���´�
	//! ����� Type,Name�� ���ڿ� �̱� ������ 
	//! ���� �����ڿ� ���� ���ڿ� ���� ������尡 �������� ���ϴ�
	//! ������ �� �𸣰����� �Լ����� ���۷����� �Ѿ OvShaderConstInfo& ���ڰ�
	//! ���� ������ ���ڷ� �Ѿ�� �Ǹ� ��û��(��Դ� 2~3�ʱ���) �����̰� �����.
	//! �Ƹ� ����ƽ �޸� �������� ���� �޸𸮷��� �޸� ���� ������尡 �ƴѰ�
	//! �ǽ��� ����.
	//! �װ� ������ OvShaderConstInfoŬ������ ���� ������ ������ ����, �׷����� �ȵǴ°�
	//! �⺻�� Ŭ������ ������ ���°��� �Ǵٰ� �����Ѵ�.
	OvShaderConstInfo(const OvShaderConstInfo& rCopy);
};

template<typename Type_0>
OvBool	OvShaderManager::SetVSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType)
{
	return _SetVSConstF(rConstInfo,(OvFloat*)&(rType),sizeof(Type_0));
}
template<typename Type_0>
OvBool	OvShaderManager::GetVSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType)
{
	return _GetVSConstF(rConstInfo,(OvFloat*)&(rType),sizeof(Type_0));
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

template<typename Type_0>
OvBool	OvShaderManager::SetPSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType)
{
	return _SetPSConstF(rConstInfo,(OvFloat*)&(rType),sizeof(Type_0));
}
template<typename Type_0>
OvBool	OvShaderManager::GetPSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType)
{
	return _GetPSConstF(rConstInfo,(OvFloat*)&(rType),sizeof(Type_0));
}
#define CONST_DECLARE_IN_APPLICATION
#include "OvPShaderConst.h"
#include "OvVShaderConst.h"
#undef CONST_DECLARE_IN_APPLICATION