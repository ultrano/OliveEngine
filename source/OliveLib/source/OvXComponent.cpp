#include "OvXComponent.h"
#include "OvXObject.h"
OvRTTI_IMPL(OvXComponent);

OvXComponent::OvXComponent()
:m_equippedObject( NULL )
{
}
OvXComponent::~OvXComponent()
{
	if ( m_equippedObject )
	{
		ShutDown();
	}
}

void		OvXComponent::SetTarget( OvXObjectSPtr _pEquippedObject )
{
	if ( m_equippedObject )
	{
		m_equippedObject->_remove_component( this );
	}
	m_equippedObject = _pEquippedObject.GetRear();
	if ( m_equippedObject )
	{
		m_equippedObject->_equip_component( this );
	}
}
OvXObjectSPtr	OvXComponent::GetTarget()
{
	return m_equippedObject;
}


void OvXComponent::SetUp()
{

}

void OvXComponent::ShutDown()
{

}

void OvXComponent::SetName( const OvString& name )
{
	m_name = name;
}

const OvString& OvXComponent::GetName()
{
	return m_name;
}