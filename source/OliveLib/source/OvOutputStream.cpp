#include "OvOutputStream.h"
#include "OvAutoPtr.h"
OvRTTI_IMPL_ROOT(OvOutputStream);

OvSize	OvOutputStream::Skip( OvSize skip_size )
{
	if ( skip_size > 0 )
	{
		OvArrayAutoPtr<OvByte> skip = new OvByte[skip_size];
		return WriteBytes( skip.GetRear(), skip_size );
	}
	return 0;
}