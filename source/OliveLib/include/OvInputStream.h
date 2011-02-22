#pragma once
#include "OvTypeDef.h"
#include "OvUtility_RTTI.h"
#include "OvRefBase.h"

OvREF_POINTER( OvInputStream );
interface_class OvInputStream : public OvRefBase
{
	OvRTTI_DECL_ROOT(OvInputStream);

	virtual OvBool ReadByte( OvByte & read ) = 0 ;
	virtual OvSize ReadBytes( OvByte * dest, OvSize dest_size ) = 0 ;

	template<typename T>
	OvBool	Read( T& data )
	{
		return !!ReadBytes( (OvByte*)&data, sizeof(T) );
	};

	OvBool Read( OvString& data )
	{
		OvSize size = 0;
		Read( size );
		data.resize( size );
		return !!ReadBytes( (OvByte*)&data[0], size );
	};

};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////