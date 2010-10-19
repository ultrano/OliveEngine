
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
		: m_time( 0 )
		, m_radian( 0 )
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
		m_time++;
		if ( m_time < 500 )
		{
			NxVec3 nx_pos = m_actor->getGlobalPosition();
			OvPoint3 ov_pos(nx_pos.x,nx_pos.y,nx_pos.z);
			NxQuat nx_qut = m_actor->getGlobalOrientationQuat();
			OvQuaternion ov_qut(nx_qut.x,nx_qut.y,nx_qut.z,nx_qut.w);

			GetTarget()->SetTranslate( ov_pos );
			GetTarget()->SetRotation( ov_qut );
		}
		else
		{
			m_scene->releaseActor( *m_actor );
			GetTarget()->SetControlFlag(OvXObject::UPDATABLE,false);
			GetTarget()->SetControlFlag(OvXObject::VISIBLE,false);
			OvXNodeSPtr xnode = GetTarget()->GetAttachedNode();
			if ( xnode )
			{
				xnode->DettachChild( GetTarget() );
			}
		}

	}
private:
	OvPoint3 m_startpt;
	float m_time;
	float m_radian;
	NxActor * m_actor;
	NxScene * m_scene;
	OvPoint3 m_vel;
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

	OvXNodeSPtr	m_root;

	NxPhysicsSDK*	m_physicsSDK;
	NxScene*		m_scene;

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
		m_root = OvNew OvXNode;
		for ( unsigned i = 0 ; i < m_loadedObjects.Count() ; ++i )
		{
			OvObjectSPtr obj = m_loadedObjects.GetByAt(i);
			if ( OvRTTI_Util::IsKindOf<OvXObject>(obj) )
			{
				m_root->AttachChild( obj );
			}
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
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

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
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
	};
	GL_ENV_TEAR_DOWN
	{
		m_mainCamera = NULL;
		m_loadedObjects.Clear();

		m_diffuseScene = NULL;

		m_shader_code = NULL;

		m_root = NULL;

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
							(OvNew testcomponent(m_scene,m_mainCamera->GetLocalLookDirection() * (rand()%50)))->SetTarget( copymodel );
							m_root->AttachChild( copymodel );
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
					Update(  m_root );
					m_scene->simulate(1.0f/6.0f);
					Render( m_mainCamera, m_root );
					m_scene->flushStream();
					m_scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
				}
			}
		}
	}

	void	RenderDiffuse( OvCameraSPtr camera, OvXObjectSPtr xobj )
	{
		OvMatrix view_project = camera->GetViewMatrix() * camera->GetProjectMatrix();
		OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::ViewProject, view_project );

		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		device->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
		device->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );

		m_renderTarget.LockRenderTarget( 0, m_diffuseScene->GetSurface() );

		OvRenderer::GetInstance()->ClearTarget();
		OvRenderer::GetInstance()->BeginTarget();
		
		Draw( xobj );

		OvRenderer::GetInstance()->EndTarget();
		m_renderTarget.UnlockRenderTarget();
	}
	void	Render( OvCameraSPtr camera, OvXObjectSPtr xobj )
	{
		RenderDiffuse( camera, xobj );

		OvRenderer::GetInstance()->SetTexture( 0, m_diffuseScene );

		OvRenderer::GetInstance()->ClearTarget();
		OvRenderer::GetInstance()->BeginTarget();

		OvRenderer::GetInstance()->RenderUnitRect
			( m_shader_code->FindShader( "rectV", "vs_2_0" ) 
			, m_shader_code->FindShader( "rectP", "ps_2_0" ) );

		OvRenderer::GetInstance()->EndTarget();
		OvRenderer::GetInstance()->PresentTarget();

	}
	void	Update( OvXObjectSPtr xobj )
	{
		if ( xobj )
		{
			xobj->Update( 0 );
			if ( OvRTTI_Util::IsTypeOf<OvXNode>(xobj) )
			{
				OvXObjectSPtr child = NULL;
				OvXNodeSPtr xnode = xobj;
				for ( unsigned i = 0 ; child = xnode->GetChildeAt(i) ; ++i )
				{
					Update( child );
				}
			}
		}
	}
	void	Draw( OvXObjectSPtr xobj )
	{
		if ( xobj )
		{
			if ( OvRTTI_Util::IsTypeOf<OvModel>(xobj) )
			{
				OvModelSPtr model = xobj;
				model->Render();
			}
			if ( OvRTTI_Util::IsTypeOf<OvXNode>(xobj) )
			{
				OvXObjectSPtr child = NULL;
				OvXNodeSPtr xnode = xobj;
				for ( unsigned i = 0 ; child = xnode->GetChildeAt(i) ; ++i )
				{
					Draw( child );
				}
			}
		}
	}
};
GL_TEST_CASE_ENV( OliveLibTest, mesh_rendering )
{
	RenderSimpleTriangle();
};
