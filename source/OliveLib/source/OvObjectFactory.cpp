#include "OvObjectFactory.h"
#include "OvXNode.h"
#include <map>
using namespace std;
using namespace Olive;

struct OvObjectFactory
{
	map<string, construct_function > factory_table;
};

OvObjectFactory& GetFactory()
{
	static OvObjectFactory static_factory;
	return static_factory;
}

OvObjectSPtr Olive::CreateObject( const std::string& type_name )
{
	construct_function func = GetFactory().factory_table[ type_name ];
	return ( func )? ( func() ) : ( 0 );
}

OvObject* Olive::CreateObject_Ptr( const std::string& type_name )
{
	construct_function func = GetFactory().factory_table[ type_name ];
	return ( func )? ( func() ) : ( 0 );
}

void Olive::RegisterConstructFunc( const char* type_name, construct_function func )
{
	GetFactory().factory_table[ string( type_name ) ] = func;
}
Olive::OvFactoryMemberDeclarer::OvFactoryMemberDeclarer( const char* type_name, construct_function func )
{
	RegisterConstructFunc( type_name, func );
}