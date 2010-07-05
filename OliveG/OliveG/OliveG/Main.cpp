#include "include_header.h"

GL_ENVIROMENT(OliveLibTest)
{
private:
	OvCameraSPtr m_mainCamera;
	OvModelSPtr m_testModel;
protected:
	OvCameraSPtr GetMainCamera(){return m_mainCamera;};
	OvModelSPtr	 GetTestModel(){return m_testModel;};

public:
	GL_ENV_SET_UP
	{
		OvSingletonPool::StartUp();

		m_mainCamera = new OvCamera;
		m_mainCamera->SetTranslate(0,0,-2);
		m_mainCamera->SetRotation( OvQuaternion().MakeQuaternion(OvPoint3(-1,0,0),D3DX_PI/2.0f) );
		m_mainCamera->Update(0);

		m_mainCamera->RegisterExtraProperty("accumPt", OliveValue::ValueFactory("Point2") );

		m_testModel = new OvModel;
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
		m_mainCamera = NULL;
		m_testModel = NULL;

		OvSingletonPool::ShutDown();
	}
public:
	void CreateDxDevice()
	{
		OvRenderer::GetInstance()->GenerateRenderer(
			CreateWindow("listbox","listbox",WS_OVERLAPPEDWINDOW | WS_VISIBLE,50,50,800,600,NULL,NULL,GetModuleHandle(NULL),NULL)
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
	void ControlMainCamera( MSG msg )
	{
		OvPoint3 curPos = GetMainCamera()->GetTranslate();
		switch ( msg.message )
		{
		case WM_MOUSEMOVE : 
			{
				OliveValue::Point2*	accumPt = (OliveValue::Point2*)GetMainCamera()->FindExtraProperty("accumPt");
				if ( accumPt )
				{
					OvQuaternion yRot,xRot;
					yRot.MakeQuaternion(OvPoint3::AXIS_Y, accumPt->GetPoint2().y / (D3DX_PI * 20.0f) );
					xRot.MakeQuaternion(OvPoint3::AXIS_X, accumPt->GetPoint2().x / (D3DX_PI * 20.0f));
					
					GetMainCamera()->SetRotation( yRot * xRot );
					
					accumPt->SetPoint2( accumPt->GetPoint2() + OvInputManager::GetInstance()->GetMouseInterval() );
				}
			}
			break;
		case WM_KEYDOWN : 
			{
				switch ( msg.wParam )
				{
				case VK_UP :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() + GetMainCamera()->GetLocalLookDirection() / 10.0f );
					break;
				case VK_DOWN :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() - GetMainCamera()->GetLocalLookDirection() / 10.0f );
					break;
				case VK_LEFT :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() - GetMainCamera()->GetLocalRightDirection() / 10.0f );
					break;
				case VK_RIGHT :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() + GetMainCamera()->GetLocalRightDirection() / 10.0f );
					break;
				}
			}
			break;
		}


	}
	void UpdateAndCommit()
	{

		GetMainCamera()->Update(0);
		GetTestModel()->Update(0);

		OvMatrix view_project = GetMainCamera()->GetViewMatrix() * GetMainCamera()->GetProjectMatrix();
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::Matrix_ViewProject, view_project );

	}
	void RenderSimpleTriangle()
	{
		OvMeshSPtr testMesh = new OvMesh;
		testMesh->Load("../../export/mesh_test.xml");
		GetTestModel()->SetMesh( testMesh );
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
					OvInputManager::ListenMessage( msg.hwnd, msg.message, msg.wParam, msg.lParam );
					ControlMainCamera( msg );
					UpdateAndCommit();

					OvRenderer::GetInstance()->ClearTarget();
					OvRenderer::GetInstance()->BeginTarget();
					GetTestModel()->Render();
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
