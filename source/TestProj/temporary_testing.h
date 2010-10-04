#include "OliveValue.h"
#include "OvTexture.h"
#include "OvRenderTexture.h"
#include "OvResourceManager.h"
#include "OvShaderCodeIncluder.h"

GL_TEST_CASE_FUNC( excuted_location_test )
{
	OvSingletonPool::StartUp();
	{
		string excuted_location;
		excuted_location.resize( 1024 );
		GetModuleFileName(NULL,(LPCH)excuted_location.c_str(),excuted_location.size());
		excuted_location.data();

		std::string	directory = OvGetDirectoryInFullFilePath( excuted_location );
		directory = OvGetDirectoryInFullFilePath( directory );
		directory = OvGetDirectoryInFullFilePath( directory );
		std::string	file_name = OvGetFileNameInFullFilePath( excuted_location );
		std::string	file_ext = OvGetExtentionInFullFilePath( excuted_location );
	}
	OvSingletonPool::ShutDown();
}
GL_TEST_CASE_FUNC( resource_reload_and_ticket_test )
{
	OvSingletonPool::StartUp();
	{
		const string file_location = "texture/test.jpg";
		OvRenderer::GetInstance()->GenerateRenderer();
		OvTextureSPtr resource = OvResourceManager::GetInstance()->LoadResource<OvTexture>( ResDirPath( file_location ) );

		OvResourceTicketSPtr ticket = OvResourceManager::GetInstance()->CheckIn( resource );

		OvResourceSPtr old_resource = ticket->CheckOut();

		OvResourceManager::GetInstance()->ReloadResource( file_location );

		OvResourceSPtr new_resource = ticket->CheckOut();

	}
	OvSingletonPool::ShutDown();
}

GL_TEST_CASE_FUNC( render_screen_rect_text )
{
	OvSingletonPool::StartUp();
	{
		OvRenderer::GetInstance()->GenerateRenderer();
		OvTextureSPtr testtex = OvResourceManager::GetInstance()->LoadResource<OvTexture>( ResDirPath("texture/save_test.jpg") );

		OvShaderCodeIncluder includer;
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