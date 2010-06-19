#include "OvRelationLinkBuilder.h"
#include "OvObjectCollector.h"

OvRTTI_IMPL_ROOT(OvRelationLinkBuilder);
OvRelationLinkBuilder::OvRelationLinkBuilder()
:m_nextBuilder( NULL )
{

}
OvRelationLinkBuilder::~OvRelationLinkBuilder()
{

}

void	OvRelationLinkBuilder::SetNextBuilder( OvRelationLinkBuilder* nextBuilder )
{
	m_nextBuilder = nextBuilder;
}
OvRelationLinkBuilder* OvRelationLinkBuilder::GetNextBuilder()
{
	return m_nextBuilder;
}


//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPointLinkBuilder);

OvPointLinkBuilder::OvPointLinkBuilder()
:m_destination( NULL )
,m_formerID( OvObjectID::INVALID )
{

}
OvPointLinkBuilder::~OvPointLinkBuilder()
{

}

void	OvPointLinkBuilder::SetDestination(OvObject** destination)
{
	m_destination = destination;
}
OvObject** OvPointLinkBuilder::GetDestination()
{
	return m_destination;
}

bool OvPointLinkBuilder::BuildLink(OvStorage::restore_object_table &restoreTable)
{
	OvStorage::restore_object_table::iterator tableIter = restoreTable.find( GetFormerID() );
	
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

void	OvPointLinkBuilder::SetFormerID( const OvObjectID& objID )
{
	m_formerID = objID;
}
const OvObjectID& OvPointLinkBuilder::GetFormerID()
{
	return m_formerID;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvSmartLinkBuilder);

OvSmartLinkBuilder::OvSmartLinkBuilder()
:m_destination( NULL )
,m_formerID( OvObjectID::INVALID )
{

}
OvSmartLinkBuilder::~OvSmartLinkBuilder()
{

}

void	OvSmartLinkBuilder::SetSmartDestination( OvObjectSPtr* destination )
{
	m_destination = destination;
}
OvObjectSPtr* OvSmartLinkBuilder::GetSmartDestination()
{
	return m_destination;
}

bool OvSmartLinkBuilder::BuildLink( OvStorage::restore_object_table& restoreTable )
{
	OvStorage::restore_object_table::iterator tableIter = restoreTable.find( GetFormerID() );

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
void	OvSmartLinkBuilder::SetFormerID( const OvObjectID& objID )
{
	m_formerID = objID;
}
const OvObjectID& OvSmartLinkBuilder::GetFormerID()
{
	return m_formerID;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvObjectCollectorLinkBuilder);

OvObjectCollectorLinkBuilder::OvObjectCollectorLinkBuilder()
:m_destination( NULL )
{

}
OvObjectCollectorLinkBuilder::~OvObjectCollectorLinkBuilder()
{
	m_relatedObjects.clear();
}

void	OvObjectCollectorLinkBuilder::SetDestinateCollector( OvObjectCollector* destination )
{
	m_destination = destination;
}
OvObjectCollector* OvObjectCollectorLinkBuilder::GetDestinateCollector()
{
	return m_destination;
}


void	OvObjectCollectorLinkBuilder::AddRelatedObjectID( const OvObjectID& objectID )
{
	m_relatedObjects.push_back( objectID );
}

bool OvObjectCollectorLinkBuilder::BuildLink( OvStorage::restore_object_table& restoreTable )
{
	OvStorage::restore_object_table::iterator tableIter;

	OvObjectCollector* destAddress = GetDestinateCollector();
	if (destAddress)
	{
		for each (const OvObjectID& formerID in m_relatedObjects )
		{
			tableIter = restoreTable.find( formerID );
			if ( OvObject* restoreObject = tableIter->second )
			{
				destAddress->AddObject( restoreObject );
			}
		}
		return true;
	}
	return false;
}