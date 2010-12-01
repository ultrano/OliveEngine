#pragma once
#include "OvSingleton.h"
#include "OvObject.h"
#include "OvObjectCollector.h"
#include <map>

OvREF_POINTER(OvObject);
OvREF_POINTER(OvModel);
OvREF_POINTER(OvCamera);

class OvSingleScene : public OvSingletonBase< OvSingleScene >
{
	typedef std::map< const OvRTTI *, OvObjectCollector > object_table;
public: //!< Create Method

	OvSingleScene();
	~OvSingleScene();

	OvModelSPtr		CreateModel();
	OvCameraSPtr	CreateCamera();

public:

	void			SetViewCamera( OvCameraSPtr camera );
	OvCameraSPtr	GetViewCamera();

public: //!< Find Method

	template<typename T>
	OvSmartPointer<T> FindObject( const OvObjectID & objectID );
	template<typename T>
	OvSmartPointer<T> FindObject( const OvString & objectName );

private:

	OvObjectSPtr	_find_object( const OvRTTI * rtti, const OvObjectID & objectID );
	OvObjectSPtr	_find_object( const OvRTTI * rtti, const OvString & objectName );

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
OvSmartPointer<T> OvSingleScene::FindObject( const OvString & objectName )
{
	return _find_object( T::GetRTTI(), objectName );
}