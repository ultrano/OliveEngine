#include "OvMaterialManager.h"
#include "OvShaderConstantTable.h"
#include "OvRenderer.h"
#include "OvTransform.h"
#include <d3dx9.h>
#include <map>
#include "OvStringUtility.h"


typedef std::map<std::string,OvShaderConstInfo> tdShaderConstMappingTable;
struct OvMaterialManager::OvPimple : OvMemObject
{
	tdShaderConstMappingTable	m_mapCommonVertShaderConstTable;
};

OvMaterialManager::OvMaterialManager()
:m_pPimple(OvNew OvMaterialManager::OvPimple)
{
}
OvMaterialManager::~OvMaterialManager()
{

}
