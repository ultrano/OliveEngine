#include "OvShaderCodeLoader.h"
#include "OvShaderCode.h"
#include "OvDataStream.h"

OvRTTI_IMPL( OvShaderCodeLoader );

OvResourceSPtr OvShaderCodeLoader::Load( OvDataStream& stream )
{
	return OvNew OvShaderCode( stream.Ptr() );
}