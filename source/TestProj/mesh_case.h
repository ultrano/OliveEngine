
#include "OvXObject.h"
#include "OvCameraController.h"
#include "OvRenderTexture.h"
#include "OvShaderCodeIncluder.h"
#include "OvShaderCode.h"

GL_TEST_ENVIROMENT(OliveLibTest)
{
private:
protected:
	OvRenderTarget m_renderTarget;
	OvTextureSPtr m_diffuseScene;
	OvTextureSPtr m_lightDepthScene;
	OvTextureSPtr m_shadowProjectedScene;
	OvCubeTextureSPtr m_pointLightDepthScene;

	
	OvShaderCodeSPtr m_depthCode;
	OvShaderCodeSPtr m_shadowProjCode;
	OvShaderCodeSPtr m_rectCode;

	OvResourceTicketSPtr m_rectVSTicket;
	OvResourceTicketSPtr m_rectPSTicket;

	OvCameraSPtr m_mainCamera;
	OvCameraSPtr m_lightCamera;
	OvXComponentSPtr m_cameraControler;

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
		m_lightCamera = m_loadedObjects.GetByName("Light");
		m_lightCamera->SetFOV( D3DX_PI/2.0f );

		OvObjectCollector components;
		m_mainCamera->GetComponents( components );
		m_cameraControler = components.GetByAt(0);

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		m_diffuseScene = CreateRenderTexture( 800, 600, 1, D3DFMT_A8B8G8R8 );
		m_lightDepthScene = CreateRenderTexture( 512, 512, 1, D3DFMT_R32F );
		m_shadowProjectedScene = CreateRenderTexture( 800, 600, 1, D3DFMT_A8B8G8R8 );
		m_pointLightDepthScene = CreateRenderCubeTexture( 512, 1, D3DFMT_R32F);

		OvShaderCodeSPtr shader_code = NULL;

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		m_depthCode = OvResourceManager::GetInstance()->LoadResource<OvShaderCode>( ResDirPath("shader/depth.shacode") );
		m_depthCode->CompileVertexShader( "Vmain", "vs_2_0" );
		m_depthCode->CompilePixelShader( "Pmain", "ps_2_0" );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		m_shadowProjCode = OvResourceManager::GetInstance()->LoadResource<OvShaderCode>( ResDirPath("shader/shadow_project.shacode") );
		m_shadowProjCode->CompileVertexShader( "Vmain", "vs_2_0" );
		m_shadowProjCode->CompilePixelShader( "Pmain", "ps_2_0" );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		m_rectCode = OvResourceManager::GetInstance()->LoadResource<OvShaderCode>( ResDirPath("shader/rect.shacode") );
		m_rectCode->CompileVertexShader( "Vmain", "vs_2_0" );
		m_rectCode->CompilePixelShader( "Pmain", "ps_2_0" );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	};
	GL_ENV_TEAR_DOWN
	{
		m_lightCamera = NULL;
		m_mainCamera = NULL;
		m_cameraControler = NULL;
		m_loadedObjects.Clear();

		m_diffuseScene = NULL;
		m_lightDepthScene = NULL;
		m_shadowProjectedScene = NULL;
		m_pointLightDepthScene = NULL;

		m_depthCode = NULL;
		m_shadowProjCode = NULL;
		m_rectCode = NULL;

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
				case VK_SPACE:
					{
						if ( m_cameraControler->GetTarget() == m_mainCamera )
						{
							m_cameraControler->SetTarget( m_lightCamera );
						}
						else if ( m_cameraControler->GetTarget() == m_lightCamera )
						{
							m_cameraControler->SetTarget( m_mainCamera );
						}
					}
					break;
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
							OvResourceManager::GetInstance()->ReloadResourceAll();
							OvModelSPtr copymodel = OvNew OvModel;
							copymodel->SetMesh( model->GetMesh() );
							copymodel->SetMaterial( model->GetMaterial() );
							copymodel->SetTranslate( (m_mainCamera->GetLocalLookDirection() * 100.0f) + m_mainCamera->GetTranslate() );
							copymodel->SetRotation( m_mainCamera->GetRotation() );
							m_loadedObjects.AddObject( copymodel );
 						}

					}
					break;
				case VK_END :
					{
						OvStorage store;
						store.Save( ResDirPath("ovf/scene_test2.xml"), m_loadedObjects);
					}
					break;
				case VK_HOME :
					{
						OvStorage store;
						store.Load( ResDirPath("ovf/scene_test2.xml"), m_loadedObjects);
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

	void	RenderDepth( const OvMatrix& view_project, OvObjectCollector objectList )
	{
		OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::ViewProject, view_project );

		OvRenderer::GetInstance()->SetVertexShader( m_depthCode->FindShader( "Vmain", "vs_2_0" ) );
		OvRenderer::GetInstance()->SetPixelShader( m_depthCode->FindShader( "Pmain", "ps_2_0" ) );


		OvRenderer::GetInstance()->ClearTarget();
		OvRenderer::GetInstance()->BeginTarget();
		for ( int i = 0 ; i < objectList.Count() ; ++i )
		{
			OvXObjectSPtr obj = objectList.GetByAt(i);
			if (OvRTTI_Util::IsKindOf<OvModel>(obj))
			{
				OvModelSPtr model = obj;
				model->RenderWithoutMaterial();
			}
		}
		OvRenderer::GetInstance()->EndTarget();

	}
	void	RenderSpotLightDepth( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		OvMatrix light_project = m_lightCamera->GetViewMatrix() * m_lightCamera->GetProjectMatrix();
		m_renderTarget.LockRenderTarget( 0, m_lightDepthScene->GetSurface() );
		
		RenderDepth( light_project, objectList );

		m_renderTarget.UnlockRenderTarget();

	}
	void	RenderShadowProjected( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		static OvMatrix bias = OvMatrix().Scale( 0.5f, -0.5f, 0 ) * OvMatrix().Translate( 0.5f, 0.5f, 0 );
		OvMatrix light_project = m_lightCamera->GetViewMatrix() * m_lightCamera->GetProjectMatrix();
		OvMatrix view_project = camera->GetViewMatrix() * camera->GetProjectMatrix();
		OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::ViewProject, view_project );

		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );
		device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );


		OvRenderer::GetInstance()->SetVertexShader( m_shadowProjCode->FindShader( "Vmain", "vs_2_0" ) );
		OvRenderer::GetInstance()->SetPixelShader( m_shadowProjCode->FindShader( "Pmain", "ps_2_0" ) );
		OvRenderer::GetInstance()->SetTexture( 0, m_lightDepthScene );

		m_renderTarget.LockRenderTarget( 0, m_shadowProjectedScene->GetSurface() );

		OvRenderer::GetInstance()->ClearTarget();
		OvRenderer::GetInstance()->BeginTarget();
		for ( int i = 0 ; i < objectList.Count() ; ++i )
		{
			OvXObjectSPtr obj = objectList.GetByAt(i);
			if (OvRTTI_Util::IsKindOf<OvModel>(obj))
			{
				OvModelSPtr model = obj;

				OvMatrix world_light_project = model->GetWorldMatrix() * light_project;
				OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::WorldLightProject, world_light_project );
				OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::WorldLightProjectBias, world_light_project * bias );
				model->RenderWithoutMaterial();
			}
		}
		OvRenderer::GetInstance()->EndTarget();
		m_renderTarget.UnlockRenderTarget();
	}
	void	Render( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		RenderDiffuse( camera, objectList );
		RenderSpotLightDepth( camera, objectList );
		RenderShadowProjected( camera, objectList );

		OvRenderer::GetInstance()->SetVertexShader( m_rectCode->FindShader( "Vmain", "vs_2_0" ) );
		OvRenderer::GetInstance()->SetPixelShader( m_rectCode->FindShader( "Pmain", "ps_2_0" ) );
		OvRenderer::GetInstance()->SetTexture( 0, m_diffuseScene );
		OvRenderer::GetInstance()->SetTexture( 1, m_shadowProjectedScene );

		OvRenderer::GetInstance()->ClearTarget();
		OvRenderer::GetInstance()->BeginTarget();
		OvRenderer::GetInstance()->RenderUnitRect();
		OvRenderer::GetInstance()->EndTarget();
		OvRenderer::GetInstance()->PresentTarget();

	}
};
GL_TEST_CASE_ENV( OliveLibTest, mesh_rendering )
{
	RenderSimpleTriangle();
};
