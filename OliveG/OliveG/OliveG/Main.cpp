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
		m_mainCamera->SetTranslate(0,50,0);
		//m_mainCamera->SetRotation( OvQuaternion().MakeQuaternion(OvPoint3(-1,0,0),D3DX_PI/2.0f) );
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
		OvRenderer::GetInstance()->GenerateRenderer();
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
					
					accumPt->SetPoint2( accumPt->GetPoint2() + OvInputDevice::GetInstance()->GetMouseInterval() );
				}
			}
			break;
		case WM_KEYDOWN : 
			{
				float moveSpeed = 1.0f;
				switch ( msg.wParam )
				{
				case VK_UP :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() + GetMainCamera()->GetLocalLookDirection() * moveSpeed );
					break;
				case VK_DOWN :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() - GetMainCamera()->GetLocalLookDirection() * moveSpeed );
					break;
				case VK_LEFT :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() - GetMainCamera()->GetLocalRightDirection() * moveSpeed );
					break;
				case VK_RIGHT :
					GetMainCamera()->SetTranslate( GetMainCamera()->GetTranslate() + GetMainCamera()->GetLocalRightDirection() * moveSpeed );
					break;
				}
			}
			break;
		}


	}
	void UpdateAndCommit()
	{

		float timeCycle = GetTickCount();
		timeCycle = timeCycle / 1000.0f;

		GetMainCamera()->Update(0);
		GetTestModel()->Update(0);

		OvMatrix view_project = GetMainCamera()->GetViewMatrix() * GetMainCamera()->GetProjectMatrix();
		OvShaderManager::GetInstance()->SetPSConst( OvMatPSConst::Time, timeCycle);
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::Time, timeCycle);
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::ViewProject, view_project );
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::ViewPos, GetMainCamera()->GetWorldTranslate() );

	}
	void RenderSimpleTriangle()
	{
		OvFileMeshLoader meshLoader;
		OvTextureLoader	texLoader;
		OvMeshSPtr testMesh = meshLoader.Load("../../export/test.msf0");

		GetTestModel()->SetMesh( testMesh );
		GetTestModel()->SetStageTexture( OvModel::Diffuse, texLoader.Load( "../../export/test.jpg" ) );
		GetTestModel()->SetStageTexture( OvModel::Normal, texLoader.Load( "../../export/normal.jpg" ) );


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

GL_TEST_CASE_ENV( OliveLibTest, mesh_loader )
{
// 	CreateDxDevice();
// 	OvFileMeshLoader file_loader;
// 	file_loader.Load( "../../export/mesh_test.mesh0" );
}


int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GL_RUN_ALL_TEST();
};
