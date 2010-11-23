#include "OvScene.h"
#include "OliveValue.h"
#include "OvCamera.h"
#include "OvModel.h"

#include <string>
using namespace std;

OvRTTI_IMPL( OvScene );

OvModelSPtr OvScene::CreateModel()
{
	return _set_and_return( OvNew OvModel );;
}

OvCameraSPtr OvScene::CreateCamera()
{
	return _set_and_return( OvNew OvCamera );
}

void OvScene::SetViewCamera( OvCameraSPtr camera )
{
	m_view_camera = camera;
}

OvCameraSPtr OvScene::GetViewCamera()
{
	return m_view_camera;
}

OvObjectSPtr OvScene::_find_object( const OvRTTI * rtti, const OvObjectID & objectID )
{
	OvObjectCollector & collector = m_object_table[ rtti ];
	return collector.GetByID( objectID );
}

OvObjectSPtr OvScene::_find_object( const OvRTTI * rtti, const std::string & objectName )
{
	OvObjectCollector & collector = m_object_table[ rtti ];
	return collector.GetByName( objectName );
}
OvObjectSPtr OvScene::_set_and_return( OvObjectSPtr object )
{
	if ( object )
	{
		const OvRTTI * rtti = object->QueryRTTI();
		OliveValue::ObjectID objID( object->GetObjectID() );

		string name = rtti->TypeName() + objID.GetValue();
		object->SetName( name.c_str() );
		
		m_object_table[ rtti ].AddObject( object );
	}
	return object;
}

OvModelSPtr OvScene::FindModel( const OvObjectID & objectID )
{
	return OvScene::FindObject<OvModel>( objectID );
}

OvModelSPtr OvScene::FindModel( const std::string & objectName )
{
	return OvScene::FindObject<OvModel>( objectName );
}

OvCameraSPtr OvScene::FindCamera( const OvObjectID & objectID )
{
	return OvScene::FindObject<OvCamera>( objectID );
}

OvCameraSPtr OvScene::FindCamera( const std::string & objectName )
{
	return OvScene::FindObject<OvCamera>( objectName );
}