#include "OvObjectInputStream.h"
#include "OvObject.h"

OvObjectInputStream::OvObjectInputStream( OvInputStream* input )
: m_input( input )
{

}

OvObjectInputStream::~OvObjectInputStream()
{

}

OvSize OvObjectInputStream::ReadBytes( OvByte * dest, OvSize dest_size )
{
	if ( m_input )
	{
		return m_input->ReadBytes( dest, dest_size );
	}
	return 0;
}

OvObject* OvObjectInputStream::ReadObject()
{
	OvObjectID	oldID;
	OvString	type_name;
	Read( oldID );
	Read( type_name );

	OvObjectSPtr obj = NULL;
	if ( oldID != OvObjectID::INVALID )
	{
		restore_table::iterator itor = m_restore_table.find( oldID );
		if ( itor != m_restore_table.end() )
		{
			obj = itor->second;
		}
		else
		{
			obj = Olive::CreateObject( type_name );
			m_restore_table[ oldID ] = obj;
		}
	}
	return obj.GetRear();
}

OvObject* OvObjectInputStream::Deserialize()
{
	OvObject* root = ReadObject();

	restore_table copy_table;
	while ( m_deseiralied.size() != m_restore_table.size() )
	{
		copy_table = m_restore_table;
		for each ( const restore_table::value_type val in copy_table )
		{
			OvObject* obj = val.second.GetRear();
			if ( m_deseiralied.find(obj) == m_deseiralied.end() )
			{
				obj->Deserialize( *this );
				m_deseiralied.insert( obj );
			}
		}
	}
	return root;
}
