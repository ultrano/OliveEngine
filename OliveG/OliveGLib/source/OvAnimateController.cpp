#include "OvAnimateController.h"
#include "OvPoint3.h"
#include "OvXObject.h"
#include "OvValueKeyCollector.h"
#include <map>
struct OvAnimateController::OvPimple : OvMemObject
{
	//!
	map<float,OvPoint3> mPositionTable;
	float				mMaxTick;
	float				mMinTick;
	float				mAccumulateTick;
	//!

};

OvAnimateController::OvAnimateController()
:m_pPimple(OvNew OvAnimateController::OvPimple)
{
	m_pPimple->mMaxTick = 0;
	m_pPimple->mMinTick = 0;
	m_pPimple->mAccumulateTick = 0;
}
OvAnimateController::~OvAnimateController()
{

}

void			OvAnimateController::SetPositionControllKey(float fTick,const OvPoint3& crPos)
{
	m_pPimple->mPositionTable[fTick] = crPos;
	m_pPimple->mMaxTick = max(m_pPimple->mMaxTick,fTick);
	m_pPimple->mMinTick = min(m_pPimple->mMinTick,fTick);
}

void			OvAnimateController::FindPosSample(float fTick,float& fTickSrc,float& fTickDest,OvPoint3& crPosSrc,OvPoint3& crPosDest)
{
	if (GetMaxTick() < fTick || GetMinTick() > fTick)
		return ;

	map<float,OvPoint3>::iterator	kIter = m_pPimple->mPositionTable.begin();
	for (; kIter != m_pPimple->mPositionTable.end() ; ++kIter)
	{
		if (fTick < kIter->first)
		{
			fTickDest = kIter->first;
			crPosDest = kIter->second;
			--kIter;
			fTickSrc = kIter->first;
			crPosSrc = kIter->second;
			break;
		}
	}

}
float			OvAnimateController::GetMaxTick()
{
	return m_pPimple->mMaxTick;
}
float			OvAnimateController::GetMinTick()
{
	return m_pPimple->mMinTick;
}

void	OvAnimateController::Update(float _fElapse)
{
	if (GetEquippedTarget())
	{
		m_pPimple->mAccumulateTick += _fElapse;
		float		kfTickScr,kfTickDest;
		OvPoint3	kPosScr,kPosDest;
		FindPosSample(m_pPimple->mAccumulateTick,kfTickScr,kfTickDest,kPosScr,kPosDest);
		float		kfProgressRate = (m_pPimple->mAccumulateTick - kfTickScr) / (kfTickDest - kfTickScr);
		OvPoint3	kProgressVector	= (kPosDest - kPosScr);
		kProgressVector = kPosScr + (kProgressVector * kfProgressRate);

		GetEquippedTarget()->SetTranslate(kProgressVector);
	}
}