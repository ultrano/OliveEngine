#include "OvSingleScene.h"
#include "OliveValue.h"
#include "OvCamera.h"
#include "OvModel.h"

#include <string>
using namespace std;

OvSingleScene::OvSingleScene()
{

}

OvSingleScene::~OvSingleScene()
{

}

OvModelSPtr OvSingleScene::CreateModel()
{
	return _set_and_return( OvNew OvModel );;
}

OvCameraSPtr OvSingleScene::CreateCamera()
{
	//return _set_and_return( OvNew OvCamera );
	return NULL;
}

void OvSingleScene::SetViewCamera( OvCameraSPtr camera )
{
	m_view_camera = camera;
}

OvCameraSPtr OvSingleScene::GetViewCamera()
{
	return m_view_camera;
}

OvObjectSPtr OvSingleScene::_find_object( const OvRTTI * rtti, const OvObjectID & objectID )
{
	OvObjectCollector & collector = m_object_table[ rtti ];
	return collector.GetByID( objectID );
}

OvObjectSPtr OvSingleScene::_find_object( const OvRTTI * rtti, const std::string & objectName )
{
	OvObjectCollector & collector = m_object_table[ rtti ];
	return collector.GetByName( objectName );
}
OvObjectSPtr OvSingleScene::_set_and_return( OvObjectSPtr object )
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
