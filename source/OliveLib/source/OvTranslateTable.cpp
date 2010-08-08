#include "OvTranslateTable.h"
#include <map>

typedef map<float,OvPoint3>	tdInterpolateTable;
struct OvTranslateTable::OvPimple : OvMemObject
{
	unsigned			m_uiKeyCount;
	tdInterpolateTable	m_mapInterpolationTable;
};

OvTranslateTable::OvTranslateTable()
:m_pPimple(OvNew OvTranslateTable::OvPimple)
{

}

unsigned	OvTranslateTable::KeyCount()
{
	return m_pPimple->m_uiKeyCount;
}

void		OvTranslateTable::SetKeyCount(unsigned uiCount)
{
	m_pPimple->m_uiKeyCount = uiCount;
}

void		OvTranslateTable::IncreaseKeyCount()
{
	++(m_pPimple->m_uiKeyCount);
}
void		OvTranslateTable::DecreaseKeyCount()
{
	--(m_pPimple->m_uiKeyCount);
}

void		OvTranslateTable::AddPoint3(float fTime,const OvPoint3& crPt)
{
	m_pPimple->m_mapInterpolationTable[fTime] = crPt;
	IncreaseKeyCount();
}

OvPoint3	OvTranslateTable::Interpolate(float fTime)
{
	tdInterpolateTable::iterator	kDestIter		= m_pPimple->m_mapInterpolationTable.begin();
	tdInterpolateTable::iterator	kScrIter		= m_pPimple->m_mapInterpolationTable.end();

	for (;kDestIter!=m_pPimple->m_mapInterpolationTable.end();++kDestIter)
	{
		if (fTime < kDestIter->first)
		{
			if (kScrIter == m_pPimple->m_mapInterpolationTable.end())
			{
				return kDestIter->second;
			}
			return OvLinearInterpolate<OvPoint3>(
				((fTime - kScrIter->first)/(kDestIter->first - kScrIter->first))
				,kScrIter->second
				,kDestIter->second);
		}
		kScrIter = kDestIter;
	}
	return kScrIter->second;
}