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

	LPDIRECT3DVERTEXSHADER9	CreateVertexShaderFromFile( const string& file, const string& func, const string& version, LPD3DXINCLUDE includer = NULL);
	LPDIRECT3DPIXELSHADER9	CreatePixelShaderFromFile( const string& file, const string& func, const string& version, LPD3DXINCLUDE includer = NULL);

	OvVertexShaderSPtr CreateVertexShaderFromCode( const string& code, const string& func, const string& version, LPD3DXINCLUDE includer = NULL);
	OvPixelShaderSPtr CreatePixelShaderFromCode( const string& code, const string& func, const string& version, LPD3DXINCLUDE includer = NULL);

	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////*  ���ؽ� ���̴� ���� �Լ��� */////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	bool	SetVSConstB(const OvShaderConstInfo& rConstInfo,bool bCheck);
	bool	GetVSConstB(const OvShaderConstInfo& rConstInfo,bool& bCheck);

	template<typename Type_0>
	bool	SetVSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType);
	template<typename Type_0>
	bool	GetVSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType);

	bool	SetVSConst(const OvShaderConstInfo& rConstInfo,const OvMatrix& rType);
	bool	GetVSConst(const OvShaderConstInfo& rConstInfo,OvMatrix& rType);

	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////*  �ȼ� ���� �Լ��� *///////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Type_0>
	bool	SetPSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType);
	template<typename Type_0>
	bool	GetPSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType);

	bool	SetTexture(UINT uiSamplerIndex,OvTextureSPtr pTexture);

private:

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	bool	_SetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);
	bool	_GetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	bool	_SetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);
	bool	_GetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);
};

class OvShaderConstInfo : public OvMemObject
{
public:
	OvShaderConstInfo();
	OvShaderConstInfo(const string& T, const string& N, UINT R,UINT C);
	OvShaderConstInfo(UINT A, const string& T, const string& N, UINT R,UINT C);
	OvShaderConstInfo operator[](const UINT uiIndex)const;
	const UINT	ArrayCount;
	const string	Type;
	const string	Name;
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
bool	OvShaderManager::SetVSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType)
{
	return _SetVSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}
template<typename Type_0>
bool	OvShaderManager::GetVSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType)
{
	return _GetVSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

template<typename Type_0>
bool	OvShaderManager::SetPSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType)
{
	return _SetPSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}
template<typename Type_0>
bool	OvShaderManager::GetPSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType)
{
	return _GetPSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}