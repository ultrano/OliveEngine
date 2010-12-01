#pragma once
#include "OvMemObject.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
#include "OvObjectID.h"
#include <string>
using namespace std;
OvREF_POINTER(OvObject);


namespace Olive
{

	typedef OvObject* (*construct_function)(void);
	OvObjectSPtr	CreateObject( const std::string& type_name );
	OvObject*		CreateObject_Ptr( const std::string& type_name );
	void			RegisterConstructFunc( const char* type_name, construct_function func );

	struct OvFactoryMemberDeclarer
	{
		OvFactoryMemberDeclarer( const char* type_name, construct_function func );
	};

#define OvFACTORY_OBJECT_DECL( type_name ) \
	static OvObject* _construct_function_(){ return OvNew type_name; };\
	static Olive::OvFactoryMemberDeclarer _static_factory_declarer;

#define OvFACTORY_OBJECT_IMPL( type_name ) \
	OvObject* _construct_function_##type_name(){ return type_name::_construct_function_(); }\
	Olive::OvFactoryMemberDeclarer type_name::_static_factory_declarer( #type_name, _construct_function_##type_name);

}