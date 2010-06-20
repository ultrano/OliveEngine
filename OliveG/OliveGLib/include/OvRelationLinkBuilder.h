#pragma once
#include "OvMemObject.h"
#include "OvSmartPointer.h"
#include "OvUtility_RTTI.h"
#include "OvStreamCommon.h"
#include "OvObjectID.h"
#include <vector>

OvREF_POINTER(OvObject);

class OvRelationLinkBuilder : public OvMemObject
{
	OvRTTI_DECL_ROOT(OvRelationLinkBuilder);
public:

	OvRelationLinkBuilder();
	virtual ~OvRelationLinkBuilder();

	virtual bool	BuildLink( restore_object_table& restoreTable ) = 0;

};

class OvPointLinkBuilder : public OvRelationLinkBuilder
{
	OvRTTI_DECL(OvPointLinkBuilder);
public:
	
	OvPointLinkBuilder();
	~OvPointLinkBuilder();
	
	void	SetDestination(OvObject** destination);
	OvObject** GetDestination();

	void	SetFormerID( const OvObjectID& );
	const OvObjectID& GetFormerID();

	virtual bool	BuildLink( restore_object_table& restoreTable ) override ;
private:

	OvObjectID	m_formerID;
	OvObject** m_destination;
};

class OvSmartLinkBuilder : public OvRelationLinkBuilder
{
	OvRTTI_DECL(OvSmartLinkBuilder);
public:

	OvSmartLinkBuilder();
	~OvSmartLinkBuilder();

	void	SetSmartDestination( OvObjectSPtr* destination );
	OvObjectSPtr* GetSmartDestination();

	void	SetFormerID( const OvObjectID& );
	const OvObjectID& GetFormerID();

	virtual bool	BuildLink( restore_object_table& restoreTable ) override ;

private:

	OvObjectID	m_formerID;
	OvObjectSPtr* m_destination;

};

class OvObjectCollector;
class OvObjectCollectorLinkBuilder : public OvRelationLinkBuilder
{
	OvRTTI_DECL(OvObjectCollectorLinkBuilder);
public:

	OvObjectCollectorLinkBuilder();
	~OvObjectCollectorLinkBuilder();

	void	SetDestinateCollector( OvObjectCollector* destination );
	OvObjectCollector* GetDestinateCollector();

	void	AddRelatedObjectID( const OvObjectID& objectID );

	virtual bool	BuildLink( restore_object_table& restoreTable ) override ;

private:

	OvObjectCollector* m_destination;
	std::vector< OvObjectID > m_relatedObjects;

};
