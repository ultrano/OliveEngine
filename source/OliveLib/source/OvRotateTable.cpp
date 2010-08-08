#include "OvRotateTable.h"
#include "OvPoint3.h"
#include "OvInterpolate.h"
#include <map>


struct OvRotateTable::OvPimple : OvMemObject
{
	unsigned			m_uiKeyCount;
};

OvRotateTable::OvRotateTable()
:m_pPimple(OvNew OvRotateTable::OvPimple)
{

}

unsigned	OvRotateTable::KeyCount()
{
	return m_pPimple->m_uiKeyCount;
}

void		OvRotateTable::SetKeyCount(unsigned uiCount)
{
	m_pPimple->m_uiKeyCount = uiCount;
}

void		OvRotateTable::IncreaseKeyCount()
{
	++(m_pPimple->m_uiKeyCount);
}
void		OvRotateTable::DecreaseKeyCount()
{
	--(m_pPimple->m_uiKeyCount);
}

/////////////////////////////////////////////////////////////////////////////////

typedef map<float,OvPoint3>	tdEulerValueTable;
struct OvEulerTable::OvPimple : OvMemObject
{
	tdEulerValueTable	m_tdKeyTable;
};

OvEulerTable::OvEulerTable()
:m_pPimple(OvNew OvEulerTable::OvPimple)
{

}

void		OvEulerTable::AddXYZEuler(float fTime,float fXRotation,float fYRotation,float fZRotation)
{
	m_pPimple->m_tdKeyTable[fTime] = OvPoint3(fXRotation,fYRotation,fZRotation);
	IncreaseKeyCount();
}

OvQuaternion	OvEulerTable::Interpolate(float fTime)
{
	tdEulerValueTable::iterator	kDestIter		= m_pPimple->m_tdKeyTable.begin();
	tdEulerValueTable::iterator	kScrIter		= m_pPimple->m_tdKeyTable.end();

	for (;kDestIter!=m_pPimple->m_tdKeyTable.end();++kDestIter)
	{
		if (fTime < kDestIter->first)
		{
			if (kScrIter == m_pPimple->m_tdKeyTable.end())
			{
				return OvEulerToQuaternion(kDestIter->second.x,kDestIter->second.y,kDestIter->second.z);
			}
			OvPoint3	kEulerAngle = OvLinearInterpolate<OvPoint3>(
				((fTime - kScrIter->first)/(kDestIter->first - kScrIter->first))
				,kScrIter->second
				,kDestIter->second);

			return OvEulerToQuaternion(kEulerAngle.x,kEulerAngle.y,kEulerAngle.z);
		}
		kScrIter = kDestIter;
	}
	
	return OvEulerToQuaternion(kScrIter->second.x,kScrIter->second.y,kScrIter->second.z);
}