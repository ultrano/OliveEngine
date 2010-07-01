#include "include_header.h"

GL_ENVIROMENT(OliveLibTest)
{
	GL_ENV_SET_UP
	{
		OvSingletonPool::StartUp();
// #ifdef _WINDOWS
// #ifdef _DEBUG
// 		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
// 
// 		_CrtSetBreakAlloc(2828);
// #endif
// #endif


	};
	GL_ENV_TEAR_DOWN
	{
		OvSingletonPool::ShutDown();
	}
public:
	void CreateDxDevice()
	{
		OvRenderer::GetInstance()->GenerateRenderer(
			CreateWindow("listbox","listbox",WS_OVERLAPPEDWINDOW | WS_VISIBLE,50,50,400,300,NULL,NULL,GetModuleHandle(NULL),NULL)
			);
	};
	void CreateShader()
	{
		LPDIRECT3DVERTEXSHADER9 vertShader = OvShaderManager::GetInstance()->CreateVertexShaderFromFile
			( "../../OliveGLib/shader/testV.fx"
			, "Vmain"
			, "vs_2_0");

		LPDIRECT3DPIXELSHADER9 pixelShader = OvShaderManager::GetInstance()->CreatePixelShaderFromFile
			( "../../OliveGLib/shader/testP.fx"
			, "Pmain"
			, "ps_2_0");

		if ( vertShader )
		{
			OvRenderer::GetInstance()->GetDevice()->SetVertexShader( vertShader );
		}

		if ( pixelShader )
		{
			OvRenderer::GetInstance()->GetDevice()->SetPixelShader( pixelShader );
		}
	}
	void RenderSimpleTriangle()
	{
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::Matrix_WorldViewProject, OvMatrix() );
		OvShaderManager::GetInstance()->SetPSConst( OvMatPSConst::Float_Test, OvPoint3(0,1,0) );

		OvMeshSPtr mesh = new OvMesh;
		mesh->Load("");
		MSG msg;
		ZeroMemory( &msg, sizeof( msg ) );
		if ( msg.message != WM_QUIT )
		{
			while ( msg.message != WM_QUIT )
			{
				if ( PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
					OvRenderer::GetInstance()->ClearTarget();
					OvRenderer::GetInstance()->BeginTarget();
					mesh->Rendering();
					OvRenderer::GetInstance()->EndTarget();
					OvRenderer::GetInstance()->PresentTarget();
				}
			}
		}
	}
};

GL_TEST_CASE_ENV( OliveLibTest, shader )
{
	CreateDxDevice();
	CreateShader();
}

GL_TEST_CASE_ENV( OliveLibTest, mesh_rendering )
{
	CreateDxDevice();
	CreateShader();
	RenderSimpleTriangle();
};

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GL_RUN_ALL_TEST();
};
