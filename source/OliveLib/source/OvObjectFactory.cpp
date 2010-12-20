#include "OvObjectFactory.h"
#include "OvXNode.h"
#include <map>
using namespace std;
using namespace Olive;

struct OvObjectFactory
{
	map<OvString, construct_function > factory_table;
};

OvObjectFactory& GetFactory()
{
	static OvObjectFactory static_factory;
	return static_factory;
}

OvBool Olive::IsObjectCreatable( const OvString& type_name )
{
	map<OvString, construct_function >::iterator itor = GetFactory().factory_table.find( type_name );
	return ( itor != GetFactory().factory_table.end() );
}

OvObjectSPtr Olive::CreateObject( const OvString& type_name )
{
	construct_function func = GetFactory().factory_table[ type_name ];
	return ( func )? ( func() ) : ( 0 );
}

OvObject* Olive::CreateObject_Ptr( const OvString& type_name )
{
	construct_function func = GetFactory().factory_table[ type_name ];
	return ( func )? ( func() ) : ( 0 );
}

void Olive::RegisterConstructFunc( const OvChar* type_name, construct_function func )
{
	GetFactory().factory_table[ OvString( type_name ) ] = func;
}
Olive::OvFactoryMemberDeclarer::OvFactoryMemberDeclarer( const OvChar* type_name, construct_function func )
{
	RegisterConstructFunc( type_name, func );
}