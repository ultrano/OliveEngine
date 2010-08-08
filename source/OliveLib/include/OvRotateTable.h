#pragma once
#include "OvQuaternion.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"

OvREF_POINTER(OvRotateTable);
OvREF_POINTER(OvEulerTable);

class OvRotateTable : public OvRefBase
{
public:

	OvRotateTable();

	virtual OvQuaternion	Interpolate(float fTime) = 0;

	unsigned	KeyCount();

protected:

	void		SetKeyCount(unsigned uiCount);
	void		IncreaseKeyCount();
	void		DecreaseKeyCount();

private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};

class OvEulerTable : public OvRotateTable
{
public:

	OvEulerTable();

	void		AddXYZEuler(float fTime,float fXRotation,float fYRotation,float fZRotation);

	virtual OvQuaternion	Interpolate(float fTime);

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};