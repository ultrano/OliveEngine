#pragma once
#include "OvTypeDef.h"
#include "OvSmartPointer.h"
#include <d3dx9.h>

OvREF_POINTER(OvBuffer);

namespace OU
{
	namespace d3dx9
	{
		D3DPRIMITIVETYPE PrimitiveType( const OvString& type
														/*
														pointlist
														linelist
														linestrip
														trianglelist
														trianglestrip
														trianglefan
														*/);
		D3DVERTEXELEMENT9 VertexElement( OvShort stream
														/* == stream ==
														0~n
														*/
										, OvShort offset
														/* == offset ==
														0~n
														*/
										, const OvString& type
														/* == type ==
														float1
														float2
														float3
														float4
														d3dcolor
														ubyte4
														short2
														short4
														*/
										, const OvString& method
														/* == method ==
														default
														partialu
														partialv
														crossuv
														uv
														lookup
														lookuppresampled
														*/
										, const OvString& usage
														/* == usage ==
														position
														blendweight
														blendindices
														normal
														psize
														texcoord
														tangent
														binormal
														tessfactor
														positiont
														color
														fog
														depth
														sample
														*/
										, OvByte usageindex
														/* == usageindex ==
														0~n
														*/);
		D3DVERTEXELEMENT9 VertexElementEnd();

		OvSize	VertexElementTypeSize( const OvString& type
														/* == type ==
														float1
														float2
														float3
														float4
														d3dcolor
														ubyte4
														short2
														short4
														*/);

		LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer( LPDIRECT3DDEVICE9 device, OvBufferSPtr buffer );
		LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer( LPDIRECT3DDEVICE9 device, OvByte* buffer, OvSize bufsize );

		LPDIRECT3DINDEXBUFFER9 CreateIndexBuffer( LPDIRECT3DDEVICE9 device, OvBufferSPtr buffer );
		LPDIRECT3DINDEXBUFFER9 CreateIndexBuffer( LPDIRECT3DDEVICE9 device, OvByte* buffer, OvSize bufsize );

		LPDIRECT3DVERTEXDECLARATION9 CreateVertexDeclaration( LPDIRECT3DDEVICE9 device, D3DVERTEXELEMENT9* elements );
	}
}