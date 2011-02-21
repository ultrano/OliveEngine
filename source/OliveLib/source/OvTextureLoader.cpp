#include "OvTextureLoader.h"
#include "OvTexture.h"
#include "OvRenderer.h"
#include "OvBufferInputStream.h"
#include "OvBuffer.h"


OvRTTI_IMPL( OvTextureLoader );
OvFACTORY_OBJECT_IMPL(OvTextureLoader);

OvResourceSPtr OvTextureLoader::Load( OvBufferInputStream& bis )
{
	OvDevice device = OvRenderer::GetInstance()->GetDevice();
	if ( device )
	{
		OvBufferSPtr buf = bis.GetBuffer();
		LPDIRECT3DTEXTURE9	kpTexture = NULL;
		if ( SUCCEEDED( D3DXCreateTextureFromFileInMemory( device
			, (LPCVOID)	buf->Pointer()
			, (UINT)	buf->Size()
			, &kpTexture ) ) )
		{
			OvTextureSPtr texture = OvNew OvTexture( kpTexture, eTexUsage_Texture );
			return texture;
		}
	}
	return NULL;
}
