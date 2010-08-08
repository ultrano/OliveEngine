#pragma once
#include "OvPoint3.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"

OvREF_POINTER(OvTranslateTable);
class OvTranslateTable : public OvRefBase
{
public:

	OvTranslateTable();

	OvPoint3	Interpolate(float fTime);

	void		AddPoint3(float fTime,const OvPoint3& crPt);

	unsigned	KeyCount();

protected:

	void		SetKeyCount(unsigned uiCount);
	void		IncreaseKeyCount();
	void		DecreaseKeyCount();

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};