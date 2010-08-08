// 2008 12 11
// maker : Han,sang woon
// OvMSObject
#pragma once
#include "OvObject.h"
#include "OvAutoPtr.h"

// WDObject -> WorldObject 
// 활동적인 오브젝트 (공간상의 객체역할)

// Class Predeclare
class OvPoint3;
class OvQuaternion;
class OvTransform;
//

OvREF_POINTER(OvMSObject);
class OvMSObject : public OvObject
{
	friend class OvNode;
	friend class OvObjectController;
	OvRTTI_DECL(OvMSObject);

public :

	OvMSObject();
	virtual ~OvMSObject();

	//! Update
	void			Update(float _fElapse);
	virtual void	UpdateSubordinate(float _fElapse);

	//! Set Local Transform
	void			SetTranslate(OvPoint3& _rPosition);
	void			SetRotation(OvQuaternion& _rRotation);
	void			SetScale(float _fScale);

	//! Get Local Transform
	OvPoint3&		GetTranslate();
	OvQuaternion&	GetRotation();
	float			GetScale();

	//! Get World Transform
	const OvPoint3&		GetWorldTranslate();
	const OvQuaternion&	GetWorldRotation();
	float				GetWorldScale();
	const OvTransform&	GetWorldTransform();

	//! Which Kind
	bool			IsNode();
	bool			IsLeaf();

	//! Get Parent
	OvNode*			GetParent();

protected:

	//! Set Parent (Do not use in application)
	void			SetParent(OvNode* _pParentNode);

	//! Set Object Controller (Do not use in application)
	void			PrependObjectController(OvObjectController* _pController);

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};