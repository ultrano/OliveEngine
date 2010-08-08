#include "OvStorage.h"
#include "OvXNode.h"
#include "OvCamera.h"
#include "OvModel.h"
#include "OvPointLight.h"

GL_TEST_CASE_FUNC( camera_save_case )
{
	OvSingletonPool::StartUp();
	OvRenderer::GetInstance()->GenerateRenderer();

	{
		OvObjectCollector loadedObjects;
		OvStorage store;
		store.Load( "../../resource/ovf/scene_test.xml", loadedObjects );
		OvXObjectSPtr object = NULL;
		object = loadedObjects.GetByAt(0);
		object->SetName("Model");
		object = loadedObjects.GetByAt(1);
		object->SetName("Camera");
		store.Save( "../../resource/ovf/scene_test.xml", loadedObjects );
	}

	OvSingletonPool::ShutDown();
}