// 2008 12 11
// maker : Han,sang woon
// OvXObject
#pragma once
#include "OvObject.h"
#include "OvTransform.h"
#include "OvSphere.h"
#include "OvObjectCollector.h"

// OvXObject -> eXtentionObject 
// 활동적인 오브젝트 (공간상의 객체역할)

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

	OvXObject();
	virtual ~OvXObject();

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

	//! 부모 포인터를 스마트 포인터로 들고 있을경우
	//! 부모와 자식이 서로 물고 있는 상황이 발생하게 되며
	//! 이는 약참조 현상을 야기 시킨다.
	//! 메모리매니저에 의해서 프로그램이 종료될때
	//! 일괄 삭제 되게 때문에 메모리 리포트에는 메모리릭이
	//! 발생하지 않는걸로 나오지만, 메모리 상에는 쓰지 않는
	//! 메모리로서 상주하게 되고 이는 프로그램의 처리부하로 이어지게 될 가능성이
	//! 높다. 
	//! 적당한 타협선은 일반포인터로만 물고 있다가 사용할때만 
	//! GetParent()인터페이스를 이용하여 스마트카운팅을 증가 시키는것이다.
	//! 이러면 사용할때는 최소한 삭제에 대해서는 보호를 받을수 있게 된다.
	//! 핸들을 들고 그때그때 find해서 쓰는 방법도 있겠지만, 이는 너무 큰
	//! 오버해드를 동반한다.(너무 크다)
	OvXNode*	m_pParent;

	OvSphere	m_cCullingSphere;
	OvTransform	m_tfLocalTransform;
	OvMatrix	m_localBuildMatrix;

	OvTransform	m_tfWorldTransform;
	OvMatrix	m_worldBuildMatrix;

	OvObjectCollector	m_extraComponents;

};
