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
#define FACTORY_MEMBER_BEGIN() OvObject* TemporaryFactoryFunction(const std::string& typeName){ if( typeName.empty() ){ return NULL; }
#define FACTORY_MEMBER( member ) else if( member::GetRTTI()->TypeName() == typeName ){ return OvNew member(); }
#define FACTORY_MEMBER_END() return NULL;}

FACTORY_MEMBER_BEGIN()
	FACTORY_MEMBER( OvXNode )
	FACTORY_MEMBER( OvCamera )
	FACTORY_MEMBER( OvModel )
	FACTORY_MEMBER( OvCameraController )
	FACTORY_MEMBER( OvFileMeshLoader )
	FACTORY_MEMBER( OvTextureLoader )
	FACTORY_MEMBER( OvShaderCodeLoader )
	FACTORY_MEMBER( OvMaterialLoader )
FACTORY_MEMBER_END()
