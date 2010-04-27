#include "OvXMLImportUtility.h"
#include "OvMesh.h"
#include "OvRenderableObject.h"
#include "OvRenderer.h"
#include "OvXNode.h"
#include "OvCamera.h"
#include "OvMath.h"
#include "OvStringUtility.h"
#include "OvObjectCollector.h"
#include "tinyxml.h"
#include <vector>

bool		OvXMLPoint3Import(TiXmlElement* pElement,OvPoint3& rOutput)
{
	if (pElement)
	{
		double	kx,ky,kz;
		pElement->Attribute("x",&kx);
		pElement->Attribute("y",&ky);
		pElement->Attribute("z",&kz);
		rOutput = OvPoint3((float)kx,(float)kz,(float)ky);
		return true;
	}
	return false;
}
bool			OvXMLQuaternionImport(TiXmlElement* pElement,OvQuaternion& rOutput)
{
	if (pElement)
	{
		double	kx,ky,kz,kw;
		pElement->Attribute("x",&kx);
		pElement->Attribute("y",&ky);
		pElement->Attribute("z",&kz);
		pElement->Attribute("w",&kw);
		rOutput = OvQuaternion((float)kx,(float)kz,(float)ky,(float)kw);
		return true;
	}
	return false;
}

bool		OvXMLTransformInport(TiXmlElement* pElement,OvTransform& rOutput)
{
	if (pElement)
	{
		TiXmlElement* kpOffsetCoord = pElement;
		if (kpOffsetCoord)
		{
			OvTransform		kTransform;
			TiXmlElement*	kpCoordData = NULL;

			kpCoordData = kpOffsetCoord->FirstChildElement("Position");
			if (false == OvXMLPoint3Import(kpCoordData,kTransform.Position))
			{
				OvAssertMsg("OvXMLPoint3Import is failed");
			}

			kpCoordData = kpOffsetCoord->FirstChildElement("Rotation");
			if (false == OvXMLQuaternionImport(kpCoordData,kTransform.Quaternion))
			{
				OvAssertMsg("OvXMLPoint3Import is failed");
			}

			kpCoordData = kpOffsetCoord->FirstChildElement("Scale");
			if (false == OvXMLPoint3Import(kpCoordData,kTransform.Scale))
			{
				OvAssertMsg("OvXMLPoint3Import is failed");
			}
			rOutput = kTransform;
			return true;
		}
	}
	return false;
}
struct STFaceIndex{STFaceIndex(short a1,short a2,short a3):_1(a1),_2(a2),_3(a3){};short _1,_2,_3;};
bool OvXmlPoint3Parse(TiXmlElement* kpEle,OvPoint3& Data)
{
	if (kpEle)
	{
		double	kx,ky,kz;
		kpEle->Attribute("x",&kx);
		kpEle->Attribute("y",&ky);
		kpEle->Attribute("z",&kz);
		Data = OvPoint3(kx,kz,ky);
		return true;
	}
	return false;
};bool OvXmlPoint2Parse(TiXmlElement* kpEle,OvPoint2& Data)
{
	if (kpEle)
	{
		double	kx,ky;
		kpEle->Attribute("x",&kx);
		kpEle->Attribute("y",&ky);
		Data = OvPoint2(kx,ky);
		return true;
	}
	return false;
};
struct OvXmlPoint3ListParser
{
	OvXmlPoint3ListParser(TiXmlElement*	kpEle)
	{
		if (kpEle)
		{
			TiXmlElement* kpValueEle = kpEle->FirstChildElement("Point3");
			while (kpValueEle)
			{
				OvPoint3 kParseData;
				if (OvXmlPoint3Parse(kpValueEle,kParseData))
				{
					Data.push_back(kParseData) ;
					kpValueEle = kpValueEle->NextSiblingElement();
				}
				else
				{
					OvAssertMsg(OvFormatString("[index: %d]데이터가 잘못되었습니다.",Data.size()));
					Data.clear();
					break;
				}
			}
		}
	}
	~OvXmlPoint3ListParser(){Data.clear();};
	vector<OvPoint3>	Data;
};
struct OvXmlPoint2ListParser
{
	OvXmlPoint2ListParser(TiXmlElement*	kpEle)
	{
		if (kpEle)
		{
			TiXmlElement* kpValueEle = kpEle->FirstChildElement("Point3");
			while (kpValueEle)
			{
				OvPoint2 kParseData;
				if (OvXmlPoint2Parse(kpValueEle,kParseData))
				{
					Data.push_back(kParseData) ;
					kpValueEle = kpValueEle->NextSiblingElement();
				}
				else
				{
					OvAssertMsg(OvFormatString("[index: %d]데이터가 잘못되었습니다.",Data.size()));
					Data.clear();
					break;
				}
			}
		}
	}
	~OvXmlPoint2ListParser(){Data.clear();};
	vector<OvPoint2>	Data;
};

struct OvXmlFaceParser
{
	OvXmlFaceParser(TiXmlElement*	kpEle)
	{
		if (kpEle)
		{
			TiXmlElement* kpValueEle = kpEle->FirstChildElement("Face");
			while (kpValueEle)
			{
				int k_1,k_2,k_3;

				kpValueEle->Attribute("a",&k_1);
				kpValueEle->Attribute("b",&k_2);
				kpValueEle->Attribute("c",&k_3);
				Data.push_back(STFaceIndex(k_1,k_3,k_2)) ;
				kpValueEle = kpValueEle->NextSiblingElement();
			}
		}
	}
	~OvXmlFaceParser(){Data.clear();};
	vector<STFaceIndex>	Data;
};
struct OvXmlTexCoordParser
{
	OvXmlTexCoordParser(TiXmlElement*	kpEle)
	{
		if (kpEle)
		{
			TiXmlElement* kpValueEle = kpEle->FirstChildElement("Point3");
			while (kpValueEle)
			{
				double	ku,kv,kw;
				kpValueEle->Attribute("x",&ku);
				kpValueEle->Attribute("y",&kv);
				kpValueEle->Attribute("z",&kw);
				Data.push_back(OvPoint2((float)ku,(float)(1.0-kv))) ;
				kpValueEle = kpValueEle->NextSiblingElement();
			}
		}
	}
	~OvXmlTexCoordParser(){Data.clear();};
	vector<OvPoint2>	Data;
};
OvMeshSPtr OvXMLMeshImport(TiXmlElement* pElement)
{
	if (pElement)
	{
		TiXmlElement*	kpRoot = pElement;
		TiXmlElement*	kpEle = NULL;
		kpEle = kpRoot->FirstChildElement("Vertex");
		OvXmlPoint3ListParser kVertParser(kpEle);

		kpEle = kpRoot->FirstChildElement("Normal");
		OvXmlPoint3ListParser kNormParser(kpEle);

		kpEle = kpRoot->FirstChildElement("VertexFace");
		OvXmlFaceParser kFaceParser(kpEle);

		kpEle = kpRoot->FirstChildElement("TVertex");
		OvXmlTexCoordParser kTVertParser(kpEle);

		kpEle = kpRoot->FirstChildElement("TVertexFace");
		OvXmlFaceParser kTFaceParser(kpEle);




		int kiVertCount = max(kVertParser.Data.size(),kTVertParser.Data.size());
		int kiFaceCount = max(kFaceParser.Data.size(),kTFaceParser.Data.size());
		OvMeshSPtr	kpMesh = NULL;
		kpMesh = new OvMesh(kiVertCount,kiFaceCount);
		if (kpMesh)
		{
			for (int i=0;i<kiFaceCount;++i)
			{
				STFaceIndex kFIndex = kFaceParser.Data[i];
				STFaceIndex kTFIndex = kTFaceParser.Data[i];

				kpMesh->SetVertPosition(kTFIndex._1,kVertParser.Data[kFIndex._1]);
				kpMesh->SetVertPosition(kTFIndex._2,kVertParser.Data[kFIndex._2]);
				kpMesh->SetVertPosition(kTFIndex._3,kVertParser.Data[kFIndex._3]);

				kpMesh->SetVertNormal(kTFIndex._1,kNormParser.Data[kFIndex._1]);
				kpMesh->SetVertNormal(kTFIndex._2,kNormParser.Data[kFIndex._2]);
				kpMesh->SetVertNormal(kTFIndex._3,kNormParser.Data[kFIndex._3]);

				kpMesh->SetVertDiffuseTexCoord(kTFIndex._1,kTVertParser.Data[kTFIndex._1]);
				kpMesh->SetVertDiffuseTexCoord(kTFIndex._2,kTVertParser.Data[kTFIndex._2]);
				kpMesh->SetVertDiffuseTexCoord(kTFIndex._3,kTVertParser.Data[kTFIndex._3]);

				kpMesh->SetIndexedFace(i,kTFIndex._1,kTFIndex._2,kTFIndex._3);
			}

			OvRenderer::GetInstance()->ExtentionVertexBuffer(kpMesh->GetVertexStreamByteSize());

			OvRenderer::GetInstance()->ExtentionIndexBuffer(kpMesh->GetIndexedFaceStreamByteSize());

			return kpMesh;
		}

	}
	return  NULL;
};

OvXObjectSPtr	OvXMLGeomImport(TiXmlElement* pElement)
{
	if (pElement)
	{
		OvRenderableObjectSPtr	kpRenderObj = new OvRenderableObject();
		TiXmlElement* pEle = NULL;
		
		pEle = pElement->FirstChildElement("OffsetCoord");
		if (pEle)
		{
			OvTransform	kTransform;
			if (false == OvXMLTransformInport(pEle,kTransform))
			{
				OvAssertMsg("OvXMLTransformInport is failed");
			}
			else
			{
				kpRenderObj->SetTranslate(kTransform.Position);
				kpRenderObj->SetRotation(kTransform.Quaternion);
				kpRenderObj->SetScale(kTransform.Scale);
			}

		}

		pEle = pElement->FirstChildElement("Mesh");
		if (pEle)
		{
			OvMeshSPtr kpMesh = OvXMLMeshImport(pEle);
			if (kpMesh == NULL)
			{
				OvAssertMsg("OvXMLMeshImport is failed");
			}
			else
			{
				kpRenderObj->SetMesh(kpMesh);
			}
		}
		return kpRenderObj;
	}
	return NULL;
}

OvXObjectSPtr	OvXMLNodeImport(TiXmlElement* pElement)
{

	if(pElement)
	{
		int				kiNodeHandle = -1;
		int				kiParentNodeHandle = -1;
		OvXNodeSPtr		kpBuildObj = OvNew OvXNode;
		string			kName;
		OvTransform		kTransform;
		TiXmlElement*	kpRoot = pElement;
		if (kpRoot && kpBuildObj)
		{
			TiXmlElement*	kpEle = NULL;

			kpEle = kpRoot->FirstChildElement("NodeInfo");
			if (kpEle)
			{
				kName = kpEle->Attribute("Name");
				kpEle->Attribute("Handle",&kiNodeHandle);
			}

			kpEle = kpRoot->FirstChildElement("ParentInfo");
			if (kpEle)
			{
				kpEle->Attribute("Handle",&kiParentNodeHandle);
			}

			kpEle = kpRoot->FirstChildElement("LocalCoord");
			if (kpEle)
			{
				if (false == OvXMLTransformInport(kpEle,kTransform))
				{
					OvAssertMsg("OvXMLTransformInport is failed");
				}
			}
			kpBuildObj->SetName(kName.data());
			kpBuildObj->SetTranslate(kTransform.Position);
			kpBuildObj->SetRotation(kTransform.Quaternion);
			kpBuildObj->SetScale(kTransform.Scale);
			return kpBuildObj;
		}
	}
	return NULL;

}
OvXObjectSPtr	OvXMLCameraImport(TiXmlElement* pElement)
{
	if (pElement)
	{
		OvCameraSPtr kpCameraObj = OvNew OvCamera;
		double	kdbFOV,kdbNear,kdbFar;
		OvCamera::eCameraType keType;
		TiXmlElement* kpEle = NULL;

		kpEle = pElement->FirstChildElement("CameraInfo");
		if (kpEle)
		{
			keType = (pElement->Attribute("Type") == "#free")? OvCamera::eCameraType_Free : OvCamera::eCameraType_Target;
			kpEle->Attribute("FOV",&kdbFOV);
		}

		kpEle = pElement->FirstChildElement("ClipPlane");
		if (kpEle)
		{
			kpEle->Attribute("NearClip",&kdbNear);
			kpEle->Attribute("FarClip",&kdbFar);
		}

		float	kfValue = 0;

		kpCameraObj->SetCameraType(keType);

		kpCameraObj->SetFOV((3.14f*((float)kdbFOV))/180.0f);

		kpCameraObj->SetNearClip(((((float)kdbNear) < 1.0f)? 1.0f : ((float)kdbNear)));

		kpCameraObj->SetFarClip(((float)kdbFar));

		return kpCameraObj;
	}
	return NULL;
};

bool OvXMLNodeTableImport(TiXmlElement* pElement,map<int,OvXObjectSPtr>& tblOutput)
{
	if (pElement)
	{
		map<int,int>	kInheritTable;
		map<int,OvXObjectSPtr>	kNodeTable;
		TiXmlElement* kpEle = NULL;
		kpEle = pElement->FirstChildElement("Node");
		for ( ; kpEle ; kpEle = kpEle->NextSiblingElement())
		{
			int kiExtHandle = -1;
			int kiParentHandle = -1;
			kpEle->Attribute("Handle",&kiExtHandle);
			kpEle->Attribute("ParentHandle",&kiParentHandle);
			OvXObjectSPtr	kImportObj = OvXMLNodeImport(kpEle);
			if (kImportObj)
			{
				//kNodeTable.insert(pair<int,OvXObjectSPtr>(kiExtHandle,kImportObj));
				kInheritTable[kiExtHandle] = kiParentHandle;//! 이부분이 좀 문제가 될 여지가 있다.
			}
		}
// 		map<int,int>::iterator	kIter = kInheritTable.begin();
// 		for (;kIter != kInheritTable.end();++kIter)
// 		{
// 			OvXNodeSPtr	kpParentNode = NULL;
// 			OvXNodeSPtr	kpChildNode = NULL;
// 			if (kNodeTable.find(kIter->second) != kNodeTable.end())
// 			{
// 				kpParentNode = kNodeTable[kIter->second];
// 			}
// 			if (kNodeTable.find(kIter->first) != kNodeTable.end())
// 			{
// 				kpChildNode = kNodeTable[kIter->first];
// 			}
// 			if (kpChildNode && kpParentNode)
// 			{
// 				kpParentNode->AttachChild(kpChildNode);
// 			}
// 		}
		tblOutput = kNodeTable;
		kNodeTable.clear();
		kInheritTable.clear();
		return true;
	}
	return false;
};
bool			 OvXMLGeomTableImport(TiXmlElement* pElement,map<int,OvXObjectSPtr>& tblOutput)
{
	if (pElement)
	{
		tblOutput.clear();
		TiXmlElement* kpEle = NULL;
		kpEle = pElement->FirstChildElement("Geometry");
		for ( ; kpEle ; kpEle = kpEle->NextSiblingElement())
		{
			int kiExtHandle = -1;
			kpEle->Attribute("LinkedNode",&kiExtHandle);
			OvXObjectSPtr	kImportObj = OvXMLGeomImport(kpEle);
			if (kImportObj)
			{
				tblOutput[kiExtHandle] = kImportObj;
			}
		}
		return true;
	}
	return false;
}
bool			 OvXMLCameraTableImport(TiXmlElement* pElement,map<int,OvXObjectSPtr>& tblOutput)
{
	if (pElement)
	{
		tblOutput.clear();
		TiXmlElement* kpEle = NULL;
		kpEle = pElement->FirstChildElement("Camera");
		for ( ; kpEle ; kpEle = kpEle->NextSiblingElement())
		{
			int kiExtHandle = -1;
			kpEle->Attribute("Handle",&kiExtHandle);
			OvXObjectSPtr	kImportObj = OvXMLCameraImport(kpEle);
			if (kImportObj)
			{
				tblOutput[kiExtHandle] = kImportObj;
			}
		}
		return true;
	}
	return false;
}
OvXObjectSPtr	OvXMLSceneNodeImport(TiXmlElement* pElement)
{
	if (pElement)
	{
		OvXNodeSPtr	kpSceneNode = OvNew OvXNode;
		map<int,OvXObjectSPtr> ktblNodeTable;
		TiXmlElement* kpEle = NULL;

		kpEle = pElement->FirstChildElement("NodeTable");
		if (OvXMLNodeTableImport(kpEle,ktblNodeTable))
		{
			map<int,OvXObjectSPtr>::iterator kIter = ktblNodeTable.begin();
			for (;kIter != ktblNodeTable.end();++kIter)
			{
				if (kIter->second->GetParent() == NULL)
				{
					kpSceneNode->AttachChild(kIter->second);
				}
			}
		}
		ktblNodeTable.clear();
		kpSceneNode = NULL;
		return NULL;

		/*kpEle = pElement->FirstChildElement("GeomTable");
		if (kpEle&&OvXMLGeomTableImport(kpEle,ktblGeomTable))
		{
			map<int,OvXObjectSPtr>::iterator kIter = ktblGeomTable.begin();
			for (;kIter != ktblGeomTable.end();++kIter)
			{
				OvXNodeSPtr	kpNode = ktblNodeTable[kIter->first];
				if (kpNode)
				{
					kpNode->AttachChild(kIter->second);
				}
			}
		}

		kpEle = pElement->FirstChildElement("CameraTable");
		if (kpEle&&OvXMLCameraTableImport(kpEle,ktblGeomTable))
		{
			map<int,OvXObjectSPtr>::iterator kIter = ktblGeomTable.begin();
			for (;kIter != ktblGeomTable.end();++kIter)
			{
				OvXNodeSPtr	kpNode = ktblNodeTable[kIter->first];
				if (kpNode)
				{
					kpNode->AttachChild(kIter->second);
				}
			}
		}

		ktblNodeTable.clear();
		ktblGeomTable.clear();
		ktblCameraTable.clear();
		return kpSceneNode;*/
	}
	return NULL;
}