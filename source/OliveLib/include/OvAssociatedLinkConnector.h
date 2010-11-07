#pragma once
#include "OvMemObject.h"
#include "OvSmartPointer.h"
#include "OvUtility_RTTI.h"
#include "OvStreamCommon.h"
#include "OvObjectID.h"
#include <vector>

OvREF_POINTER(OvObject);

class OvAssociatedLinkConnector : public OvMemObject
{
	OvRTTI_DECL_ROOT(OvAssociatedLinkConnector);
public:

	OvAssociatedLinkConnector();
	virtual ~OvAssociatedLinkConnector();

	virtual bool	ConnectLink( OvLinkageTable& restoreTable ) = 0;

};

class OvPointerLinkConnector : public OvAssociatedLinkConnector
{
	OvRTTI_DECL(OvPointerLinkConnector);
public:
	
	OvPointerLinkConnector();
	~OvPointerLinkConnector();
	
	void	SetDestination(OvObject** destination);
	OvObject** GetDestination();

	void	SetFormerID( const OvObjectID& );
	const OvObjectID& GetFormerID();

	virtual bool	ConnectLink( OvLinkageTable& restoreTable ) override ;
private:

	OvObjectID	m_formerID;
	OvObject** m_destination;
};

class OvSmartPtrLinkConnector : public OvAssociatedLinkConnector
{
	OvRTTI_DECL(OvSmartPtrLinkConnector);
public:

	OvSmartPtrLinkConnector();
	~OvSmartPtrLinkConnector();

	void	SetSmartDestination( OvObjectSPtr* destination );
	OvObjectSPtr* GetSmartDestination();

	void	SetFormerID( const OvObjectID& );
	const OvObjectID& GetFormerID();

	virtual bool	ConnectLink( OvLinkageTable& restoreTable ) override ;

private:

	OvObjectID	m_formerID;
	OvObjectSPtr* m_destination;

};

class OvObjectCollector;
class OvCollectedObjectsLinkConnector : public OvAssociatedLinkConnector
{
	OvRTTI_DECL(OvCollectedObjectsLinkConnector);
public:

	OvCollectedObjectsLinkConnector();
	~OvCollectedObjectsLinkConnector();

	void	SetDestinateCollector( OvObjectCollector* destination );
	OvObjectCollector* GetDestinateCollector();

	void	AddRelatedObjectID( const OvObjectID& objectID );

	virtual bool	ConnectLink( OvLinkageTable& restoreTable ) override ;

private:

	OvObjectCollector* m_destination;
	std::vector< OvObjectID > m_relatedObjects;

};
