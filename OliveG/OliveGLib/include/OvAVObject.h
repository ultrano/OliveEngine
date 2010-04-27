// 2008 12 11
// maker : Han,sang woon
// OvAVObject
#pragma once
#include "OvObject.h"
#include "OvAutoPtr.h"

// AVObject -> ActiveObject 
// 활동적인 오브젝트 (공간상의 객체역할)

// Class 선선언부
class OvPoint3;
class OvQuaternion;
//

OvREF_POINTER(OvAVObject);
class OvAVObject : public OvObject
{
	friend class OvNode;
	friend class OvObjectController;
	OvRTTI_DECL(OvAVObject);

public :

	OvAVObject();
	virtual ~OvAVObject();

	void			Update(float _fElapse);
	virtual void	UpdateSubordinate(float _fElapse);

	void			SetTranslate(OvPoint3& _rPosition);
	void			SetRotation(OvQuaternion& _rRotation);
	void			SetScale(float _fScale);

	OvPoint3&		GetTranslate();
	OvQuaternion&	GetRotation();
	float			GetScale();

	bool			IsNode();
	bool			IsLeaf();

	OvNode*			GetParent();

protected:

	void			SetParent(OvNode* _pParentNode);
	void			PrependObjectController(OvObjectController* _pController);

private:

	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};