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
#include "OliveValue.h"
#include "OvDataStream.h"
#include <map>
using namespace std;

OvRTTI_IMPL( OvMaterialLoader );

struct SStateTypeTable : OvMemObject
{
	SStateTypeTable()
	{
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		state_type_table["addressu"] 		= D3DSAMP_ADDRESSU;
		state_type_table["addressv"] 		= D3DSAMP_ADDRESSV;
		state_type_table["addressw"] 		= D3DSAMP_ADDRESSW;
		state_type_table["bordercolor"]		= D3DSAMP_BORDERCOLOR;
		state_type_table["magfilter"] 		= D3DSAMP_MAGFILTER;
		state_type_table["minfilter"] 		= D3DSAMP_MINFILTER;
		state_type_table["mipfilter"] 		= D3DSAMP_MIPFILTER;
		state_type_table["mipmaplodbias"]	= D3DSAMP_MIPMAPLODBIAS;
		state_type_table["maxmiplevel"]		= D3DSAMP_MAXMIPLEVEL;
		state_type_table["maxanisotropy"]	= D3DSAMP_MAXANISOTROPY;
		state_type_table["srgbtexture"]		= D3DSAMP_SRGBTEXTURE;
		state_type_table["elementindex"]	= D3DSAMP_ELEMENTINDEX;
		state_type_table["dmapoffset"]		= D3DSAMP_DMAPOFFSET;

	};
	std::map<std::string, DWORD> state_type_table;
};

struct SStateValueTable : OvMemObject
{

	SStateValueTable()
	{
		//////////////////////////////////////////////////////////////////////////

		state_value_table["wrap"]			=	D3DTADDRESS_WRAP      ;
		state_value_table["mirror"]			=	D3DTADDRESS_MIRROR    ;
		state_value_table["clamp"]			=	D3DTADDRESS_CLAMP     ;
		state_value_table["border"]			=	D3DTADDRESS_BORDER    ;
		state_value_table["mirroronce"]		=	D3DTADDRESS_MIRRORONCE;

		//////////////////////////////////////////////////////////////////////////

		state_value_table["none"]			=	D3DTEXF_NONE          ;
		state_value_table["point"]			=	D3DTEXF_POINT         ;
		state_value_table["linear"]			=	D3DTEXF_LINEAR        ;
		state_value_table["anisotropic"]	=	D3DTEXF_ANISOTROPIC   ;
		state_value_table["pyramidalquad"]	=	D3DTEXF_PYRAMIDALQUAD ;
		state_value_table["gaussianquad"]	=	D3DTEXF_GAUSSIANQUAD  ;

		//////////////////////////////////////////////////////////////////////////
		

	};
	std::map<std::string, DWORD> state_value_table;
};

DWORD StringToStateType( const char* type )
{
	static SStateTypeTable table;
	return table.state_type_table[ type ];
}
DWORD StringToStateValue( const char* value )
{
	static SStateValueTable tavle;
	return tavle.state_value_table[ value ];
}

OvResourceSPtr OvMaterialLoader::Load( OvDataStream& stream )
{
	TiXmlDocument doc("material_doc");
	
	if ( ! doc.Parse( stream.Ptr() ) )
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

	OvShaderCode vertex_code( shader_code );
	vertexShader = vertex_code.CompileVertexShader( entry_function, complie_version );

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	TiXmlElement* pixel_shader_elem = shader_elem->FirstChildElement("pixel_shader");

	shader_code		= pixel_shader_elem->GetText();
	entry_function	= pixel_shader_elem->Attribute("entry_function");
	complie_version	= pixel_shader_elem->Attribute("complie_version");

	OvShaderCode pixel_code( shader_code );
	pixelShader = pixel_code.CompilePixelShader( entry_function, complie_version );

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	TiXmlElement* sampler_stage_elem = root->FirstChildElement( "sampler_stage" );
	std::map<unsigned int, OvResourceTicketSPtr> stageImage;
	OvMaterial::sampler_state_table	state_table;

	for ( TiXmlElement* sampler_elem = sampler_stage_elem->FirstChildElement( "sampler" )
		; NULL != sampler_elem
		; sampler_elem = sampler_elem->NextSiblingElement( "sampler" ) )
	{
		int stage = 0;
		sampler_elem->Attribute( "stage", &stage );
		
		TiXmlElement* texture_elem = sampler_elem->FirstChildElement( "texture" );

		OvResourceTicketSPtr image = OvResourceManager::GetInstance()->AsyncLoadResource<OvTexture>( AbsolutePath( texture_elem->GetText() ) );

		stageImage[ stage ] = image;

		for ( TiXmlElement* state_elem = sampler_elem->FirstChildElement( "state" )
			; NULL != state_elem
			; state_elem = state_elem->NextSiblingElement( "state" ) )
		{
			DWORD type	= StringToStateType( state_elem->Attribute( "type") );
			DWORD value	= StringToStateValue( state_elem->GetText() );
			state_table[ make_pair( stage, type ) ] = value;
		}
	}
	

	//////////////////////////////////////////////////////////////////////////

	OvMaterialSPtr material = OvNew OvMaterial;
	material->SetVertexShader( vertexShader );
	material->SetPixelShader( pixelShader );
	for ( int i = 0 ; i < OvMaterial::MaxStage ; ++i )
	{
		material->SetStageTexture( (OvMaterial::TextureStage)i, stageImage[i] );
	}

	typedef OvMaterial::sampler_state_table::value_type state_table_type;
	for each ( const state_table_type& info in state_table )
	{
		DWORD sampler = info.first.first;
		DWORD type = info.first.second;
		DWORD value = info.second;
		material->SetSamplerState( sampler, type, value );
	}
	return material;
}