#include "OvMaterial.h"
#include "OvRenderer.h"
#include "OvShaderManager.h"
#include "OvPixelShader.h"
#include "OvVertexShader.h"
#include "OvTexture.h"
#include "OvResourceManager.h"
#include "OvRegisterableProperties.h"

OvRTTI_IMPL( OvMaterial );


OvMaterial::OvMaterial()
: m_vertexShader( NULL )
, m_pixelShader( NULL )
{

}

OvMaterial::~OvMaterial()
{
	m_vertexShader = NULL;
	m_pixelShader = NULL;
}

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
	m_stageTexture[stageIndex] = OvResourceManager::GetInstance()->FindTicket( texture );
}

void OvMaterial::SetStageTexture( TextureStage stageIndex, OvResourceTicketSPtr ticket )
{
	m_stageTexture[stageIndex] = ticket;
}
OvTextureSPtr OvMaterial::GetStageTexture( OvMaterial::TextureStage stageIndex )
{
	 OvResourceTicketSPtr ticket = m_stageTexture[stageIndex];
	 if ( ticket )
	 {
		return ticket->CheckOut();
	 }
	 return NULL;
}

void OvMaterial::ApplyMaterial()
{
	OvRenderer::GetInstance()->SetVertexShader( GetVertexShader() );
	OvRenderer::GetInstance()->SetPixelShader( GetPixelShader() );

	for ( int i = 0 
		; i < MaxStage 
		; ++i )
	{
		OvRenderer::GetInstance()->SetTexture( i , GetStageTexture( (TextureStage)i ) );
	}

}