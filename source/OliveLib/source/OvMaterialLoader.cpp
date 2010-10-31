#include "OvMaterialLoader.h"
#include "OvMaterial.h"
#include "tinyxml.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"
#include "OvTexture.h"
#include "OvResourceManager.h"
#include "OvShaderManager.h"
#include "OvShaderCodeIncluder.h"
#include "OvShaderCode.h"
#include <map>
using namespace std;

OvRTTI_IMPL( OvMaterialLoader );

OvResourceSPtr OvMaterialLoader::Load( const std::string& fileLocation )
{
	TiXmlDocument doc("material_doc");
	
	if ( ! doc.LoadFile( fileLocation.c_str() ) )
	{	
		return NULL;
	}
	TiXmlElement* root = doc.RootElement();

	//////////////////////////////////////////////////////////////////////////
	TiXmlElement* shader_elem = root->FirstChildElement( "shader" );

	OvShaderCodeIncluder includer;
	OvVertexShaderSPtr	vertexShader = NULL;
	OvPixelShaderSPtr	pixelShader	 = NULL;
	string shader_code;
	string entry_function;
	string complie_version;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	TiXmlElement* vertex_shader_elem = shader_elem->FirstChildElement("vertex_shader");

	shader_code		= vertex_shader_elem->GetText();
	entry_function	= vertex_shader_elem->Attribute("entry_function");
	complie_version	= vertex_shader_elem->Attribute("complie_version");

	vertexShader = OvShaderCode( shader_code ).CompileVertexShader( entry_function, complie_version );

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	TiXmlElement* pixel_shader_elem = shader_elem->FirstChildElement("pixel_shader");

	shader_code		= pixel_shader_elem->GetText();
	entry_function	= pixel_shader_elem->Attribute("entry_function");
	complie_version	= pixel_shader_elem->Attribute("complie_version");

	pixelShader = OvShaderCode( shader_code ).CompilePixelShader( entry_function, complie_version );

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	TiXmlElement* sampler_stage_elem = root->FirstChildElement( "sampler_stage" );
	std::map<unsigned int, OvTextureSPtr> stageImage;

	for ( TiXmlElement* sampler_elem = sampler_stage_elem->FirstChildElement( "sampler" )
		; NULL != sampler_elem
		; sampler_elem = sampler_elem->NextSiblingElement() )
	{
		int stage = 0;
		sampler_elem->Attribute( "stage", &stage );
		
		TiXmlElement* texture_elem = sampler_elem->FirstChildElement( "texture" );

		OvTextureSPtr image = OvResourceManager::GetInstance()->LoadResource<OvTexture>( ResDirPath( texture_elem->GetText() ) );

		stageImage[ stage ] = image;
	}

	//////////////////////////////////////////////////////////////////////////

	OvMaterialSPtr material = new OvMaterial;
	material->SetVertexShader( vertexShader );
	material->SetPixelShader( pixelShader );
	for ( int i = 0 ; i < OvMaterial::MaxStage ; ++i )
	{
		material->SetStageTexture( (OvMaterial::TextureStage)i, stageImage[i] );
	}
	return material;
}