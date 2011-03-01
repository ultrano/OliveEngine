#include "OvUtility_render.h"
#include <exception>

namespace OU
{
	namespace d3dx9
	{
		typedef OvMap<OvString,OvByte> str_byte_table;
		struct SVEStrConvert
		{
			SVEStrConvert()
			{
				datatype["float1"] = D3DDECLTYPE_FLOAT1;
				datatype["float2"] = D3DDECLTYPE_FLOAT2;
				datatype["float3"] = D3DDECLTYPE_FLOAT3;
				datatype["float4"] = D3DDECLTYPE_FLOAT4;
				datatype["d3dcolor"] = D3DDECLTYPE_D3DCOLOR;
				datatype["ubyte4"] = D3DDECLTYPE_UBYTE4;
				datatype["short2"] = D3DDECLTYPE_SHORT2;
				datatype["short4"] = D3DDECLTYPE_SHORT4;


				method["default"] = D3DDECLMETHOD_DEFAULT;
				method["partialu"] = D3DDECLMETHOD_PARTIALU;
				method["partialv"] = D3DDECLMETHOD_PARTIALV;
				method["crossuv"] = D3DDECLMETHOD_CROSSUV;
				method["uv"] = D3DDECLMETHOD_UV;
				method["lookup"] = D3DDECLMETHOD_LOOKUP;
				method["lookuppresampled"] = D3DDECLMETHOD_LOOKUPPRESAMPLED;


				usage["position"] = D3DDECLUSAGE_POSITION;
				usage["blendweight"] = D3DDECLUSAGE_BLENDWEIGHT;
				usage["blendindices"] = D3DDECLUSAGE_BLENDINDICES;
				usage["normal"] = D3DDECLUSAGE_NORMAL;
				usage["psize"] = D3DDECLUSAGE_PSIZE;
				usage["texcoord"] = D3DDECLUSAGE_TEXCOORD;
				usage["tangent"] = D3DDECLUSAGE_TANGENT;
				usage["binormal"] = D3DDECLUSAGE_BINORMAL;
				usage["tessfactor"] = D3DDECLUSAGE_TESSFACTOR;
				usage["positiont"] = D3DDECLUSAGE_POSITIONT;
				usage["color"] = D3DDECLUSAGE_COLOR;
				usage["fog"] = D3DDECLUSAGE_FOG;
				usage["depth"] = D3DDECLUSAGE_DEPTH;
				usage["sample"] = D3DDECLUSAGE_SAMPLE;

			}
			OvUInt FindType( const OvString& str )
			{
				str_byte_table::iterator itor = datatype.find( str );
				if ( itor == datatype.end() )
				{
					//DOTO: 나중에 바꿔주자
					OvString err = str + " is unknown";
					throw std::exception( err.c_str() );
				}
				return itor->second;
			}
			OvUInt FindMethod( const OvString& str )
			{
				str_byte_table::iterator itor = method.find( str );
				if ( itor == method.end() )
				{
					//DOTO: 나중에 바꿔주자
					OvString err = str + " is unknown";
					throw std::exception( err.c_str() );
				}
				return itor->second;
			}
			OvUInt FindUsage( const OvString& str )
			{
				str_byte_table::iterator itor = usage.find( str );
				if ( itor == usage.end() )
				{
					//DOTO: 나중에 바꿔주자
					OvString err = str + " is unknown";
					throw std::exception( err.c_str() );
				}
				return itor->second;
			}
			str_byte_table datatype;
			str_byte_table method;
			str_byte_table usage;
		};

		D3DVERTEXELEMENT9 VertexElement( OvShort stream , OvShort offset , const OvString& type , const OvString& method , const OvString& usage , OvByte usageindex )
		{
			static SVEStrConvert tables;
			D3DVERTEXELEMENT9 ret = { stream
									, offset
									, tables.FindType( type )
									, tables.FindMethod( method )
									, tables.FindUsage( usage )
									, usageindex };

			return ret;
		}

		D3DVERTEXELEMENT9 VertexElementEnd()
		{
			D3DVERTEXELEMENT9 ret = D3DDECL_END();
			return ret;
		}

	}
}






