#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "tinyxml.h"
#include <algorithm>
#include <vector>
#include <map>
#include <queue>




struct OvObjectManager::OvPimple : OvMemObject
{
	OvObjectID		m_hMaxHandle;

};

OvObjectManager::OvObjectManager()
{
	m_pPimple = OvNew OvObjectManager::OvPimple;
}
OvObjectManager::~OvObjectManager()
{
	TiXmlDocument doc("Leaked_Object_Report");
	TiXmlElement root("Leaked_Object_Report");
	for each( object_table::value_type table_pair in m_objectTable )
	{
		OvObject* leackObj = table_pair.second;
		if ( leackObj )
		{
			TiXmlElement elem("report");
			string typeName = OvRTTI_Util::TypeName( leackObj );
			OvObjectID objID = leackObj->GetObjectID();
			string objName	 = leackObj->GetName();

			string reportContext = OvFormatString("[type: %s] [id: %d] [name: %s]"
				, typeName.c_str()
				, objID.core
				, objName.c_str() );
			elem.InsertEndChild( TiXmlText( reportContext.c_str() ) );
			root.InsertEndChild( elem );
		}
	}
	doc.InsertEndChild( root );

	time_t reportTime;
	time( &reportTime );
	tm* reportLocalTime = localtime( &reportTime );
	doc.SaveFile( OvFormatString("../../export/object_report/leacked_objects_report_%d_%d_%d.xml"
		, reportLocalTime->tm_hour
		, reportLocalTime->tm_min
		, reportLocalTime->tm_sec) );
}

OvObjectID		OvObjectManager::AllocObjectID(OvObject* _pObject)
{
	m_pPimple->m_hMaxHandle.core++;
	m_objectTable[m_pPimple->m_hMaxHandle] = _pObject;

	return m_pPimple->m_hMaxHandle;
}

void		OvObjectManager::RecallObjectID(OvObject* _pObject)
{
	//! 오브젝트는 오브젝트 테이블에서 삭제한다.
	m_objectTable.erase(_pObject->GetObjectID());
}
OvObject*			OvObjectManager::FindObject(const OvObjectID& rObjHandle)
{
	if (m_objectTable.find(rObjHandle) != m_objectTable.end())
	{
		return m_objectTable[rObjHandle];
	}
	return NULL;
}