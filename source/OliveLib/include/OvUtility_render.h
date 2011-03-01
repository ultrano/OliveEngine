#pragma once
#include "OvTypeDef.h"
#include <d3dx9.h>

namespace OU
{
	namespace d3dx9
	{
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
	}
}