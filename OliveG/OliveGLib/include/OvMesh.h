#pragma once
#include "OvObject.h"
#include "OvRTTI.h"
#include "OvAutoPtr.h"
#include "OvNSMeshDescription.h"

class OvPoint3;
class OvPoint2;

OvREF_POINTER(OvMesh);
class OvMesh : public OvObject
{
	OvRTTI_DECL(OvMesh);

public :

	OvMesh(UINT uiVertCount,UINT uiFaceIndexCount);
	~OvMesh();

	bool	SetVertPosition(UINT uiVertIndex,const OvPoint3& rRet);
	bool	GetVertPosition(UINT uiVertIndex,OvPoint3& rRet);

	bool	SetVertNormal(UINT uiVertIndex,const OvPoint3& rRet);
	bool	GetVertNormal(UINT uiVertIndex,OvPoint3& rRet);

	bool	SetVertDiffuseTexCoord(UINT uiVertIndex,const OvPoint2& rRet);
	bool	GetVertDiffuseTexCoord(UINT uiVertIndex,OvPoint2& rRet);

	bool	SetIndexedFace(UINT uiIndex,short _1,short _2,short _3);
	bool	GetIndexedFace(UINT uiIndex,short& _1,short& _2,short& _3);

	void	SetPrimitiveType(OvNSMeshDescription::ePrimitiveType eType);
	int		GetPrimitiveType();

	void	SetDrawType(OvNSMeshDescription::eDrawType eType);
	int		GetDrawType();

	bool	IsValidVertIndex(UINT uiVertIndex);
	bool	IsValidFaceIndex(UINT uiFaceIndex);

	int		GetVertexFormatFlag();

	size_t	GetVertexStrideByteSize();

	size_t	GetVertexStreamByteSize();
	void*	GetVertexStreamRealPointer();

	size_t	GetIndexedFaceStreamByteSize();
	void*	GetIndexedFaceStreamRealPointer();

	size_t	GetVertexCount();
	size_t	GetFaceCount();

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};