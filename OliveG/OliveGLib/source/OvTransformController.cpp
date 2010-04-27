#include "OvTransformController.h"
#include "OvRotateTable.h"
#include "OvTranslateTable.h"
#include "OvXObject.h"
#include <map>

struct OvTransformController::OvPimple : OvMemObject
{
	//!
	OvRotateTableSPtr		m_pRotationTable;
	OvTranslateTableSPtr	m_pPositionTable;
	//!

	//!
	OvQuaternion m_cResultRotation;
	OvPoint3	m_cResultPosition;

	float		m_fAccumlateTickCount;
	float		m_fStartTick;
	float		m_fEndTick;
};


OvTransformController::OvTransformController()
:m_pPimple(OvNew OvTransformController::OvPimple)
{
	m_pPimple->m_fAccumlateTickCount	= 0;
	m_pPimple->m_fStartTick				= 0;
	m_pPimple->m_fEndTick				= 0;
}
OvTransformController::~OvTransformController()
{

}


void			OvTransformController::AddPosKey(float fTick,const OvPoint3& crPos)
{
	m_pPimple->m_pPositionTable->AddPoint3(fTick,crPos);
}

void			OvTransformController::SetStartTick(float fTick)
{
	m_pPimple->m_fStartTick	=	fTick;
}
void			OvTransformController::SetEndTick(float fTick)
{
	m_pPimple->m_fEndTick	=	fTick;
}
float			OvTransformController::GetStartTick()
{
	return m_pPimple->m_fStartTick;
}
float			OvTransformController::GetEndTick()
{
	return m_pPimple->m_fEndTick;
}

void			OvTransformController::SetRotateTable(OvRotateTableSPtr pRotateTable)
{
	m_pPimple->m_pRotationTable = pRotateTable;
}

void			OvTransformController::SetTranslateTable(OvTranslateTableSPtr pTranslateTable)
{
	m_pPimple->m_pPositionTable = pTranslateTable;
}

float			OvTransformController::GetTickCount()
{
	return m_pPimple->m_fAccumlateTickCount;
}

void			OvTransformController::Update(float _fElapse)
{
	UpdateRot();
	UpdatePos();
	CommitTransform();
	m_pPimple->m_fAccumlateTickCount += _fElapse;

	//! 테스트 코드.
	if (m_pPimple->m_fAccumlateTickCount >20000)
	{
		m_pPimple->m_fAccumlateTickCount = 0;
	}
}

void			OvTransformController::UpdateRot()
{
	OvRotateTableSPtr		kpRotationTable = m_pPimple->m_pRotationTable;
	if (kpRotationTable && kpRotationTable->KeyCount())
	{
		m_pPimple->m_cResultRotation = m_pPimple->m_pRotationTable->Interpolate(GetTickCount());
	}
}
void			OvTransformController::UpdatePos()
{
	OvTranslateTableSPtr	kpPositionTable = m_pPimple->m_pPositionTable;
	if (kpPositionTable && kpPositionTable->KeyCount())
	{
		m_pPimple->m_cResultPosition = m_pPimple->m_pPositionTable->Interpolate(GetTickCount());
	}
}
void			OvTransformController::CommitTransform()
{
	if (GetTargetObject())
	{
		GetTargetObject()->SetRotation(m_pPimple->m_cResultRotation);
		GetTargetObject()->SetTranslate(m_pPimple->m_cResultPosition);
	}
}