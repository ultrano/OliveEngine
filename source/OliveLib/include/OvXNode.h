#pragma once
#include "OvXObject.h"
#include "OvObjectCollector.h"

OvREF_POINTER(OvXNode);
class OvStorage;
class OvXNode : public OvXObject
{
	OvRTTI_DECL(OvXNode);
	OvFACTORY_OBJECT_DECL(OvXNode);

public:

	OvXNode();
	virtual ~OvXNode();

	void AttachChild(OvXObjectSPtr obj);

	// ����� �������ٸ�, ������ ��ü�� ���� �����͸� �����Ѵ�.
	OvXObjectSPtr	DettachChild(OvXObjectSPtr obj);

	size_t			GetChildCount();

	OvSize			GetChildrenSet( OvObjectSet children );

	virtual void Serialize( OvObjectOutputStream & output ) override;
	virtual void Deserialize( OvObjectInputStream & input ) override;


private:

	virtual void	_update_system( OvFloat _fElapse ) override;

private:

	OvObjectSet	m_children;

};

class OvScene;
class OvSceneNode : public OvXNode
{
	OvRTTI_DECL(OvSceneNode);
	OvFACTORY_OBJECT_DECL(OvSceneNode);
	
	//<! pseudo code
	void	UpdateScene( OvFloat elapse );
	void	SetScene( OvScene* scene );
	OvScene* GetScene();
private:
	OvScene*		m_scene;

};