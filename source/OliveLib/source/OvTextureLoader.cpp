#include "OvTextureLoader.h"
#include "OvTexture.h"
#include "OvRenderer.h"
#include "OvDataStream.h"

OvRTTI_IMPL( OvTextureLoader );

OvResourceSPtr OvTextureLoader::Load( OvDataStream& stream )
{
	OvDevice device = OvRenderer::GetInstance()->GetDevice();
	if ( device )
	{
		LPDIRECT3DTEXTURE9	kpTexture = NULL;
		if ( SUCCEEDED( D3DXCreateTextureFromFileInMemory( device
			, (LPCVOID)	stream.Ptr()
			, (UINT)	stream.Size()
			, &kpTexture ) ) )
		{
			OvTextureSPtr texture = OvNew OvTexture( kpTexture, eTexUsage_Texture );
			return texture;
		}
	}
	return NULL;
}
