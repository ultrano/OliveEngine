#include "OvShaderCodeLoader.h"
#include "OvShaderCode.h"
#include "OvBufferInputStream.h"
#include "OvBuffer.h"

OvRTTI_IMPL( OvShaderCodeLoader );
OvFACTORY_OBJECT_IMPL(OvShaderCodeLoader);

OvResourceSPtr OvShaderCodeLoader::Load( OvBufferInputStream& bis )
{
	OvBufferSPtr buf = bis.GetBuffer();
	return OvNew OvShaderCode( (const char*)buf->Pointer(), buf->Size() );
}