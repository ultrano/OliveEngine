#include "OliveValue.h"
#include "OvTexture.h"
#include "OvRenderTexture.h"
#include "OvResourceManager.h"
#include "OvShaderCodeIncluder.h"

GL_TEST_CASE_FUNC( render_screen_rect_text )
{
	OvSingletonPool::StartUp();
	{
		OvRenderer::GetInstance()->GenerateRenderer();
		OvTextureSPtr testtex = OvResourceManager::GetInstance()->LoadResource<OvTexture>("../../resource/texture/save_test.jpg");

		OvShaderCodeIncluder includer("../OliveLib/shader", "../../resource");
		OvVertexShaderSPtr rectVertShader = OvShaderManager::GetInstance()->CreateVertexShaderFromFile
			( "../../resource/shader/rect.shacode"
			, "Vmain"
			, "vs_2_0"
			, &includer );
		OvPixelShaderSPtr rectPixelShader = OvShaderManager::GetInstance()->CreatePixelShaderFromFile
			( "../../resource/shader/rect.shacode"
			, "Pmain"
			, "ps_2_0"
			, &includer );
		OvRenderer::GetInstance()->SetVertexShader( rectVertShader );
		OvRenderer::GetInstance()->SetPixelShader( rectPixelShader );
		OvRenderer::GetInstance()->SetTexture( 0, testtex );
		while ( !( GetAsyncKeyState( VK_ESCAPE ) & 0x8000 ) )
		{
			OvRenderer::GetInstance()->ClearTarget();
			OvRenderer::GetInstance()->BeginTarget();
			OvRenderer::GetInstance()->RenderUnitRect();
			OvRenderer::GetInstance()->EndTarget();
			OvRenderer::GetInstance()->PresentTarget();
		}
	}
	OvSingletonPool::ShutDown();
}
GL_TEST_CASE_FUNC( olive_value_addtional_operator_test )
{

	OliveValue::Integer ovint(10);
	OliveValue::Float ovfloat(11);
	OliveValue::Bool ovbool(false);

	int kint = ovint.GetInteger();
	float kfloat = ovfloat.GetFloat();
	bool kbool = ovbool.GetBool();

	kint = ovint;
	kfloat = ovfloat;
	kbool = ovbool;

	kint = 20;
	kfloat = 22;
	kbool = true;

	ovint = kint;
	ovfloat = kfloat;
	ovbool = kbool;

	ovbool.SetValue("False");
	ovbool.SetValue("True");

}