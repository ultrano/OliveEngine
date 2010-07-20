#include "OvNextTermMaterialLoader.h"

GL_TEST_CASE_FUNC( next_term_material_load_test )
{
	OvSingletonPool::StartUp();

	{
		OvRenderer::GetInstance()->GenerateRenderer();

		OvNextTermMaterialLoader loader;
		loader.Load("../../resource/material/test.mat");

	}

	OvSingletonPool::ShutDown();
}