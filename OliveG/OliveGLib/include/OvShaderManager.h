#pragma once
#include "OvUtility.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
class OvShaderConstInfo;
class OvMatrix;
OvREF_POINTER(OvTexture);

class OvShaderManager : public OvSingletonBase< OvShaderManager >
{
public:

	OvShaderManager();
	~OvShaderManager();

	////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////*  버텍스 쉐이더 관련 함수들 */////////////////////////////////////
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
	/////////////////////////*  픽셀 관련 함수들 *///////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Type_0>
	bool	SetPSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType);
	template<typename Type_0>
	bool	GetPSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType);

	bool	SetTexture(UINT uiSamplerIndex,OvTextureSPtr pTexture);

private:


	bool	SetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);
	bool	GetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////

	bool	SetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);
	bool	GetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize);
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
	//! 복사 생성자는 막는다
	//! 멤버중 Type,Name이 문자열 이기 때문에 
	//! 복사 생성자에 의한 문자열 복사 오버헤드가 생각보다 심하다
	//! 이유는 잘 모르겠지만 함수에서 레퍼런스로 넘어간 OvShaderConstInfo& 인자가
	//! 복사 생성자 인자로 넘어가게 되면 엄청난(길게는 2~3초까지) 딜레이가 생긴다.
	//! 아마 스테틱 메모리 영역에서 스텍 메모리로의 메모리 복사 오버헤드가 아닌가
	//! 의심해 본다.
	//! 그걸 떠나서 OvShaderConstInfo클래스는 복사 생성될 이유가 없고, 그래서도 안되는게
	//! 기본인 클래스기 때문에 막는것이 옳다고 생각한다.
	OvShaderConstInfo(const OvShaderConstInfo& rCopy);
};

template<typename Type_0>
bool	OvShaderManager::SetVSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType)
{
	return SetVSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}
template<typename Type_0>
bool	OvShaderManager::GetVSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType)
{
	return GetVSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

template<typename Type_0>
bool	OvShaderManager::SetPSConst(const OvShaderConstInfo& rConstInfo,const Type_0& rType)
{
	return SetPSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}
template<typename Type_0>
bool	OvShaderManager::GetPSConst(const OvShaderConstInfo& rConstInfo,Type_0& rType)
{
	return GetPSConstF(rConstInfo,(float*)&(rType),sizeof(Type_0));
}