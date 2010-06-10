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

	OvRTTI(const string & classname)
		:m_strClassName(classname)
		,m_pPropertyBag(NULL)
	{
		m_pBaseClassRTTI[0] = NULL;
		m_pBaseClassRTTI[1] = NULL;
	};
	OvRTTI(const string & classname, const OvRTTI& baseclass)
		:m_strClassName(classname)
		,m_pPropertyBag(NULL)
	{
		m_pBaseClassRTTI[0] = &baseclass;
	};

	void					SetPropertyBag(OvPropertyBag* propBag){m_pPropertyBag = propBag;};
	inline OvPropertyBag*	PropertyBag(){return m_pPropertyBag;};
	inline const char*	TypeName(){return m_strClassName.data();};
	const OvRTTI*		GetBaseRTTI(unsigned int uiIndex = 0){return m_pBaseClassRTTI[uiIndex];};

private:

	const string					m_strClassName;

	const OvRTTI*					m_pBaseClassRTTI[OvRTTI_MAX_PARENT_COUNT];

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




#define	OvRTTI_DECL_ROOT(classname) \
private:\
	static const OvRTTI msh_OvRTTI;\
public:\
	static const OvRTTI*	GetRTTI(){return &classname::msh_OvRTTI;};\
	virtual const OvRTTI* QueryRTTI()const{return &msh_OvRTTI;};\
	typedef classname __this_class;

#define	OvRTTI_DECL(classname) \
private:\
	static const OvRTTI msh_OvRTTI;\
public:\
	static const OvRTTI*	GetRTTI(){return &classname::msh_OvRTTI;};\
	static const OvRTTI*	GetBaseRTTI(){return __super::GetRTTI();};\
	virtual const OvRTTI*	QueryRTTI()const{return &classname::msh_OvRTTI;};\
	typedef classname __this_class;


#define	OvRTTI_IMPL_NOPARENT(classname) const OvRTTI classname::msh_OvRTTI(#classname);

#define	OvRTTI_IMPL(classname) const OvRTTI classname::msh_OvRTTI(#classname,*(classname::GetBaseRTTI()));

#define OvRTTI_TypeName(classptr) ((const_cast<OvRTTI*>(classptr->QueryRTTI()))->TypeName())
#define	OvRTTI_IsEqual(classptr1,classptr2) ((classptr1&&classptr2)? ((((classptr1)->QueryRTTI()))==(((classptr2)->QueryRTTI()))):0)

#define	OvRTTI_IsClassOf(classtype,classptr1) ((classptr1)? (((classtype::GetRTTI())) == (((classptr1)->QueryRTTI()))):0)
#define OvRTTI_IsKindOf(classtype,classptr1) ((classptr1)? (IsStemFrom(((classtype::GetRTTI())),((classptr1)->QueryRTTI()))):0)

