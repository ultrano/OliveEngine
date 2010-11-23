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
	if ( OvXNode::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvXNode;
	}
	else if ( OvCamera::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvCamera;
	}
	else if ( OvModel::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvModel;
	}
	// 	else if ("OvPointLight" == typeName)
	// 	{
	// 		return OvNew OvPointLight;
	// 	}
	else if ( OvCameraController::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvCameraController;
	}
	else if ( OvFileMeshLoader::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvFileMeshLoader;
	}
	else if ( OvTextureLoader::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvTextureLoader;
	}
	else if ( OvShaderCodeLoader::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvShaderCodeLoader;
	}
	else if ( OvMaterialLoader::GetRTTI()->TypeName() == typeName)
	{
		return OvNew OvMaterialLoader;
	}
	return NULL;
}