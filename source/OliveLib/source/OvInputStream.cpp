#include "OvInputStream.h"
#include "OvAutoPtr.h"
OvRTTI_IMPL_ROOT(OvInputStream);
//////////////////////////////////////////////////////////////////////////

OvSize	OvInputStream::Skip( OvSize skip_size )
{
	OvArrayAutoPtr<OvByte> skip = new OvByte[skip_size];
	return ReadBytes( skip.GetRear(), skip_size );
}
//////////////////////////////////////////////////////////////////////////