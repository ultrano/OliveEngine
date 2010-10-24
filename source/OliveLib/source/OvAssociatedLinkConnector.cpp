#include "OvAssociatedLinkConnector.h"
#include "OvObjectCollector.h"
#include "OvObject.h"
#include "OvObjectID.h"

OvRTTI_IMPL_ROOT(OvAssociatedLinkConnector);
OvAssociatedLinkConnector::OvAssociatedLinkConnector()
{

}
OvAssociatedLinkConnector::~OvAssociatedLinkConnector()
{

}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPointerLinkConnector);

OvPointerLinkConnector::OvPointerLinkConnector()
:m_destination( NULL )
,m_formerID( OvObjectID::INVALID )
{

}
OvPointerLinkConnector::~OvPointerLinkConnector()
{

}

void	OvPointerLinkConnector::SetDestination(OvObject** destination)
{
	m_destination = destination;
}
OvObject** OvPointerLinkConnector::GetDestination()
{
	return m_destination;
}

bool OvPointerLinkConnector::BuildLink( restore_object_table &restoreTable)
{
	restore_object_table::iterator tableIter = restoreTable.find( GetFormerID() );
	
	if ( tableIter != restoreTable.end() )
	{
		OvObject** destAddress = GetDestination();
		OvObject* restoreObject = tableIter->second;
		if ( destAddress && restoreObject )
		{
			*destAddress = restoreObject;
			return true;
		}
	}
	return false;
}

void	OvPointerLinkConnector::SetFormerID( const OvObjectID& objID )
{
	m_formerID = objID;
}
const OvObjectID& OvPointerLinkConnector::GetFormerID()
{
	return m_formerID;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvSmartPtrLinkConnector);

OvSmartPtrLinkConnector::OvSmartPtrLinkConnector()
:m_destination( NULL )
,m_formerID( OvObjectID::INVALID )
{

}
OvSmartPtrLinkConnector::~OvSmartPtrLinkConnector()
{

}

void	OvSmartPtrLinkConnector::SetSmartDestination( OvObjectSPtr* destination )
{
	m_destination = destination;
}
OvObjectSPtr* OvSmartPtrLinkConnector::GetSmartDestination()
{
	return m_destination;
}

bool OvSmartPtrLinkConnector::BuildLink( restore_object_table& restoreTable )
{
	restore_object_table::iterator tableIter = restoreTable.find( GetFormerID() );

	if ( tableIter != restoreTable.end() )
	{
		OvObjectSPtr* destAddress = GetSmartDestination();
		OvObject* restoreObject = tableIter->second;
		if ( destAddress && restoreObject )
		{
			*destAddress = restoreObject;
			return true;
		}
	}
	return false;
}
void	OvSmartPtrLinkConnector::SetFormerID( const OvObjectID& objID )
{
	m_formerID = objID;
}
const OvObjectID& OvSmartPtrLinkConnector::GetFormerID()
{
	return m_formerID;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvCollectedObjectsLinkConnector);

OvCollectedObjectsLinkConnector::OvCollectedObjectsLinkConnector()
{
	m_destination = NULL;
	m_relatedObjects.clear();
}
OvCollectedObjectsLinkConnector::~OvCollectedObjectsLinkConnector()
{
	m_destination = NULL;
	m_relatedObjects.clear();
}

void	OvCollectedObjectsLinkConnector::SetDestinateCollector( OvObjectCollector* destination )
{
	m_destination = destination;
}
OvObjectCollector* OvCollectedObjectsLinkConnector::GetDestinateCollector()
{
	return m_destination;
}


void	OvCollectedObjectsLinkConnector::AddRelatedObjectID( const OvObjectID& objectID )
{
	if ( OvObjectID::INVALID != objectID )
	{
		m_relatedObjects.push_back( objectID );
	}
}

bool OvCollectedObjectsLinkConnector::BuildLink( restore_object_table& restoreTable )
{
	OvObjectCollector* destAddress = GetDestinateCollector();
	if (destAddress)
	{
		for each (const OvObjectID& formerID in m_relatedObjects )
		{
			restore_object_table::iterator tableIter;
			tableIter = restoreTable.find( formerID );
			if ( restoreTable.end() != tableIter )
			{
				if ( OvObject* restoreObject = tableIter->second )
				{
					destAddress->AddObject( restoreObject );
				}
			}
		}
		return true;
	}
	return false;
}
