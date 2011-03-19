#include "OvObjectOutputStream.h"
#include "OvObject.h"

OvObjectOutputStream::OvObjectOutputStream( OvOutputStream* output )
: m_output( output )
{

}

OvObjectOutputStream::~OvObjectOutputStream()
{

}

OvSize OvObjectOutputStream::WriteBytes( OvByte * write_buf, OvSize write_size )
{
	if ( m_output )
	{
		return m_output->WriteBytes( write_buf, write_size );
	}
	return 0;
}

OvSize OvObjectOutputStream::Skip( OvSize offset )
{
	if ( m_output )
	{
		return m_output->Skip( offset );
	}
	return 0;
}

OvBool OvObjectOutputStream::WriteObject( OvObjectSPtr obj )
{
	OvObjectID objID = OvObjectID::INVALID;
	OvString type_name = "";
	if ( obj )
	{
		m_serialize_targets.insert( obj );
		objID = obj->GetObjectID();
		type_name = OvTypeName( obj );
	}
	Write( objID );
	Write( type_name );
	return !!obj;
}

OvBool OvObjectOutputStream::Serialize( OvObjectSPtr obj )
{
	WriteObject( obj );

	OvSet<OvObjectSPtr> copy_targets;
	while ( m_serialize_targets.size() != m_serialized.size() )
	{
		copy_targets = m_serialize_targets;
		for each( OvObjectSPtr target in copy_targets )
		{
			if ( m_serialized.find( target ) == m_serialized.end() )
			{
				target->Serialize( *this );
				m_serialized.insert( target );
			}
		}
	}
	return true;
}
