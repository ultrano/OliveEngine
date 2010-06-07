#pragma once
#include <string>

using namespace std;

class OvPropertyBag;
class	OvRTTI{

	friend bool IsStemFrom(const OvRTTI* _pBaseRTTI,const OvRTTI* _pCompareRTTI);

public:

	enum
	{
		OvRTTI_MAX_PARENT_COUNT = 2
	};

	OvRTTI(const string & classname):m_strClassName(classname)
	{
		m_pBaseClassRTTI[0] = NULL;
		m_pBaseClassRTTI[1] = NULL;
	};
	OvRTTI(const string & classname, const OvRTTI& baseclass):m_strClassName(classname)//,m_dwGeneration(baseclass.m_dwGeneration+1)
	{
		m_pBaseClassRTTI[0] = &baseclass;
	};

	OvRTTI(const string & classname, const OvRTTI& baseclass0, const OvRTTI& baseclass1):
	m_strClassName(classname)/*,
	m_dwGeneration(min(baseclass0.m_dwGeneration,baseclass1.m_dwGeneration) + 1)*/
	{
		m_pBaseClassRTTI[0] = &baseclass0;
		m_pBaseClassRTTI[1] = &baseclass1;
	};

	OvRTTI(const string & classname,OvPropertyBag* pPropertyBag):m_strClassName(classname),m_pPropertyBag(pPropertyBag)
	{
		m_pBaseClassRTTI[0] = NULL;
		m_pBaseClassRTTI[1] = NULL;
	};

	OvRTTI(const string & classname, const OvRTTI& baseclass,OvPropertyBag* pPropertyBag)
		:m_strClassName(classname)
		,m_pPropertyBag(pPropertyBag)
	{
		m_pBaseClassRTTI[0] = &baseclass;
	};
	OvRTTI(const string & classname, const OvRTTI& baseclass0, const OvRTTI& baseclass1,OvPropertyBag* pPropertyBag)
		:m_strClassName(classname)
		,m_pPropertyBag(pPropertyBag)
	{
		m_pBaseClassRTTI[0] = &baseclass0;
		m_pBaseClassRTTI[1] = &baseclass1;
	};



	inline const char*	TypeName(){return m_strClassName.data();};
	inline OvPropertyBag* PropertyBag(){return m_pPropertyBag;};
	const OvRTTI*		GetBaseRTTI(unsigned int uiIndex = 0){return m_pBaseClassRTTI[uiIndex];};

private:

	const string					m_strClassName;

	const OvRTTI*					m_pBaseClassRTTI[OvRTTI_MAX_PARENT_COUNT];

	//! 파생된 클레스가 몇번째 세대인지를 이용해
	//! RTTI 연산을 최적화 하려 했으나
	//! RTTI는 정적타임(컴파일타임)에 정해지기 때문에
	//! 제너럴변수에 옳바른 세대수가 들어오지 못한다
	//! (정적 변수에 대한 초기화 순서는 컴파일에 의해 약속 받지 못한다)
	//! 특히나 하위 클레스부터 순차적으로 초기화 되야하는 RTTI의 특성상
	//! 이 몇번째 파생된 세대인지를 구해 내는것은 무리이다.
	//! 다른 최적화 방법을 찾아보야 할것 같다.
	//const DWORD						m_dwGeneration;

	OvPropertyBag*					m_pPropertyBag;

};

inline bool IsStemFrom(const OvRTTI* _pBaseRTTI,const OvRTTI* _pCompareRTTI){

	if( ! _pBaseRTTI || ! _pCompareRTTI)
		return false;

	if (_pBaseRTTI == _pCompareRTTI)
		return true;

	//! 정적 변수이기 때문에 초기화가 약속되지 못하기 때문에 제너럴 상수의 오차가 심하다.
	/*if (_pBaseRTTI->m_dwGeneration > _pCompareRTTI->m_dwGeneration)
		return false;*/

	OvRTTI* kpRTTI = NULL;

	for (short i=0;i < OvRTTI::OvRTTI_MAX_PARENT_COUNT ;++i)
	{
		kpRTTI = (OvRTTI*)_pCompareRTTI->m_pBaseClassRTTI[i];

		if( IsStemFrom(_pBaseRTTI,kpRTTI) )
			return true;
	}

	return false;

};




#define	OvRTTI_DECL(classname) \
public:\
	static const OvRTTI msh_OvRTTI;\
	virtual const OvRTTI* QueryRTTI()const{return &msh_OvRTTI;};\
	typedef classname __this_class;

#define OvRTTI_OvRTTI(classname) (&(classname::msh_OvRTTI))

#define	OvRTTI_IMPL_NOPARENT(classname) const OvRTTI classname::msh_OvRTTI(#classname);
#define	OvRTTI_IMPL_NOPARENT_PROP(classname) const OvRTTI classname::msh_OvRTTI(#classname,&msh_OvPropertyBag);

#define	OvRTTI_IMPL(classname,parentname) const OvRTTI classname::msh_OvRTTI(#classname,parentname::msh_OvRTTI);
#define	OvRTTI_IMPL_PROP(classname,parentname) const OvRTTI classname::msh_OvRTTI(#classname,parentname::msh_OvRTTI,&msh_OvPropertyBag);

#define	OvRTTI_IMPL2(classname,parentname0,parentname1) const OvRTTI classname::msh_OvRTTI(#classname,parentname0::msh_OvRTTI,parentname1::msh_OvRTTI);
#define	OvRTTI_IMPL2_PROP(classname,parentname0,parentname1) const OvRTTI classname::msh_OvRTTI(#classname,parentname0::msh_OvRTTI,parentname1::msh_OvRTTI,&msh_OvPropertyBag);

#define OvRTTI_TypeName(classptr) ((const_cast<OvRTTI*>(classptr->QueryRTTI()))->TypeName())
#define	OvRTTI_IsEqual(classptr1,classptr2) ((classptr1&&classptr2)? ((((classptr1)->QueryRTTI()))==(((classptr2)->QueryRTTI()))):0)
#define	OvRTTI_IsClassOf(classtype,classptr1) ((classptr1)? ((&(classtype::msh_OvRTTI)) == (((classptr1)->QueryRTTI()))):0)
#define OvRTTI_IsKindOf(classtype,classptr1) ((classptr1)? (IsStemFrom((&(classtype::msh_OvRTTI)),((classptr1)->QueryRTTI()))):0)

