#pragma once
#include "OvSingleton.h"
#include "OvXNode.h"
#include "OvObjectCollector.h"
#include <map>

OvREF_POINTER(OvModel);
OvREF_POINTER(OvCamera);

class OvSingleScene : public OvSingletonBase<OvSingleScene>
{
	
	typedef std::map< const OvRTTI *, OvObjectCollector > object_table;

public: //!< Create Method

	OvModelSPtr		CreateModel();
	OvCameraSPtr	CreateCamera();

public:

	void			SetViewCamera( OvCameraSPtr camera );
	OvCameraSPtr	GetViewCamera();

public: //!< Find Method

	OvModelSPtr		FindModel( const OvObjectID & objectID );
	OvModelSPtr		FindModel( const std::string & objectName );

	OvCameraSPtr	FindCamera( const OvObjectID & objectID );
	OvCameraSPtr	FindCamera( const std::string & objectName );

	template<typename T>
	OvSmartPointer<T> FindObject( const OvObjectID & objectID );
	template<typename T>
	OvSmartPointer<T> FindObject( const std::string & objectName );

private:

	OvObjectSPtr	_find_object( const OvRTTI * rtti, const OvObjectID & objectID );
	OvObjectSPtr	_find_object( const OvRTTI * rtti, const std::string & objectName );

	OvObjectSPtr	_set_and_return( OvObjectSPtr object );

private:

	object_table	m_object_table;

	OvCameraSPtr	m_view_camera;

	//OvObjectCollector	m_
};

template<typename T>
OvSmartPointer<T> OvSingleScene::FindObject( const OvObjectID & objectID )
{
	return _find_object( T::GetRTTI(), objectID );
}
template<typename T>
OvSmartPointer<T> OvSingleScene::FindObject( const std::string & objectName )
{
	return _find_object( T::GetRTTI(), objectName );
}