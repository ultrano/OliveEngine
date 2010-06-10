#include "OvXController.h"
#include "OvXObject.h"
OvRTTI_IMPL(OvXController);
struct OvXController::OvPimple : OvMemObject
{
	OvXControllerSPtr		mNextLinkedController;
	OvXObject*			mTargetObject;
};


OvXController::OvXController():m_pPimple(OvNew OvPimple)
{
	m_pPimple->mTargetObject = NULL;
}
OvXController::~OvXController()
{

}

void	OvXController::SetNextController(OvXObjectSPtr _pNextController)
{
	if(!_pNextController)
		return ;

	m_pPimple->mNextLinkedController = _pNextController;
}

OvXObjectSPtr	OvXController::GetNextController()
{
	return m_pPimple->mNextLinkedController;
}

void		OvXController::SetTargetObject(OvXObjectSPtr _pTargetObject)
{
	if(!_pTargetObject)
		return;

	m_pPimple->mTargetObject = _pTargetObject.GetRear();
	_pTargetObject->PrependObjectController(this);
}
OvXObjectSPtr	OvXController::GetTargetObject()
{
	return m_pPimple->mTargetObject;
}

