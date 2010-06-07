// 2008 12 11
// maker : Han,sang woon
// OvXObject
#pragma once
#include "OvObject.h"
#include "OvTransform.h"
#include "OvSphere.h"

// OvXObject -> eXtentionObject 
// Ȱ������ ������Ʈ (�������� ��ü����)

// Class Predeclare
class OvPoint3;
class OvQuaternion;
class OvMatrix;
class OvTransform;
OvREF_POINTER(OvXNode);
OvREF_POINTER(OvXController);
//

OvREF_POINTER(OvXObject);
class OvXObject : public OvObject
{
	OvRTTI_DECL(OvXObject);
	OvPROP_BAG_DECL(OvXObject);

	friend class OvXNode;
	friend class OvObjectFactory;
	friend class OvXController;

public :

	OvXObject();
	virtual ~OvXObject();

	//! Update
	void			Update(float _fElapse);
	virtual void	UpdateSubordinate(float _fElapse);

	//! Set Local Transform
	void			SetTranslate(OvPoint3& _rPosition);
	void			SetTranslate(float x,float y,float z);
	void			SetRotation(OvQuaternion& _rRotation);
	void			SetScale(const OvPoint3& ptAxisScale);
	void			SetScale(float _fScale);

	//! Set World Transform
	void			SetTranslateFromWorldCoord(OvPoint3&);
	void			SetTranslateFromWorldCoord(float x,float y,float z);
	void			SetRotationFromWorldCoord(OvQuaternion& );
	void			SetScaleFromWorldCoord(OvPoint3&);
	void			SetScaleFromWorldCoord(float _fScale);

	//! Get Local Transform
	OvPoint3&		GetTranslate();
	OvQuaternion&	GetRotation();
	const OvPoint3&	GetScale();

	//! Get World Transform
	const OvPoint3&		GetWorldTranslate();
	const OvQuaternion&	GetWorldRotation();
	const OvPoint3&		GetWorldScale();
	const OvMatrix&		GetWorldMatrix();
	const OvTransform&	GetWorldTransform();

	//! Which Kind
	bool			IsNode();
	bool			IsLeaf();

	//! Get Parent
	OvXObjectSPtr			GetParent();

	OvXControllerSPtr	GetHeaderObjectController();

protected:

	//! Set Object Controller (Do not use in application)
	void			PrependObjectController(OvXControllerSPtr _pController);

	//! Set Parent (Do not use in application)
	void			SetParent(OvXNodeSPtr _pParentNode);

private:

	//! �θ� �����͸� ����Ʈ �����ͷ� ��� �������
	//! �θ�� �ڽ��� ���� ���� �ִ� ��Ȳ�� �߻��ϰ� �Ǹ�
	//! �̴� ������ ������ �߱� ��Ų��.
	//! �޸𸮸Ŵ����� ���ؼ� ���α׷��� ����ɶ�
	//! �ϰ� ���� �ǰ� ������ �޸� ����Ʈ���� �޸𸮸���
	//! �߻����� �ʴ°ɷ� ��������, �޸� �󿡴� ���� �ʴ�
	//! �޸𸮷μ� �����ϰ� �ǰ� �̴� ���α׷��� ó�����Ϸ� �̾����� �� ���ɼ���
	//! ����. 
	//! ������ Ÿ������ �Ϲ������ͷθ� ���� �ִٰ� ����Ҷ��� 
	//! GetParent()�������̽��� �̿��Ͽ� ����Ʈī������ ���� ��Ű�°��̴�.
	//! �̷��� ����Ҷ��� �ּ��� ������ ���ؼ��� ��ȣ�� ������ �ְ� �ȴ�.
	//! �ڵ��� ��� �׶��׶� find�ؼ� ���� ����� �ְ�����, �̴� �ʹ� ū
	//! �����ص带 �����Ѵ�.(�ʹ� ũ��)
	OvXNode*	m_pParent;

	OvSphere	m_cCullingSphere;
	OvTransform	m_tfLocalTransform;
	OvTransform	m_tfWorldTransform;

	OvXControllerSPtr	m_spHeaderObjectController;
};
