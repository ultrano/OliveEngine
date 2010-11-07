#include "TemporaryFactoryFunction.h"
// ////////////////////// 테스트 인클루드 (물리적 구조때문에 나중에 지워줘야 한다.) /////
#include "OvCamera.h"
#include "OvXNode.h"
#include "OvModel.h"
#include "OvMaterial.h"
#include "OvCameraController.h"
#include "OvFileMeshLoader.h"
#include "OvTextureLoader.h"
#include "OvShaderCodeLoader.h"
#include "OvMaterialLoader.h"
// //////////////////////////////////////////////////////////////////////////

OvObject* TemporaryFactoryFunction(const std::string& typeName)
{
	if ("OvXNode" == typeName)
	{
		return OvNew OvXNode;
	}
	else if ("OvCamera" == typeName)
	{
		return OvNew OvCamera;
	}
	else if ("OvModel" == typeName)
	{
		return OvNew OvModel;
	}
	// 	else if ("OvPointLight" == typeName)
	// 	{
	// 		return OvNew OvPointLight;
	// 	}
	else if ("OvCameraController" == typeName)
	{
		return OvNew OvCameraController;
	}
	else if ("OvFileMeshLoader" == typeName)
	{
		return OvNew OvFileMeshLoader;
	}
	else if ("OvTextureLoader" == typeName)
	{
		return OvNew OvTextureLoader;
	}
	else if ("OvShaderCodeLoader" == typeName)
	{
		return OvNew OvShaderCodeLoader;
	}
	else if ("OvMaterialLoader" == typeName)
	{
		return OvNew OvMaterialLoader;
	}
	return NULL;
}