#include "OvObject.h"
#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvProperty.h"
#include <string>
using namespace std;

OvRTTI_IMPL_PROP(OvObject,OvRefBase);
OvPROP_BAG_IMPL(OvObject);
struct OvObject::OvPimple : OvMemObject
{
	// 멤버변수들을 기술한다.
	// 멤버변수또한 되도록 캡슐화 하기 위해 핌플패턴을 적용한다.

	string			mObjectName;
	const char*		mObjectDescription;
	OvObjectID			m_hObjectID;

	//! 로딩시에 쓰이게될, 세이브시에 저장되었던 예전 핸들번호.
	//! 계층구조를 구축하는데에 표본으로 쓰인다.
	//! 어플리케이션에선 쓰일 일이 없으므로 외부로 누출시키는 인터페이스를 제공하지 않는다.
	OvObjectID			m_hOldHandle;

};

class OvObject::OvProp_Pimple : public OvProperty
{
	virtual bool	Store(OvObject* pObj, TiXmlElement& rXml)
	{
		OvAutoPtr<OvPimple>& krProp = *(OvAutoPtr<OvPimple>*)Access(pObj);
		string strName = krProp->mObjectName;
		return false;
	};
	virtual bool	Restore(OvObject* pObj, TiXmlElement& rXml){return false;};
};

void OvObject::RegisterProperties()
{
	{
		OvProp_Pimple* kpPropProtector = new OvProp_Pimple;
		kpPropProtector->SetOffset(offsetof(__this_class,m_pPimple));
		kpPropProtector->SetPropertyName("Protected");
		GetPropertyBag()->RegisterProperty(kpPropProtector);
	}
};

// OvObject::OvObject(ovloader ploader):m_pPimple(new OvObject::OvPimple)
// {
// 	m_pPimple->m_hObjectID = OvObjectManager::Instance()->AllocObjectID(this);
// 	ovstore kstore = ploader->getstore<OvObject>();
// 	kstore.get
// 
// }

OvObject::OvObject():m_pPimple(OvNew OvObject::OvPimple)
{
	m_pPimple->m_hObjectID = OvObjectManager::GetInstance()->AllocObjectID(this);
}
OvObject::~OvObject()
{
	OvObjectManager::GetInstance()->RecallObjectID(this);
	m_pPimple = NULL;
}

void	OvObject::SetName(const char* _pName)
{
	m_pPimple->mObjectName = _pName;
}
const char* OvObject::GetName()
{
	return m_pPimple->mObjectName.data();
}

const OvObjectID		OvObject::GetObjectID()
{
	return m_pPimple->m_hObjectID;
}