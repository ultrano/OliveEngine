#pragma once
#include "OvTypeDef.h"
#include "OvUtility_RTTI.h"
#include "OvRefObject.h"

OvREF_POINTER( OvOutputStream );
interface_class OvOutputStream : public OvRefObject
{
	OvRTTI_DECL_ROOT(OvOutputStream);

	//! override method
	virtual OvSize WriteBytes( OvByte * write_buf, OvSize write_size ) = 0;
	virtual OvSize	Skip( OvSize offset ) = 0;
	//

	template<typename T>
	OvBool	Write( const T& data )
	{
		return !!WriteBytes( (OvByte*)&data, sizeof(T) );
	};

	OvBool Write( const OvString& data )
	{
		OvSize size = (OvSize)data.size();
		Write( size );
		return !!WriteBytes( (OvByte*)&data[0], size );
	};
	OvBool Write( const OvChar* data){ return Write( OvString(data) ); };

};