#include "OvOutputStream.h"
#include "OvAutoPtr.h"
OvRTTI_IMPL_ROOT(OvOutputStream);

OvSize	OvOutputStream::Skip( OvSize skip_size )
{
	OvArrayAutoPtr<OvByte> skip = new OvByte[skip_size];
	return WriteBytes( skip.GetRear(), skip_size );
}