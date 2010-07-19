
GL_ENVIROMENT(OliveLibTest)
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
		store.Load( "../../resource/ovf/scene_test.xml", m_loadedObjects);

		m_mainCamera = m_loadedObjects.GetByName("Camera");
		m_mainCamera->Update(0);

		m_mainCamera->RegisterExtraProperty("accumPt", OliveValue::ValueFactory("Point2") );

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
				case VK_ESCAPE:
					m_exitFlag = true;
					break;
				case VK_INSERT : 
					{

						OvModelSPtr model = m_loadedObjects.GetByName("Model");
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
						store.Save( "../../resource/ovf/scene_test2.xml", m_loadedObjects);
					}
					break;
				case VK_HOME :
					{
						OvStorage store;
						store.Load( "../../resource/ovf/scene_test2.xml", m_loadedObjects);
					}
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

		for (int i=0;i<m_loadedObjects.Count();++i)
		{
			OvObjectSPtr obj = m_loadedObjects.GetByAt(i);
			if ( OvRTTI_Util::IsKindOf<OvXObject>(obj) )
			{
				OvXObjectSPtr xobj = obj;
				xobj->Update(0);
			}
		}
		GetMainCamera()->Update(0);
		OvMatrix view_project = GetMainCamera()->GetViewMatrix() * GetMainCamera()->GetProjectMatrix();
		OvShaderManager::GetInstance()->SetPSConst( OvMatPSConst::Time, timeCycle);
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::Time, timeCycle);
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::ViewProject, view_project );
		OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::ViewPos, GetMainCamera()->GetWorldTranslate() );

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
					UpdateAndCommit();

					OvRenderer::GetInstance()->ClearTarget();
					OvRenderer::GetInstance()->BeginTarget();
					for (int i=0;i<m_loadedObjects.Count();++i)
					{
						OvXObjectSPtr obj = m_loadedObjects.GetByAt(i);
						if (OvRTTI_Util::IsKindOf<OvModel>(obj))
						{
							OvModelSPtr model = obj;
							model->Render();
						}
					}
					OvRenderer::GetInstance()->EndTarget();
					OvRenderer::GetInstance()->PresentTarget();
				}
			}
		}
	}
};

// GL_TEST_CASE_ENV( OliveLibTest, shader )
// {
// 	CreateShader();
// }

GL_TEST_CASE_ENV( OliveLibTest, mesh_rendering )
{
	RenderSimpleTriangle();
};
