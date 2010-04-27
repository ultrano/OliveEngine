#include "OvMesh.h"
#include "OvBitFlags.h"
#include "OvRenderer.h"
#include "OvPoint3.h"
#include "OvPoint2.h"
//
#include <d3dx9.h>
#include <vector>
//

OvRTTI_IMPL_NOPARENT(OvMesh);
struct STMeshVertexFormat
{
	OvPoint3	mPosition;
	OvPoint3	mNormal;
	OvPoint2	mDiffuseTexCoord;
	enum {DefaultFVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)};
};
struct STMeshFaceFormat
{
	short _1,_2,_3;
	STMeshFaceFormat():_1(0),_2(0),_3(0){};
	STMeshFaceFormat(short _in1,short _in2,short _in3):_1(_in1),_2(_in2),_3(_in3){};
};

struct OvMesh::OvPimple : OvMemObject
{

	vector<STMeshVertexFormat>	m_vecVertStream;
	vector<STMeshFaceFormat>	m_vecFaceStream;
	OvNSMeshDescription::ePrimitiveType				m_ePrimitiveType;
	OvNSMeshDescription::eDrawType					m_eDrawType;

};

OvMesh::OvMesh(UINT uiVertCount,UINT uiFaceIndexCount):m_pPimple(OvNew OvMesh::OvPimple)
{
	m_pPimple->m_vecVertStream.resize(uiVertCount);
	m_pPimple->m_vecFaceStream.resize(uiFaceIndexCount);
	m_pPimple->m_ePrimitiveType	= OvNSMeshDescription::ePrimitiveType_Indexed;
	m_pPimple->m_eDrawType		= OvNSMeshDescription::eDrawType_TRIANGLELIST;
}
OvMesh::~OvMesh()
{
	m_pPimple->m_vecVertStream.clear();
	m_pPimple->m_vecFaceStream.clear();
}

bool	OvMesh::SetVertPosition(UINT uiVertIndex,const OvPoint3& rRet)
{
	if (IsValidVertIndex(uiVertIndex))
	{
		m_pPimple->m_vecVertStream.at(uiVertIndex).mPosition = rRet;
		return true;
	}
	return false;
}
bool	OvMesh::GetVertPosition(UINT uiVertIndex,OvPoint3& rRet)
{
	if (IsValidVertIndex(uiVertIndex))
	{
		rRet = m_pPimple->m_vecVertStream.at(uiVertIndex).mPosition;
		return true;
	}
	return false;
}
bool	OvMesh::SetVertNormal(UINT uiVertIndex,const OvPoint3& rRet)
{
	if (IsValidVertIndex(uiVertIndex))
	{
		m_pPimple->m_vecVertStream.at(uiVertIndex).mNormal = rRet;
		return true;
	}
	return false;
}
bool	OvMesh::GetVertNormal(UINT uiVertIndex,OvPoint3& rRet)
{
	if (IsValidVertIndex(uiVertIndex))
	{
		rRet = m_pPimple->m_vecVertStream.at(uiVertIndex).mNormal;
		return true;
	}
	return false;
}
bool	OvMesh::SetVertDiffuseTexCoord(UINT uiVertIndex,const OvPoint2& rRet)
{
	if (IsValidVertIndex(uiVertIndex))
	{
		m_pPimple->m_vecVertStream.at(uiVertIndex).mDiffuseTexCoord = rRet;
		return true;
	}
	return false;
}
bool	OvMesh::GetVertDiffuseTexCoord(UINT uiVertIndex,OvPoint2& rRet)
{
	if (IsValidVertIndex(uiVertIndex))
	{
		rRet = m_pPimple->m_vecVertStream.at(uiVertIndex).mDiffuseTexCoord;
		return true;
	}
	return false;
}
bool	OvMesh::SetIndexedFace(UINT uiIndex,short _1,short _2,short _3)
{
	if (IsValidFaceIndex(uiIndex))
	{
		m_pPimple->m_vecFaceStream.at(uiIndex) = STMeshFaceFormat(_1,_2,_3);
		return true;
	}
	return false;

}
bool	OvMesh::GetIndexedFace(UINT uiIndex,short& _1,short& _2,short& _3)
{
	if (IsValidFaceIndex(uiIndex))
	{
		STMeshFaceFormat kFace = m_pPimple->m_vecFaceStream.at(uiIndex);
		_1 = kFace._1;
		_2 = kFace._2;
		_3 = kFace._3;
		return true;
	}
	return false;

}
void	OvMesh::SetPrimitiveType(OvNSMeshDescription::ePrimitiveType eType)
{
	m_pPimple->m_ePrimitiveType = eType;
}
int		OvMesh::GetPrimitiveType()
{
	return (int)m_pPimple->m_ePrimitiveType;
}
void	OvMesh::SetDrawType(OvNSMeshDescription::eDrawType eType)
{
	m_pPimple->m_eDrawType = eType;
}
int		OvMesh::GetDrawType()
{
	return (int)m_pPimple->m_eDrawType;
}
bool	OvMesh::IsValidVertIndex(UINT uiVertIndex)
{
	return (m_pPimple->m_vecVertStream.size() > uiVertIndex && uiVertIndex >= 0);
}
bool	OvMesh::IsValidFaceIndex(UINT uiFaceIndex)
{
	return (m_pPimple->m_vecFaceStream.size() > uiFaceIndex && uiFaceIndex >= 0);
}
int		OvMesh::GetVertexFormatFlag()
{
	return (int)STMeshVertexFormat::DefaultFVF;
}
size_t	OvMesh::GetVertexStrideByteSize()
{
	return sizeof(STMeshVertexFormat)*sizeof(byte);
}
size_t	OvMesh::GetVertexStreamByteSize()
{
	return GetVertexCount()*sizeof(STMeshVertexFormat)*sizeof(byte);
}
void*	OvMesh::GetVertexStreamRealPointer()
{
	if (IsValidVertIndex(0))
	{
		return &(m_pPimple->m_vecVertStream.at(0));
	}
	return NULL;
}
size_t	OvMesh::GetIndexedFaceStreamByteSize()
{
	return GetFaceCount()*sizeof(STMeshFaceFormat)*sizeof(byte);
}
void*	OvMesh::GetIndexedFaceStreamRealPointer()
{
	if (IsValidFaceIndex(0))
	{
		return &(m_pPimple->m_vecFaceStream.at(0));
	}
	return NULL;
}

size_t	OvMesh::GetVertexCount()
{
	return m_pPimple->m_vecVertStream.size();
}
size_t	OvMesh::GetFaceCount()
{
	return m_pPimple->m_vecFaceStream.size();
}


