#include "OvUtility_d3dx9.h"
#include "OvBuffer.h"
#include <exception>

namespace OU
{
	namespace d3dx9
	{
		typedef OvMap<OvString,OvByte> str_byte_table;
		typedef OvMap<OvString,OvSize> str_size_table;
		typedef OvMap<OvString,OvUInt> str_uint_table;
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

				typesize["float1"] = sizeof(OvFloat);
				typesize["float2"] = sizeof(OvFloat) * 2;
				typesize["float3"] = sizeof(OvFloat) * 3;
				typesize["float4"] = sizeof(OvFloat) * 4;
				typesize["d3dcolor"] = sizeof(OvUInt) * 3;
				typesize["ubyte4"] = sizeof(OvByte) * 4;
				typesize["short2"] = sizeof(OvShort) * 2;
				typesize["short4"] = sizeof(OvShort) * 4;

				primitivetype["pointlist"]		=	D3DPT_POINTLIST    ;
				primitivetype["linelist"]		=	D3DPT_LINELIST     ;
				primitivetype["linestrip"]		=	D3DPT_LINESTRIP    ;
				primitivetype["trianglelist"]	=	D3DPT_TRIANGLELIST ;
				primitivetype["trianglestrip"]	=	D3DPT_TRIANGLESTRIP;
				primitivetype["trianglefan"]	=	D3DPT_TRIANGLEFAN  ;

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
			OvSize FindTypeSize( const OvString& str )
			{
				str_size_table::iterator itor = typesize.find( str );
				if ( itor == typesize.end() )
				{
					//DOTO: 나중에 바꿔주자
					OvString err = str + " is unknown";
					throw std::exception( err.c_str() );
				}
				return itor->second;
			}
			OvUInt FindPrimitiveType( const OvString& str )
			{
				str_uint_table::iterator itor = primitivetype.find( str );
				if ( itor == primitivetype.end() )
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

			str_size_table typesize;

			str_uint_table primitivetype;

		};
		SVEStrConvert& GetConvertTable(){ static SVEStrConvert tables; return tables; };
		D3DVERTEXELEMENT9 VertexElement( OvShort stream , OvShort offset , const OvString& type , const OvString& method , const OvString& usage , OvByte usageindex )
		{
			
			D3DVERTEXELEMENT9 ret = { stream
									, offset
									, GetConvertTable().FindType( type )
									, GetConvertTable().FindMethod( method )
									, GetConvertTable().FindUsage( usage )
									, usageindex };

			return ret;
		}

		D3DVERTEXELEMENT9 VertexElementEnd()
		{
			D3DVERTEXELEMENT9 ret = D3DDECL_END();
			return ret;
		}

		OvSize VertexElementTypeSize( const OvString& type /* == type == float1 float2 float3 float4 d3dcolor ubyte4 short2 short4 */ )
		{
			return GetConvertTable().FindTypeSize( type );
		}

		LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer( LPDIRECT3DDEVICE9 device, OvBufferSPtr buffer )
		{
			if ( buffer )
			{
				return CreateVertexBuffer( device, buffer->Pointer(), buffer->Size() );
			}
			return NULL;
		}

		LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer( LPDIRECT3DDEVICE9 device, OvByte* buffer, OvSize bufsize )
		{
			if ( device && buffer && bufsize )
			{
				LPDIRECT3DVERTEXBUFFER9 vertexStream = NULL;
				HRESULT hr = device->CreateVertexBuffer
					( bufsize
					, 0
					, 0
					, D3DPOOL_MANAGED
					, &vertexStream
					, NULL
					);
				if ( SUCCEEDED(hr) && vertexStream )
				{
					void* copyDest = NULL;
					if ( SUCCEEDED(vertexStream->Lock( 0, bufsize, &copyDest, 0)) && copyDest)
					{
						memcpy( copyDest, buffer, bufsize );
						vertexStream->Unlock();
						return vertexStream;
					}
				}
			}
			return NULL;
		}

		LPDIRECT3DINDEXBUFFER9 CreateIndexBuffer( LPDIRECT3DDEVICE9 device, OvBufferSPtr buffer )
		{
			if ( buffer )
			{
				return CreateIndexBuffer( device, buffer->Pointer(), buffer->Size() );
			}
			return NULL;
		}

		LPDIRECT3DINDEXBUFFER9 CreateIndexBuffer( LPDIRECT3DDEVICE9 device, OvByte* buffer, OvSize bufsize )
		{
			if ( device && buffer && bufsize )
			{
				LPDIRECT3DINDEXBUFFER9	streamBuffer = NULL;
				HRESULT hr = device->CreateIndexBuffer
					( bufsize
					, 0
					, D3DFMT_INDEX16
					, D3DPOOL_MANAGED
					, &streamBuffer
					, NULL
					);

				if ( SUCCEEDED(hr) && streamBuffer )
				{
					void* copyDest = NULL;
					if ( SUCCEEDED(streamBuffer->Lock( 0, bufsize, &copyDest, 0)) && copyDest)
					{
						memcpy( copyDest, buffer, bufsize );
						streamBuffer->Unlock();
						return streamBuffer;
					}
				}
			}
			return NULL;
		}

		LPDIRECT3DVERTEXDECLARATION9 CreateVertexDeclaration( LPDIRECT3DDEVICE9 device, D3DVERTEXELEMENT9* elements )
		{
			if ( device && elements )
			{
				LPDIRECT3DVERTEXDECLARATION9 vertDecl = NULL;
				HRESULT hr = device->CreateVertexDeclaration( elements, &vertDecl );
				if ( SUCCEEDED( hr ) )
				{
					return vertDecl;
				}
			}
			return NULL;
		}

		D3DPRIMITIVETYPE PrimitiveType( const OvString& type )
		{
			return (D3DPRIMITIVETYPE)GetConvertTable().FindPrimitiveType( type );
		}
	}
}






