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
};

GL_TEST_CASE_ENV( OliveLibTest, property_bag_test )
{
	CreateDxDevice();

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	if ( msg.message != WM_QUIT )
	{
		while ( PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );

		}
	}
};

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GL_RUN_ALL_TEST();
};
