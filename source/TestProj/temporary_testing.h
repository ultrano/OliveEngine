#include "OliveValue.h"
#include "OvTexture.h"
#include "OvRenderTarget.h"

GL_TEST_CASE_FUNC( render_texture_test_case )
{
	OvSingletonPool::StartUp();
	{
		OvRenderer::GetInstance()->GenerateRenderer();
		OvRenderTargetSPtr render_texture = CreateRenderTexture( 256, 256, 1, D3DFMT_A8B8G8R8 );
		OliveValue::Bool result;
		result = render_texture->Begin();
		result = render_texture->End();
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