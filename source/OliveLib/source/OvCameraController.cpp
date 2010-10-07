#include "OvCameraController.h"
#include "OvMessageManager.h"
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
bool OvCameraController::MessageListen( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	OvCameraSPtr target_camera = GetTarget();
	switch( message )
	{
	case WM_MOUSEMOVE : 
		{
			OvQuaternion yRot,xRot;
			yRot.MakeQuaternion(OvPoint3::AXIS_Y, m_accumulatedRotate.x / (D3DX_PI * 20.0f) );
			xRot.MakeQuaternion(OvPoint3::AXIS_X, m_accumulatedRotate.y / (D3DX_PI * 20.0f));

			target_camera->SetRotation( yRot * xRot );

			m_accumulatedRotate = ( m_accumulatedRotate + OvMessageManager::GetInstance()->GetMouseInterval() );
		}
		break;
	case WM_KEYDOWN : 
		{
			OvPoint3 direction;
			OvPoint3 velocity;
			float moveSpeed = 1.0f;
			switch ( wparam )
			{
			case VK_UP :
				direction = target_camera->GetLocalLookDirection();
				break;
			case VK_DOWN :
				direction = -target_camera->GetLocalLookDirection();
				break;
			case VK_LEFT :
				direction = -target_camera->GetLocalRightDirection();
				break;
			case VK_RIGHT :
				direction = target_camera->GetLocalRightDirection();
				break;
			}
			velocity = (target_camera->GetTranslate() + direction * moveSpeed);
			target_camera->SetTranslate( velocity );
		}
	}
	return false;
}