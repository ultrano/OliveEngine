#pragma once

namespace OvNSMeshDescription
{
	enum eDrawType
	{
		eDrawType_UNKNOWN,
		eDrawType_POINTLIST,
		eDrawType_LINELIST,
		eDrawType_LINESTRIP,
		eDrawType_TRIANGLELIST,
		eDrawType_TRIANGLESTRIP,
		eDrawType_TRIANGLEFAN,
	};
	enum ePrimitiveType
	{
		ePrimitiveType_Indexed,
		ePrimitiveType_None_Indexed
	};
	enum eVertexFormatType
	{
		eVertexFormatType_Position,
		eVertexFormatType_Normal,
		eVertexFormatType_DiffuseTexCoord,
	};
};