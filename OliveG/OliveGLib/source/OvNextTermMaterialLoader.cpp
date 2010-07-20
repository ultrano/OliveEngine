#include "OvNextTermMaterialLoader.h"
#include "tinyxml.h"
#include "OvShaderManager.h"
#include "OvShaderCodeIncluder.h"

OvResourceSPtr OvNextTermMaterialLoader::Load( const std::string& fileLocation )
{
	TiXmlDocument doc("material_doc");
	
	doc.LoadFile( fileLocation.c_str() );
	
	TiXmlElement* root = doc.RootElement();
	TiXmlElement* vertex_shader = root->FirstChildElement("pixel_shader");

	string vertex_shader_code = vertex_shader->GetText();
	string entry_function	= vertex_shader->Attribute("entry_function");
	string complie_version	= vertex_shader->Attribute("complie_version");

	OvShaderCodeIncluder includer("../../OliveGLib/shader");
	LPDIRECT3DPIXELSHADER9 directShader = OvShaderManager::GetInstance()->CreatePixelShaderFromCode
		( vertex_shader_code
		, entry_function
		, complie_version
		, &includer );

	return false;
}