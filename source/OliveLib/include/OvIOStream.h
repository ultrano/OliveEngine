#pragma once
#pragma warning( disable : 4521)

#include "OvTypeDef.h"
#include "OvMemObject.h"
#include "OvOutputStream.h"
#include "OvInputStream.h"

interface_class OvIOStream : public OvInputStream, public OvOutputStream, public OvMemObject
{
	OvRTTI_DECL_EX(OvIOStream,OvInputStream,OvOutputStream);

	virtual OvInputStream& Read( OvString& buf, OvUInt read_size ) = 0 ;
	virtual OvInputStream& ReadLine( OvString& buf )  = 0 ;
};