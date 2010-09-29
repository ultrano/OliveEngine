
#include "OvXObject.h"
#include "OvCameraController.h"
#include "OvRenderTexture.h"

GL_TEST_ENVIROMENT(OliveLibTest)
{
private:
protected:
	OvCameraSPtr m_mainCamera;
	OvObjectCollector m_loadedObjects;
	OvCameraSPtr GetMainCamera(){return m_mainCamera;};
	bool m_exitFlag;
public:
	GL_ENV_SET_UP
	{
		m_exitFlag = false;
		OvSingletonPool::StartUp();
		OvRenderer::GetInstance()->GenerateRenderer();

		OvStorage store;
		if ( ! store.Load( ("../../resource/ovf/scene_test.xml"), m_loadedObjects) )
		{
			OvMessageBox("¸ÁÇÞ¾î¿°^_^ ·Îµù ¤¤¤¤","");
			m_exitFlag = true;
		}
		m_mainCamera = m_loadedObjects.GetByName("Camera");
	};
	GL_ENV_TEAR_DOWN
	{
		m_mainCamera = NULL;
		m_loadedObjects.Clear();

		OvSingletonPool::ShutDown();
	}
public:
	void ControlMainCamera( MSG msg )
	{
		OvPoint3 curPos = GetMainCamera()->GetTranslate();
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
						RenderToTexture( GetMainCamera(), m_loadedObjects );
					}
					break;
				case VK_INSERT : 
					{

						OvModelSPtr model = m_loadedObjects.GetByName("Ball");
						if ( model )
						{
							OvModelSPtr copymodel = OvNew OvModel;
							copymodel->SetMesh( model->GetMesh() );
							copymodel->SetMaterial( model->GetMaterial() );
							copymodel->SetTranslate( (GetMainCamera()->GetLocalLookDirection() * 100.0f) + GetMainCamera()->GetTranslate() );
							copymodel->SetRotation( GetMainCamera()->GetRotation() );
							m_loadedObjects.AddObject( copymodel );
						}

					}
					break;
				case VK_END :
					{
						OvStorage store;
						store.Save( ("../../resource/ovf/scene_test2.xml"), m_loadedObjects);
					}
					break;
				case VK_HOME :
					{
						OvStorage store;
						store.Load( ("../../resource/ovf/scene_test2.xml"), m_loadedObjects);
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
					Render( GetMainCamera(), m_loadedObjects );
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

	void	Render( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		float timeCycle = GetTickCount();
		timeCycle = timeCycle / 1000.0f;

		OvMatrix view_project = camera->GetViewMatrix() * camera->GetProjectMatrix();

		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::ViewProject, view_project );
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::ViewPos, camera->GetWorldTranslate() );

		OvShaderManager::GetInstance()->SetPSConst( OvMatPSConst::Time, timeCycle);
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::Time, timeCycle);

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
		OvRenderer::GetInstance()->PresentTarget();
	}

	void RenderToTexture( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		OvTextureSPtr render_texture = CreateRenderTexture(1024,1024,1,D3DFORMAT::D3DFMT_A8B8G8R8);
		OvTextureSPtr depth_stencil = CreateDepthStencilTexture(1024,1024,1,D3DFORMAT::D3DFMT_D16);
		OvRenderTarget render_target;

		render_target.LockRenderTarget( 0, render_texture->GetSurface() );
		render_target.LockDepthStencil( depth_stencil->GetSurface() );

 		Render( camera, objectList );

		render_target.UnlockRenderTarget();
		render_target.UnlockDepthStencil();

 		SaveTexture( ( "../../resource/texture/save_test.bmp" ), render_texture, D3DXIFF_BMP);
	}
};
GL_TEST_CASE_ENV( OliveLibTest, mesh_rendering )
{
	RenderSimpleTriangle();
};
