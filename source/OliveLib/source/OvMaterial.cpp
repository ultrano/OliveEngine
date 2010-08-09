#include "OvMaterial.h"
#include "OvRenderer.h"
#include "OvShaderManager.h"

#include "OvRegisterableProperties.h"

OvRTTI_IMPL( OvMaterial );

void OvMaterial::SetVertexShader( OvVertexShaderSPtr shader )
{
	m_vertexShader = shader;
}

OvVertexShaderSPtr OvMaterial::GetVertexShader()
{
	return m_vertexShader;
}

void OvMaterial::SetPixelShader( OvPixelShaderSPtr shader )
{
	m_pixelShader = shader;
}

OvPixelShaderSPtr OvMaterial::GetPixelShader()
{
	return m_pixelShader;
}

void OvMaterial::SetStageTexture( OvMaterial::TextureStage stageIndex, OvTextureSPtr texture )
{
	m_stageTexture[stageIndex] = texture;
}

OvTextureSPtr OvMaterial::GetStageTexture( OvMaterial::TextureStage stageIndex )
{
	return m_stageTexture[stageIndex];
}

void OvMaterial::ApplyMaterial()
{
	OvRenderer::GetInstance()->SetVertexShader( m_vertexShader );
	OvRenderer::GetInstance()->SetPixelShader( m_pixelShader );

	for ( int i = 0 
		; i < TextureStage::MaxStage 
		; ++i )
	{
		OvShaderManager::GetInstance()->SetTexture( i , m_stageTexture[i] );
	}

}