// 2008 12 11
// maker : Han,sang woon
// OvXObject
#pragma once
#include "OvObject.h"

// OvXObject -> eXtentionObject 
// 활동적인 오브젝트 (공간상의 객체역할)

// Class Predeclare
class OvPoint3;
class OvQuaternion;
class OvMatrix;
class OvTransform;
OvREF_POINTER(OvXNode);
OvREF_POINTER(OvObjectController);
//

OvREF_POINTER(OvXObject);
class OvXObject : public OvObject
{
	OvRTTI_DECL(OvXObject);
	OvPROP_BAG_DECL(OvXObject);

	friend class OvXNode;
	friend class OvObjectFactory;
	friend class OvObjectController;

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

	OvObjectControllerSPtr	GetHeaderObjectController();

protected:

	//! Set Object Controller (Do not use in application)
	void			PrependObjectController(OvObjectControllerSPtr _pController);

	//! Set Parent (Do not use in application)
	void			SetParent(OvXNodeSPtr _pParentNode);

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
	class OvProp_Pimple;
};
