
#include "NxPhysics.h"
#include "lua_system.h"
#include "include_header.h"
#include "OvXObject.h"
#include "OvCameraController.h"
#include "OvRenderTarget.h"
#include "OvShaderCodeIncluder.h"
#include "OvShaderCode.h"
#include "OxCameraController.h"
#include "OxBoxMovement.h"
#include "OvInputManager.h"
#include "OxTestPhysx.h"
#include "OliveDevice.h"
#include "OvTextDrawer.h"

// 테스트 환경 구축
GL_TEST_ENVIROMENT( OliveLibTest )
{
private:
protected:
	OvTextureSPtr m_diffuseScene;
	
	OvShaderCodeSPtr m_shader_code;

	OvCameraSPtr m_mainCamera;
	OvObjectCollector m_loadedObjects;

	OvXNodeSPtr	m_root;

	OxTestPhysx	m_physx;

	OvTextDrawerSPtr m_text;

	OvUInt m_draw_obj_count;

public:
	GL_ENV_SET_UP
	{

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		OliveDevice::EngineOn();

		OvStorage store;
		OvAssert( store.Load( AbsolutePath("ovf/scene_test.xml"), m_loadedObjects) );
		m_root = OvNew OvXNode;
		for ( unsigned i = 0 ; i < m_loadedObjects.Count() ; ++i )
		{
			OvObjectSPtr obj = m_loadedObjects.GetByAt(i);
			if ( OvIsKindOf<OvXObject>(obj) )
			{
				m_root->AttachChild( obj );
			}
		}
		m_mainCamera = m_loadedObjects.GetByName("Camera");
		m_mainCamera->RemoveComponent( m_mainCamera->GetFirstComponent<OvCameraController>() );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		m_diffuseScene = OvRenderer::GetInstance()->CreateRenderTexture( WindowWidth, WindowHeight );

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		m_shader_code = OvResourceManager::GetInstance()->LoadResource<OvShaderCode>( AbsolutePath("shader/test.shacode") );

		m_shader_code->CompileVertexShader( "rectV", "vs_2_0" );
		m_shader_code->CompilePixelShader( "rectP", "ps_2_0" );
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		m_text = OvNew OvTextDrawer;
		m_text->BuildFont( 16, 8, 1 );

		(OvNew OxCameraController( m_physx.GetScene() ))->SetTarget( m_mainCamera );
		m_draw_obj_count = 0;
	};
	GL_ENV_TEAR_DOWN
	{
		m_root = NULL;
		m_mainCamera = NULL;
		m_loadedObjects.Clear();

		m_diffuseScene = NULL;

		m_shader_code = NULL;

		m_text = NULL;

		OliveDevice::EngineOff();

	}
public:
	void Run()
	{
		OvInputManager* input = OvInputManager::GetInstance();
		while ( OliveDevice::Run() && !input->IsStateOfKey( DIK_ESCAPE, PRESSED ) )
		{
			Control();
			Update(  m_root );
			m_physx.GetScene()->simulate(1.0f/6.0f);
			Render( m_mainCamera, m_root );
			m_physx.GetScene()->flushStream();
			m_physx.GetScene()->fetchResults(NX_RIGID_BODY_FINISHED, true);
		}
	}

	void Control()
	{
		OvInputManager* input = OvInputManager::GetInstance();
		if ( input->IsStateOfMouse( L_BUTTON, PRESSED | PRESSING ) )
		{
			OvModelSPtr model = m_loadedObjects.GetByName("Ball");
			if ( model )
			{
				OvModelSPtr copymodel = model->Clone();
				copymodel->SetTranslate( (m_mainCamera->GetLocalLookDirection() * 20.0f) + m_mainCamera->GetTranslate() );
				copymodel->SetRotation( m_mainCamera->GetRotation() );
				(OvNew OxBoxMovement(m_physx.GetScene(),m_mainCamera->GetLocalLookDirection() ))->SetTarget( copymodel );
				m_root->AttachChild( copymodel );
			}
		}
		if ( input->IsStateOfKey( DIK_I, PRESSED ) )
		{
			OvObjectCollector savecollector;
			savecollector.AddObject(m_root);
			OvStorage store;
			OvAssert( store.Save( AbsolutePath("ovf/scene_test.xml"), savecollector) );
		}
	}

	void	RenderDiffuse( OvCameraSPtr camera, OvXObjectSPtr xobj )
	{
		OvRenderer* renderer = OvRenderer::GetInstance();
		OvShaderManager* shader = OvShaderManager::GetInstance();

		OvMatrix view_project = camera->GetViewMatrix() * camera->GetProjectMatrix();
		shader->SetVSConst( OvVShaderConst::ViewProject, view_project );

		renderer->SetRenderTarget( m_diffuseScene, true, true, OvColor( 255,0,255,255 ));
		
		Draw( xobj );

		renderer->SetRenderTarget( NULL );

	}
	void	Render( OvCameraSPtr camera, OvXObjectSPtr xobj )
	{
		OvRenderer* renderer = OvRenderer::GetInstance();

		renderer->BeginFrame();

		m_draw_obj_count = 0;
		RenderDiffuse( camera, xobj );
		OvPoint3 pt = camera->GetWorldTranslate();
		OvUInt objcount = m_draw_obj_count;
		m_text->DrawToTexture( m_diffuseScene, Ov::ToString(pt).c_str(), OvIRect(0,10,50,50), DT_NOCLIP, OvColor(255,0,0,0) );
		m_text->DrawToTexture( m_diffuseScene, Ov::ToString(objcount).c_str(), OvIRect(0,30,50,50), DT_NOCLIP, OvColor(255,0,0,0) );
		renderer->SetTexture( 0, m_diffuseScene );

		renderer->RenderUnitRect
			( m_shader_code->FindShader( "rectV", "vs_2_0" ) 
			, m_shader_code->FindShader( "rectP", "ps_2_0" ) );


		renderer->EndFrame();
		renderer->PresentFrame();

	}

	// 재귀호출
	void	Update( OvXObjectSPtr xobj )
	{
		if ( xobj )
		{
			xobj->Update( 0 );
			if ( OvIsTypeOf<OvXNode>(xobj) )
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

	// 재귀호출
	void	Draw( OvXObjectSPtr xobj )
	{
		if ( xobj )
		{
			if ( OvIsTypeOf<OvModel>(xobj) )
			{
				OvModelSPtr model = xobj;
				model->Render();
				++m_draw_obj_count;
			}

			if ( OvIsTypeOf<OvXNode>(xobj) )
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

// "OliveLibTest" 테스트 환경에서 "physx_test" 테스트
GL_TEST_CASE_ENV( OliveLibTest, physx_test )
{
	Run();
};
