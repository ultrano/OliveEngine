#pragma once
#include "OvResource.h"
#include "OvAutoPtr.h"
#include "OvResourceTicket.h"
#include <map>
//
//OvREF_POINTER(OvTexture);
//OvREF_POINTER(OvMesh);
//

OvREF_POINTER(OvPixelShader);
OvREF_POINTER(OvVertexShader);
OvREF_POINTER(OvTexture);
OvREF_POINTER(OvMaterial);
class OvMaterial : public OvResource
{
	OvRTTI_DECL( OvMaterial );
public:
	typedef std::map<pair<DWORD,DWORD>,DWORD> sampler_state_table;

	// 요고는 마테리얼 부분으로 빼자
	enum TextureStage
	{
		Stage0,
		Stage1,
		MaxStage
	};

	OvMaterial();
	~OvMaterial();

	void	SetSamplerState( DWORD sampler, DWORD type, DWORD value );
	OvBool	GetSamplerState( DWORD sampler, DWORD type, DWORD& value );

	void	SetVertexShader( OvVertexShaderSPtr shader );
	OvVertexShaderSPtr GetVertexShader();

	void	SetPixelShader( OvPixelShaderSPtr shader );
	OvPixelShaderSPtr GetPixelShader();

	void	SetStageTexture( TextureStage stageIndex,  OvResourceTicketSPtr ticket  );
	void	SetStageTexture( TextureStage stageIndex, OvTextureSPtr texture );
	OvTextureSPtr GetStageTexture( TextureStage stageIndex);

	void	ApplyMaterial();

private:

	OvVertexShaderSPtr m_vertexShader;
	OvPixelShaderSPtr m_pixelShader;
	OvResourceTicketSPtr	m_stageTexture[ MaxStage ];
	sampler_state_table	m_sampler_states;
};
