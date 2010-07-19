#include "OvStorage.h"
#include "OvXNode.h"
#include "OvCamera.h"
#include "OvModel.h"
#include "OvPointLight.h"

GL_TEST_CASE_FUNC( streaming )
{
	OvSingletonPool::StartUp();

	{

		OvObjectCollector streaming;
		streaming.AddObject( OvNew OvCamera );

		OvStorage store;
		store.Save( "../../export/store.xml", streaming);
		store.ExportObjectStructure( "../../export/object_structure.xml", OvObject::GetRTTI() );
		store.ExportObjectStructure( "../../export/xobject_structure.xml", OvXObject::GetRTTI() );
		store.ExportObjectStructure( "../../export/node_structure.xml", OvXNode::GetRTTI() );
		store.ExportObjectStructure( "../../export/camera_structure.xml", OvCamera::GetRTTI() );
		store.ExportObjectStructure( "../../export/model_structure.xml", OvModel::GetRTTI() );
		store.ExportObjectStructure( "../../export/pointlight_structure.xml", OvPointLight::GetRTTI() );

	}
	
	OvSingletonPool::ShutDown();

}
GL_TEST_CASE_FUNC( extra_prop_streaming )
{
	OvSingletonPool::StartUp();

	{
		OvStorage store;
		OvObjectCollector streaming;
		OvXNodeSPtr node = OvNew OvXNode;

		for ( int i = 0 ; i < 5 ; ++i)
		{
			OliveValue::Integer index(i);
			node->RegisterExtraProperty( "test"+index.GetValue(), OvNew OliveValue::Integer( i ) );
		}

		streaming.AddObject( node );
		store.Save( "../../export/extra_prop_test.xml", streaming);
		streaming.Clear();
		store.Load( "../../export/extra_prop_test.xml", streaming);
		store.Save( "../../export/extra_prop_test2.xml", streaming);
	}

	OvSingletonPool::ShutDown();
}
GL_TEST_CASE_FUNC( camera_save_case )
{
	OvSingletonPool::StartUp();

	{
		OvStorage store;
		OvObjectCollector streaming;
		OvCameraSPtr camera = OvNew OvCamera;
		OvXNodeSPtr node = OvNew OvXNode;
		camera->SetLookTarget( node );
		streaming.AddObject( camera );
		store.Save( "../../export/camera_save_text.xml", streaming);
	}

	OvSingletonPool::ShutDown();
}

GL_TEST_CASE_FUNC( model_save_case )
{
	OvSingletonPool::StartUp();

	{
		size_t siz = sizeof(OvMeshSPtr);
		OvRenderer::GetInstance()->GenerateRenderer();
		OvStorage store;
		OvObjectCollector streaming;


		OvFileMeshLoader meshLoader;
		OvTextureLoader texLoader;

		OvVertexShaderSPtr vshader = OvResourceManager::GetInstance()->LoadResource<OvVertexShader>( "../../OliveGLib/shader/testV.fx" );
		OvPixelShaderSPtr pshader = OvResourceManager::GetInstance()->LoadResource<OvPixelShader>( "../../OliveGLib/shader/testP.fx" );
		OvMeshSPtr testMesh = OvResourceManager::GetInstance()->LoadResource<OvMesh>("../../export/test.msf0");
		OvTextureSPtr diffuce = OvResourceManager::GetInstance()->LoadResource<OvTexture>( "../../export/test.jpg" );
		OvTextureSPtr normal = OvResourceManager::GetInstance()->LoadResource<OvTexture>( "../../export/normal.jpg" );

		OvMaterialSPtr material = OvNew OvMaterial;
		material->SetVertexShader( vshader );
		material->SetPixelShader( pshader );
		material->SetStageTexture( OvMaterial::Stage0, diffuce);
		material->SetStageTexture( OvMaterial::Stage1, normal);

		OvModelSPtr model = OvNew OvModel;
		model->SetMesh( testMesh );
		model->SetMaterial( material );

		streaming.AddObject( model );
		store.Save( "../../export/model_save.xml", streaming);
		store.Load( "../../export/model_save.xml", streaming);

	}

	OvSingletonPool::ShutDown();

}