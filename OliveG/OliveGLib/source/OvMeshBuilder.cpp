#include "OvMeshBuilder.h"
#include "OvMesh.h"
#include "OvPoint3.h"
#include "OvRenderer.h"
#include "tinyxml.h"

struct OvMeshBuilder::OvPimple : OvMemObject
{

};

OvMeshSPtr	OvMeshBuilder::Build(const char* pFile)
{
	TiXmlDocument	kDoc("MeshBuild");

	if (kDoc.LoadFile(pFile))
	{

		TiXmlElement*	kpRoot = kDoc.FirstChildElement("Mesh");
		TiXmlElement*	kpEle = kpRoot->FirstChildElement("Count");

		int	kiVertCount = 0;
		int	kiFaceCount = 0;
		kpEle->Attribute("VertCount",&kiVertCount);
		kpEle->Attribute("FaceCount",&kiFaceCount);
		OvMeshSPtr	kpMesh = OvNew OvMesh(kiVertCount,kiFaceCount);

		kpEle = kpRoot->FirstChildElement("Position");
		if (kpEle)
		{
			TiXmlElement* kpPosEle = kpEle->FirstChildElement("Pos");
			for (int i=0;i<kiVertCount;++i)
			{
				if (kpPosEle)
				{
					double	kx,ky,kz;
					kpPosEle->Attribute("x",&kx);
					kpPosEle->Attribute("y",&ky);
					kpPosEle->Attribute("z",&kz);
				}
				kpPosEle = kpPosEle->NextSiblingElement();
			}
		}

		kpEle = kpRoot->FirstChildElement("Normal");
		if (kpEle)
		{
			TiXmlElement* kpNormEle = kpEle->FirstChildElement("Norm");
			for (int i=0;i<kiVertCount;++i)
			{
				if (kpNormEle)
				{
					double	kx,ky,kz;
					kpNormEle->Attribute("x",&kx);
					kpNormEle->Attribute("y",&ky);
					kpNormEle->Attribute("z",&kz);
				}
				kpNormEle = kpNormEle->NextSiblingElement();
			}
		}

		kpEle = kpRoot->FirstChildElement("FaceIndex");
		if (kpEle)
		{
			TiXmlElement* kpFaceEle = kpEle->FirstChildElement("Face");
			for (int i=0;i<kiFaceCount;++i)
			{
				if (kpFaceEle)
				{
					int k_1,k_2,k_3;
					//OvMesh::SFaceFormat	kFace;
					kpFaceEle->Attribute("a",&k_1);
					kpFaceEle->Attribute("b",&k_2);
					kpFaceEle->Attribute("c",&k_3);
				}
				kpFaceEle = kpFaceEle->NextSiblingElement();
			}
		}


		//OvRenderer::GetInstance()->ExtentionVertexBuffer(kStream.GetStreamSize());

		//OvRenderer::GetInstance()->ExtentionIndexBuffer(kStream.GetStreamSize());

		return kpMesh;

	}
	return NULL;
}