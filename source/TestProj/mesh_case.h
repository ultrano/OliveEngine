
#include "NxPhysics.h"

#include "include_header.h"
#include "OvXObject.h"
#include "OvCameraController.h"
#include "OvRenderTexture.h"
#include "OvShaderCodeIncluder.h"
#include "OvShaderCode.h"

class testcomponent : public OvXComponent
{
public:
	testcomponent(NxScene * scene, OvPoint3& vel )
	: m_radian( 0 )
	, m_actor( NULL )	
	, m_scene( scene )
	, m_vel( vel ){};
	virtual void SetUp() override
	{
		if(m_scene == NULL) return;	

		// Create body
		NxBodyDesc bodyDesc;
		bodyDesc.angularDamping	= 0.5f;
		bodyDesc.linearVelocity = NxVec3(m_vel.x,m_vel.y,m_vel.z);

		OvPoint3 scale = GetTarget()->GetScale();
		NxSphereShapeDesc desc;
		desc.radius = scale.x;

		NxVec3 pos(GetTarget()->GetTranslate().x,GetTarget()->GetTranslate().y,GetTarget()->GetTranslate().z);
		NxActorDesc actorDesc;
		actorDesc.shapes.pushBack(&desc);
		actorDesc.body			= &bodyDesc;
		actorDesc.density		= 10.0f;
		actorDesc.globalPose.t  = pos;
		m_actor = m_scene->createActor(actorDesc);
	}
	virtual void Update(float _fElapse) override
	{
		m_radian += (D3DX_PI/180.0f);
		//OvPoint3 dir( cosf(m_radian),0,sinf(m_radian));
		//GetTarget()->SetTranslate( m_startpt + dir * 5 );
		
		//GetTarget()->SetRotation(GetTarget()->GetRotation()*OvQuaternion().MakeQuaternion(0,1,0,(D3DX_PI/180.0f)));
		NxVec3 nx_pos = m_actor->getGlobalPosition();
		OvPoint3 ov_pos(nx_pos.x,nx_pos.y,nx_pos.z);
		NxQuat nx_qut = m_actor->getGlobalOrientationQuat();
		OvQuaternion ov_qut(nx_qut.x,nx_qut.y,nx_qut.z,nx_qut.w);

		GetTarget()->SetTranslate( ov_pos );
		GetTarget()->SetRotation( ov_qut );

	}
private:
	OvPoint3 m_startpt;
	float m_radian;
	NxActor * m_actor;
	NxScene * m_scene;
	OvPoint3 m_vel;
};

GL_TEST_ENVIROMENT(OliveLibTest)
{
private:
protected:
	OvRenderTarget m_renderTarget;
	OvTextureSPtr m_diffuseScene;
	OvTextureSPtr m_lightDepthScene;
	OvTextureSPtr m_shadowProjectedScene;
	OvTextureSPtr m_shadowAccumulatedScene;

	
	OvShaderCodeSPtr m_shader_code;


	OvCameraSPtr m_mainCamera;
	list<OvCameraSPtr> m_lights;
	OvXComponentSPtr m_cameraControler;

	OvObjectCollector m_loadedObjects;

	NxPhysicsSDK*	m_physicsSDK;
	NxScene*		m_scene;

	bool m_exitFlag;
public:
	GL_ENV_SET_UP
	{
		//////////////////////////////////////////////////////////////////////////
		NxPhysicsSDKDesc desc;
		NxSDKCreateError errorCode = NXCE_NO_ERROR;
		m_physicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION);
		m_physicsSDK->setParameter(NX_SKIN_WIDTH, 0.05f);

		// Create a scene
		NxSceneDesc sceneDesc;
		sceneDesc.gravity				= NxVec3(0.0f, -9.81f, 0.0f);
		m_scene = m_physicsSDK->createScene(sceneDesc);
		

		// Set default material
		NxMaterial* defaultMaterial = m_scene->getMaterialFromIndex(0);
		defaultMaterial->setRestitution(0.0f);
		defaultMaterial->setStaticFriction(0.5f);
		defaultMaterial->setDynamicFriction(0.5f);

		// Create ground plane
		NxPlaneShapeDesc planeDesc;
		NxActorDesc actorDesc;
		actorDesc.shapes.pushBack(&planeDesc);
		m_scene->createActor(actorDesc);
		////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
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

		OvObjectCollector components;
		m_mainCamera->GetComponents( components );
		m_cameraControler = components.GetByAt(0);

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		m_diffuseScene = CreateRenderTexture( 800, 600, 1, D3DFMT_A8B8G8R8 );
		m_lightDepthScene = CreateRenderTexture( 512, 512, 1, D3DFMT_R32F );
		m_shadowProjectedScene = CreateRenderTexture( 800, 600, 1, D3DFMT_A8B8G8R8 );
		m_shadowAccumulatedScene = CreateRenderTexture( 800, 600, 1, D3DFMT_A8B8G8R8 );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		m_shader_code = OvResourceManager::GetInstance()->LoadResource<OvShaderCode>( ResDirPath("shader/test.shacode") );

		m_shader_code->CompileVertexShader( "v_spot_shadow", "vs_2_0" );
		m_shader_code->CompilePixelShader( "p_spot_shadow", "ps_2_0" );

		m_shader_code->CompileVertexShader( "rectV", "vs_2_0" );
		m_shader_code->CompilePixelShader( "rectP", "ps_2_0" );

		m_shader_code->CompileVertexShader( "depthV", "vs_2_0" );
		m_shader_code->CompilePixelShader( "depthP", "ps_2_0" );

		m_shader_code->CompileVertexShader( "accumulateV", "vs_2_0" );
		m_shader_code->CompilePixelShader( "accumulateP", "ps_2_0" );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	};
	GL_ENV_TEAR_DOWN
	{
		m_mainCamera = NULL;
		m_lights.clear();
		m_cameraControler = NULL;
		m_loadedObjects.Clear();

		m_diffuseScene = NULL;
		m_lightDepthScene = NULL;
		m_shadowProjectedScene = NULL;
		m_shadowAccumulatedScene = NULL;

		m_shader_code = NULL;

		m_physicsSDK->releaseScene( *m_scene );
		NxReleasePhysicsSDK( m_physicsSDK );
		m_physicsSDK = NULL;

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
							OvCameraSPtr light = OvNew OvCamera;
							light->SetTranslate( m_mainCamera->GetTranslate() );
							light->SetRotation( m_mainCamera->GetRotation() );
							light->SetFOV( m_mainCamera->GetFOV() );
							light->Update(0);
							light->SetFarClip(800);
							m_loadedObjects.AddObject( light );
							m_lights.push_back( light );
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
							OvModelSPtr copymodel = OvNew OvModel;
							copymodel->SetMesh( model->GetMesh() );
							copymodel->SetMaterial( model->GetMaterial() );
							copymodel->SetTranslate( (m_mainCamera->GetLocalLookDirection() * 5.0f) + m_mainCamera->GetTranslate() );
							copymodel->SetScale( model->GetScale() );
							(OvNew testcomponent(m_scene,m_mainCamera->GetLocalLookDirection() * 15))->SetTarget( copymodel );
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
		m_scene->simulate(1.0f/6.0f);
		for ( int i = 0 ; i < objectList.Count() ; ++i )
		{
			OvObjectSPtr obj = objectList.GetByAt(i);
			if (OvRTTI_Util::IsKindOf<OvXObject>(obj))
			{
				OvXObjectSPtr xobj = obj;
				xobj->Update( elapsed );
			}
		}
		m_scene->flushStream();
		m_scene->fetchResults(NX_RIGID_BODY_FINISHED, true);

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

		OvRenderer::GetInstance()->SetVertexShader( m_shader_code->FindShader( "depthV", "vs_2_0" ) );
		OvRenderer::GetInstance()->SetPixelShader( m_shader_code->FindShader( "depthP", "ps_2_0" ) );

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

		OvRenderer::GetInstance()->RenderUnitRect();


		OvRenderer::GetInstance()->EndTarget();

	}
	void	RenderSpotLightDepth( OvCameraSPtr camera, OvCameraSPtr light,OvObjectCollector objectList )
	{
		OvMatrix light_project = light->GetViewMatrix() * light->GetProjectMatrix();
		m_renderTarget.LockRenderTarget( 0, m_lightDepthScene->GetSurface() );
		
		RenderDepth( light_project, objectList );

		m_renderTarget.UnlockRenderTarget();

	}
	void	RenderShadowProjected( OvCameraSPtr camera, OvCameraSPtr light,OvObjectCollector objectList )
	{
		static OvMatrix bias = OvMatrix().Scale( 0.5f, -0.5f, 0 ) * OvMatrix().Translate( 0.5f, 0.5f, 0 );
		OvMatrix light_project = light->GetViewMatrix() * light->GetProjectMatrix();
		OvMatrix view_project = camera->GetViewMatrix() * camera->GetProjectMatrix();
		OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::ViewProject, view_project );

		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );
		device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );

		OvRenderer::GetInstance()->SetVertexShader( m_shader_code->FindShader( "v_spot_shadow", "vs_2_0" ) );
		OvRenderer::GetInstance()->SetPixelShader( m_shader_code->FindShader( "p_spot_shadow", "ps_2_0" ) );
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
	void	RenderShadowAccumulated()
	{
		OvRenderer::GetInstance()->SetVertexShader( m_shader_code->FindShader( "accumulateV", "vs_2_0" ) );
		OvRenderer::GetInstance()->SetPixelShader( m_shader_code->FindShader( "accumulateP", "ps_2_0" ) );
		OvRenderer::GetInstance()->SetTexture( 0, m_shadowProjectedScene );

		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		device->SetRenderState( D3DRS_ALPHABLENDENABLE, true);
		device->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
		device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
		device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

		m_renderTarget.LockRenderTarget( 0, m_shadowAccumulatedScene->GetSurface() );

		OvRenderer::GetInstance()->BeginTarget();

		OvRenderer::GetInstance()->RenderUnitRect();

		OvRenderer::GetInstance()->EndTarget();

		m_renderTarget.UnlockRenderTarget();
		device->SetRenderState( D3DRS_ALPHABLENDENABLE, false);

	}
	void	Render( OvCameraSPtr camera, OvObjectCollector objectList )
	{
		RenderDiffuse( camera, objectList );
		m_renderTarget.LockRenderTarget( 0, m_shadowAccumulatedScene->GetSurface() );
		OvRenderer::GetInstance()->ClearTarget();
		m_renderTarget.UnlockRenderTarget();
		for each ( OvCameraSPtr light in m_lights )
		{
			RenderSpotLightDepth( camera, light, objectList );
			RenderShadowProjected( camera, light, objectList );
			RenderShadowAccumulated();
		}

		OvRenderer::GetInstance()->SetVertexShader( m_shader_code->FindShader( "rectV", "vs_2_0" ) );
		OvRenderer::GetInstance()->SetPixelShader( m_shader_code->FindShader( "rectP", "ps_2_0" ) );
		OvRenderer::GetInstance()->SetTexture( 0, m_diffuseScene );
		OvRenderer::GetInstance()->SetTexture( 1, m_shadowAccumulatedScene );

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
