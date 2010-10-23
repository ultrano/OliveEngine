#include "OvCameraController.h"
#include "OvInputManager.h"
#include "OvQuaternion.h"
#include "OvCamera.h"
#include "OvRegisterableProperties.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvCameraController);

OvCameraController::OvCameraController()
{

}

OvCameraController::~OvCameraController()
{

}
void OvCameraController::Update( float _fElapse )
{
	
	OvCameraSPtr target_camera = GetTarget();
	
	OvQuaternion yRot,xRot;
	yRot.MakeQuaternion(OvPoint3::AXIS_Y, m_accumulatedRotate.x / (D3DX_PI * 20.0f) );
	xRot.MakeQuaternion(OvPoint3::AXIS_X, m_accumulatedRotate.y / (D3DX_PI * 20.0f));

	target_camera->SetRotation( yRot * xRot );

	OvPoint2 mouseMovement = OvInputManager::GetCurrentMousePos() - m_liatMousePos;
	m_liatMousePos = OvInputManager::GetCurrentMousePos();
	m_accumulatedRotate = ( m_accumulatedRotate + mouseMovement );
	
	OvPoint3 direction;
	OvPoint3 velocity;
	float moveSpeed = 1.0f;
	if ( OvInputManager::IsPushed( VK_UP ) )
	{
		direction += target_camera->GetLocalLookDirection();
	}
	if ( OvInputManager::IsPushed( VK_DOWN ) )
	{
		direction += -target_camera->GetLocalLookDirection();
	}
	if ( OvInputManager::IsPushed( VK_LEFT ) )
	{
		direction += -target_camera->GetLocalRightDirection();
	}
	if ( OvInputManager::IsPushed( VK_RIGHT ) )
	{
		direction += target_camera->GetLocalRightDirection();
	}
	velocity = (target_camera->GetTranslate() + direction * moveSpeed);
	target_camera->SetTranslate( velocity );
	
}