#pragma once
#include "OvResource.h"
#include "OvAutoPtr.h"
#include "OvResourceTicket.h"
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

	// 요고는 마테리얼 부분으로 빼자
	enum TextureStage
	{
		Stage0,
		Stage1,
		MaxStage
	};

	OvMaterial();
	~OvMaterial();

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

};
