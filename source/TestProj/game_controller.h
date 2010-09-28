
#include "GMPhysics.h"

GL_TEST_ENVIROMENT( Simple_Game )
{
	bool m_exitFlag;
	OvCameraSPtr m_mainCamera;
	OvObjectCollector m_objectList;
	GL_ENV_SET_UP
	{
		m_exitFlag = false;
		OvSingletonPool::StartUp();
		OvRenderer::GetInstance()->GenerateRenderer();

		OvStorage store;

		store.Load( ( "../../resource/ovf/game_scene.xml" ), m_objectList);
		m_mainCamera = m_objectList.GetByName("Camera");

		OvXObjectSPtr ball = m_objectList.GetByName("Ball");
		if ( ball )
		{
			GMPhysicsSPtr simple_physics = OvNew GMPhysics;
			simple_physics->SetTarget( ball );
		}
	}

	GL_ENV_TEAR_DOWN
	{
		m_objectList.Clear();
		m_mainCamera = NULL;
		OvSingletonPool::ShutDown();
	}

	OvCameraSPtr GetMainCamera(){return m_mainCamera;};
public:
	void	Run()
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
					switch ( msg.message )
					{
					case WM_KEYDOWN : 
						{
							switch ( msg.wParam )
							{
							case VK_ESCAPE:
								if ( m_exitFlag == false)
								{
									m_exitFlag = true;
									RenderToTexture( GetMainCamera(), m_objectList );
								}
								break;
							case VK_INSERT:
								OvXObjectSPtr ball = m_objectList.GetByName("Ball");
								OliveValue::Point3* velocity = ball->FindExtraProperty<OliveValue::Point3>( "velocity" );
								velocity->SetPoint3( velocity->GetPoint3() + OvPoint3(0.1f,0,0) );
								break;
							}
						}
					}
				}

				{
					Update( 0, m_objectList );
					Render( GetMainCamera(), m_objectList );
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
		OvRenderTargetSPtr render_target = CreateRenderTexture(800,600,1,D3DFORMAT::D3DFMT_A16B16G16R16);
		render_target->Lock();
		Render( camera, objectList );
		render_target->Unlock();
		SaveTexture( ( "../../resource/texture/save_test.bmp" ), render_target, D3DXIFF_BMP);
	}

};
GL_TEST_CASE_ENV( Simple_Game, run )
{
	Run();
};