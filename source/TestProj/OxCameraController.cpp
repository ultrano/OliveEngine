
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
	if ( m_scene && m_cameraActor )
	{
		m_scene->releaseActor( *m_cameraActor );
		m_cameraActor = NULL;
	}
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

	float mouseSensitivity = 0.1f;
	OvPoint3 delta = OvInputManager::GetMouseMoveDelta() * mouseSensitivity;
	OvPoint2 mouseMovement( delta.x, delta.y );
	m_accumulatedRotate = ( m_accumulatedRotate + mouseMovement );

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	target_camera->SetRotation( yRot * xRot );
	target_camera->SetTranslate( OvConvert::xyz<OvPoint3>( m_cameraActor->getGlobalPosition() ) + OvPoint3::AXIS_Y*3 );
	target_camera->SetFOV( target_camera->GetFOV() - delta.z*0.001f );

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	OvPoint3 direction;
	OvPoint3 velocity;
	float moveSpeed = 50.0f;
	if ( OvInputManager::IsStateOfKey( DIK_LSHIFT, PRESSING ))
	{
		moveSpeed = moveSpeed * 5;
	}
	if ( OvInputManager::IsStateOfKey( DIK_W, PRESSING ) )
	{
		direction += target_camera->GetLocalLookDirection();
	}
	if ( OvInputManager::IsStateOfKey( DIK_S, PRESSING ) )
	{
		direction += -target_camera->GetLocalLookDirection();
	}
	if ( OvInputManager::IsStateOfKey( DIK_A, PRESSING ) )
	{
		direction += -target_camera->GetLocalRightDirection();
	}
	if ( OvInputManager::IsStateOfKey( DIK_D, PRESSING ) )
	{
		direction += target_camera->GetLocalRightDirection();
	}
	direction.y = 0;
	velocity = ( direction.Normalize() * moveSpeed );
	m_cameraActor->addForce( OvConvert::xyz<NxVec3>( velocity ) );

	if ( OvInputManager::IsStateOfKey( DIK_SPACE, PRESSED ) )
	{
		m_cameraActor->addForce( OvConvert::xyz<NxVec3>( OvPoint3::AXIS_Y * 2500 ) );
	}

}