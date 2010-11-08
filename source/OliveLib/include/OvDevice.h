#pragma once
#include "OvRenderingCommon.h"

class OvDevice
{
private:
	OvDevice();
public:

	OvDevice( OvDevice& copy );
	OvDevice(LPDIRECT3DDEVICE9 device, CRITICAL_SECTION& occupy );
	~OvDevice();

	LPDIRECT3DDEVICE9 operator ->()const;;
	operator	LPDIRECT3DDEVICE9();
	operator	bool();

private:
	LPDIRECT3DDEVICE9 m_device;
	CRITICAL_SECTION& m_device_occupy;
};