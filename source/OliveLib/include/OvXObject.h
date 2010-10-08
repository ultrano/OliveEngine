// 2008 12 11
// maker : Han,sang woon
// OvXObject
#pragma once
#include "OvObject.h"
#include "OvTransform.h"
#include "OvSphere.h"
#include "OvObjectCollector.h"
#include "OvBitFlags.h"

// OvXObject -> eXtentionObject 
// Ȱ������ ������Ʈ (�������� ��ü����)

// Class Predeclare
class OvPoint3;
class OvQuaternion;
class OvMatrix;
OvREF_POINTER(OvXNode);
OvREF_POINTER(OvXComponent);
//

OvREF_POINTER(OvXNode);
OvREF_POINTER(OvXObject);
class OvXObject : public OvObject
{
	OvRTTI_DECL(OvXObject);
	OvPROPERTY_BAG_DECL(OvXObject);

	friend class OvXNode;
	friend class OvObjectFactory;
	friend class OvXComponent;

public :
	enum CONTROL_FLAG
	{
		UPDATABLE,
		VISIBLE,
	};
	OvXObject();
	virtual ~OvXObject();

	void			SetControlFlag( CONTROL_FLAG flag, bool check );
	bool			GetControlFlag( CONTROL_FLAG flag );

	//! Update
	void			Update(float _fElapse);

	//! updating for application
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
	const OvMatrix&	GetLocalMatrix();

	//! Get World Transform
	const OvPoint3&		GetWorldTranslate();
	const OvQuaternion&	GetWorldRotation();
	const OvPoint3&		GetWorldScale();
	const OvMatrix&		GetWorldMatrix();

	//! Which Kind
	bool			IsNode();
	bool			IsLeaf();

	//! Get Parent
	OvXNodeSPtr			GetAttachedNode();

	bool				GetComponents( OvObjectCollector& extraComponents );
	OvXComponentSPtr	RemoveComponent( const OvObjectSPtr component );
	OvXComponentSPtr	RemoveComponent( const OvObjectID& compoentID );

private:

	//! Set Object Controller (Do not use in application)
	bool			_equip_component( OvXComponentSPtr component );
	bool			_remove_component( OvXComponentSPtr component );

	//! Set Parent (Do not use in application)
	void			_set_parent(OvXNodeSPtr _pParentNode);

	//! Updating for system (Do not override in application, Use the "UpdateSubordinate" Method)
	virtual void	_update_system( float _fElapse );

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
	OvMatrix	m_localBuildMatrix;

	OvTransform	m_tfWorldTransform;
	OvMatrix	m_worldBuildMatrix;

	OvObjectCollector	m_extraComponents;

	Ov8SetFlags	m_controlFlags;

};
