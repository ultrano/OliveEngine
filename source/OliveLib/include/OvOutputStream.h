#pragma once
#include "OvTypeDef.h"
#include "OvUtility_RTTI.h"
#include "OvRefBase.h"

OvREF_POINTER( OvOutputStream );
interface_class OvOutputStream : public OvRefBase
{
	OvRTTI_DECL_ROOT(OvOutputStream);

	virtual OvBool WriteByte( OvByte write ) = 0;
	virtual OvSize WriteBytes( OvByte * write_buf, OvSize write_size ) = 0;

	template<typename T>
	OvBool	Write( T& data )
	{
		return !!WriteBytes( (OvByte*)&data, sizeof(T) );
	};

	OvBool Write( OvString& data )
	{
		OvSize size = (OvSize)data.size();
		Write( size );
		return !!WriteBytes( (OvByte*)&data[0], size );
	};

};