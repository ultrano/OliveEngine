
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
		store.Load( "../../resource/ovf/game_scene.xml", m_objectList);
		m_mainCamera = m_objectList.GetByName("Camera");

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
								m_exitFlag = true;
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

};
GL_TEST_CASE_ENV( Simple_Game, run )
{
	Run();
};