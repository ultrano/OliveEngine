
#include "NxPhysics.h"
#include "OxCameraController.h"
#include "OvInputManager.h"
#include "OvPoint3.h"
#include "OvPoint2.h"
#include "OvCamera.h"
#include <d3dx9.h>

OxCameraController::OxCameraController( NxScene * scene )
: m_scene( scene )
{
}

OxCameraController::~OxCameraController()
{

}

void OxCameraController::SetUp()
{
	if ( NULL == m_scene ) return;
	// Create body
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;

	OvPoint3 scale = GetTarget()->GetScale();
	NxSphereShapeDesc desc;
	desc.radius = scale.x;

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&desc);
	actorDesc.body			= &bodyDesc;
	actorDesc.density		= 10.0f;
	m_cameraActor = m_scene->createActor( actorDesc );
	m_cameraActor->setGlobalPosition( OvConvert::xyz<NxVec3>( GetTarget()->GetTranslate() ) );
}

void OxCameraController::ShutDown()
{
	if ( m_scene && m_cameraActor )
	{
		m_scene->releaseActor( *m_cameraActor );
		m_cameraActor = NULL;
	}
}

void OxCameraController::Update( float _fElapse )
{

	OvCameraSPtr target_camera = GetTarget();

	OvQuaternion yRot,xRot;
	yRot.MakeQuaternion(OvPoint3::AXIS_Y, m_accumulatedRotate.x / (D3DX_PI * 20.0f) );
	xRot.MakeQuaternion(OvPoint3::AXIS_X, m_accumulatedRotate.y / (D3DX_PI * 20.0f));

	OvPoint2 mouseMovement = OvInputManager::GetCurrentMousePos() - m_lastMousePos;
	m_lastMousePos = OvInputManager::GetCurrentMousePos();
	m_accumulatedRotate = ( m_accumulatedRotate + mouseMovement );

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	target_camera->SetRotation( yRot * xRot );
	target_camera->SetTranslate( OvConvert::xyz<OvPoint3>( m_cameraActor->getGlobalPosition() ) + OvPoint3::AXIS_Y*3 );

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	OvPoint3 direction;
	OvPoint3 velocity;
	float moveSpeed = 50.0f;
	if ( OvInputManager::IsPushed( VK_SHIFT ))
	{
		moveSpeed = moveSpeed * 2;
	}
	if ( OvInputManager::IsPushed( 'W' ) )
	{
		direction += target_camera->GetLocalLookDirection();
	}
	if ( OvInputManager::IsPushed( 'S' ) )
	{
		direction += -target_camera->GetLocalLookDirection();
	}
	if ( OvInputManager::IsPushed( 'A' ) )
	{
		direction += -target_camera->GetLocalRightDirection();
	}
	if ( OvInputManager::IsPushed( 'D' ) )
	{
		direction += target_camera->GetLocalRightDirection();
	}
	direction.y = 0;
	velocity = ( direction.Normalize() * moveSpeed );
	m_cameraActor->addForce( OvConvert::xyz<NxVec3>( velocity ) );

	if ( OvInputManager::IsPushed( VK_SPACE ) )
	{
		m_cameraActor->addForce( OvConvert::xyz<NxVec3>( OvPoint3::AXIS_Y * 250 ) );
	}

}