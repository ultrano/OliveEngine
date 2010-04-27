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
	// ����������� ����Ѵ�.
	// ����������� �ǵ��� ĸ��ȭ �ϱ� ���� ���������� �����Ѵ�.

	string			mObjectName;
	const char*		mObjectDescription;
	OvObjectID			m_hObjectID;

	//! �ε��ÿ� ���̰Ե�, ���̺�ÿ� ����Ǿ��� ���� �ڵ��ȣ.
	//! ���������� �����ϴµ��� ǥ������ ���δ�.
	//! ���ø����̼ǿ��� ���� ���� �����Ƿ� �ܺη� �����Ű�� �������̽��� �������� �ʴ´�.
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