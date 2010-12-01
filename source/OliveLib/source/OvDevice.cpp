#include "OvDevice.h"

OvDevice::OvDevice( OvDevice& copy )
: m_device( copy.m_device )
, m_device_occupy( copy.m_device_occupy )
{
	copy.m_device = NULL;
	::EnterCriticalSection( &m_device_occupy );
}

OvDevice::OvDevice( LPDIRECT3DDEVICE9 device, CRITICAL_SECTION& occupy ) 
: m_device( device )
, m_device_occupy( occupy )
{
	::EnterCriticalSection( &m_device_occupy );
}

OvDevice::~OvDevice()
{
	if ( m_device )
	{
		m_device = NULL;
		::LeaveCriticalSection( &m_device_occupy );
	}
}

OvDevice::operator LPDIRECT3DDEVICE9()
{
	return m_device;
}
OvDevice::operator OvBool()
{
	return (NULL != m_device);
}

LPDIRECT3DDEVICE9 OvDevice::operator->() const
{
	return m_device;
}