#include "OvCameraController.h"
#include "OvInputManager.h"
#include "OvQuaternion.h"
#include "OvCamera.h"
#include "OvRegisterableProperties.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvCameraController);
OvFACTORY_OBJECT_IMPL(OvCameraController);
OvCameraController::OvCameraController()
{

}

OvCameraController::~OvCameraController()
{

}
void OvCameraController::Update( float _fElapse )
{
	OvInputManager* input = OvInputManager::GetInstance();
	OvCameraSPtr target_camera = GetTarget();
	
	OvQuaternion yRot,xRot;
	yRot.MakeQuaternion(OvPoint3::AXIS_Y, m_accumulatedRotate.x / (D3DX_PI * 20.0f) );
	xRot.MakeQuaternion(OvPoint3::AXIS_X, m_accumulatedRotate.y / (D3DX_PI * 20.0f));

	target_camera->SetRotation( yRot * xRot );

	OvPoint3 delta = input->GetMouseMoveDelta();
	OvPoint2 mouseMovement( delta.x, delta.y );
	m_accumulatedRotate = ( m_accumulatedRotate + mouseMovement );
	
	OvPoint3 direction;
	OvPoint3 velocity;
	float moveSpeed = 1.0f;
	if ( input->IsStateOfKey( VK_UP, PRESSING ) )
	{
		direction += target_camera->GetLocalLookDirection();
	}
	if ( input->IsStateOfKey( VK_DOWN, PRESSING ) )
	{
		direction += -target_camera->GetLocalLookDirection();
	}
	if ( input->IsStateOfKey( VK_LEFT, PRESSING ) )
	{
		direction += -target_camera->GetLocalRightDirection();
	}
	if ( input->IsStateOfKey( VK_RIGHT, PRESSING ) )
	{
		direction += target_camera->GetLocalRightDirection();
	}
	velocity = (target_camera->GetTranslate() + direction * moveSpeed);
	target_camera->SetTranslate( velocity );
	
}