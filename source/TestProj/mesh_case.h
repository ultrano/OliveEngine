
#include "include_header.h"
#include "OvXObject.h"
#include "OvCameraController.h"
#include "OvRenderTexture.h"
#include "OvShaderCodeIncluder.h"
#include "OvShaderCode.h"

class testcomponent : public OvXComponent
{
public:
	testcomponent():m_radian(0){};
	virtual void SetUp() override
	{
		m_startpt = GetTarget()->GetTranslate();
	}
	virtual void Update(float _fElapse) override
	{
		m_radian += (D3DX_PI/180.0f);
		//OvPoint3 dir( cosf(m_radian),0,sinf(m_radian));
		//GetTarget()->SetTranslate( m_startpt + dir * 5 );
		
		//GetTarget()->SetRotation(GetTarget()->GetRotation()*OvQuaternion().MakeQuaternion(0,1,0,(D3DX_PI/180.0f)));

	}
private:
	OvPoint3 m_startpt;
	float m_radian;
};

GL_TEST_ENVIROMENT( OliveLibTest )
{
private:
protected:
	OvRenderTarget m_renderTarget;
	OvTextureSPtr m_diffuseScene;
	
	OvShaderCodeSPtr m_shader_code;

	OvCameraSPtr m_mainCamera;
	OvObjectCollector m_loadedObjects;

	bool m_exitFlag;
public:
	GL_ENV_SET_UP
	{
		m_exitFlag = false;
		OvSingletonPool::StartUp();
		OvRenderer::GetInstance()->GenerateRenderer();

		OvStorage store;
		if ( ! store.Load( ResDirPath("ovf/scene_test.xml"), m_loadedObjects) )
		{
			OvMessageBox("¸ÁÇÞ¾î¿°^_^ ·Îµù ¤¤¤¤","");
			m_exitFlag = true;
		}
		m_mainCamera = m_loadedObjects.GetByName("Camera");
		m_mainCamera->SetFOV( D3DX_PI/2.0f );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		m_diffuseScene = CreateRenderTexture( 800, 600, 1, D3DFMT_A8B8G8R8 );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		m_shader_code = OvResourceManager::GetInstance()->LoadResource<OvShaderCode>( ResDirPath("shader/test.shacode") );

		m_shader_code->CompileVertexShader( "rectV", "vs_2_0" );
		m_shader_code->CompilePixelShader( "rectP", "ps_2_0" );
	};
	GL_ENV_TEAR_DOWN
	{
		m_mainCamera = NULL;
		m_loadedObjects.Clear();

		m_diffuseScene = NULL;

		m_shader_code = NULL;

		OvSingletonPool::ShutDown();
	}
public:
	void ControlMainCamera( MSG msg )
	{
		OvPoint3 curPos = m_mainCamera->GetTranslate();
		switch ( msg.message )
		{
		case WM_KEYDOWN : 
			{
				switch ( msg.wParam )
				{
				case VK_ESCAPE:
					if ( !m_exitFlag )
					{
						m_exitFlag = true;
					}
					break;
				case VK_INSERT : 
					{
						OvModelSPtr model = m_loadedObjects.GetByName("Ball");
						if ( model )
						{
							OvModelSPtr copymodel = model->Clone();
							copymodel->SetTranslate( (m_mainCamera->GetLocalLookDirection() * 5.0f) + m_mainCamera->GetTranslate() );
							m_loadedObjects.AddObject( copymodel );
 						}
					}
					break;
				}
			}
			break;
		}


	}
	void RenderSimpleTriangle()
	{

		MSG msg;
		ZeroMemory( &msg, sizeof( msg ) );
		if ( msg.message != WM_QUIT )
		{
			while ( !m_exitFlag && msg.message != WM_QUIT )
			{
				if ( PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE ) )
				{
					TranslateMessage( &msg );
					DispatchMessage( &msg );
					ControlMainCamera( msg );
				}


				{
					Update( 0, m_loadedObjects );
					Render( m_mainCamera, m_loadedObjects );
				}
			}
		}
	}
	void	Update( float elapsed, OvObjectCollector objectList  )
	{
		for ( int i = 0 ; i < objectList.Count() ; ++i )
		{
			OvObjectSPtr obj = objectList.GetByAt(i);
			if (OvRTTI_Util::IsKindOf<OvXObject>(obj))
			{
				OvXObjectSPtr xobj = obj;
				xobj->Update( elapsed );
			}
		}
	}

	void	RenderDiffuse( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		OvMatrix view_project = camera->GetViewMatrix() * camera->GetProjectMatrix();
		OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::ViewProject, view_project );

		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
		device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

		m_renderTarget.LockRenderTarget( 0, m_diffuseScene->GetSurface() );

		OvRenderer::GetInstance()->ClearTarget();
		OvRenderer::GetInstance()->BeginTarget();
		for ( int i = 0 ; i < objectList.Count() ; ++i )
		{
			OvXObjectSPtr obj = objectList.GetByAt(i);
			if (OvRTTI_Util::IsKindOf<OvModel>(obj))
			{
				OvModelSPtr model = obj;
				model->Render();
			}
		}
		OvRenderer::GetInstance()->EndTarget();
		m_renderTarget.UnlockRenderTarget();
	}
	void	Render( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		RenderDiffuse( camera, objectList );

		OvRenderer::GetInstance()->SetTexture( 0, m_diffuseScene );

		OvRenderer::GetInstance()->ClearTarget();
		OvRenderer::GetInstance()->BeginTarget();

		OvRenderer::GetInstance()->RenderUnitRect
			( m_shader_code->FindShader( "rectV", "vs_2_0" ) 
			, m_shader_code->FindShader( "rectP", "ps_2_0" ) );

		OvRenderer::GetInstance()->EndTarget();
		OvRenderer::GetInstance()->PresentTarget();

	}
};
GL_TEST_CASE_ENV( OliveLibTest, mesh_rendering )
{
	RenderSimpleTriangle();
};
