#include "OvObjectController.h"
#include "OvXObject.h"

struct OvObjectController::OvPimple : OvMemObject
{
	OvObjectControllerSPtr		mNextLinkedController;
	OvXObject*			mTargetObject;
};


OvObjectController::OvObjectController():m_pPimple(OvNew OvPimple)
{
	m_pPimple->mTargetObject = NULL;
}
OvObjectController::~OvObjectController()
{

}

void	OvObjectController::SetNextController(OvXObjectSPtr _pNextController)
{
	if(!_pNextController)
		return ;

	m_pPimple->mNextLinkedController = _pNextController;
}

OvXObjectSPtr	OvObjectController::GetNextController()
{
	return m_pPimple->mNextLinkedController;
}

void		OvObjectController::SetTargetObject(OvXObjectSPtr _pTargetObject)
{
	if(!_pTargetObject)
		return;

	m_pPimple->mTargetObject = _pTargetObject.GetRear();
	_pTargetObject->PrependObjectController(this);
}
OvXObjectSPtr	OvObjectController::GetTargetObject()
{
	return m_pPimple->mTargetObject;
}

