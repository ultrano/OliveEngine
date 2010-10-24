
#include "NxPhysics.h"
#include "OxTestPhysx.h"

OxTestPhysx::OxTestPhysx()
{
	//////////////////////////////////////////////////////////////////////////
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	m_physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
	m_physicsSDK->setParameter(NX_SKIN_WIDTH, 0.05f);

	// Create a scene
	NxSceneDesc sceneDesc;
	sceneDesc.gravity				= NxVec3(0.0f, -9.81f, 0.0f);
	m_scene = m_physicsSDK->createScene(sceneDesc);

	// Set default material
	NxMaterial* defaultMaterial = m_scene->getMaterialFromIndex(0);
	defaultMaterial->setRestitution(0.0f);
	defaultMaterial->setStaticFriction(0.5f);
	defaultMaterial->setDynamicFriction(0.5f);

	NxMaterialDesc hightention;
	hightention.restitution = 1.0f;
	hightention.dynamicFriction = 0.0f;
	hightention.staticFriction = 0.0f;
	m_scene->createMaterial( hightention );

	// Create ground plane
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	m_scene->createActor(actorDesc);

}

OxTestPhysx::~OxTestPhysx()
{
	m_physicsSDK->releaseScene( *m_scene );
	NxReleasePhysicsSDK( m_physicsSDK );
	m_physicsSDK = NULL;
}

NxScene* OxTestPhysx::GetScene()
{
	return m_scene;
}