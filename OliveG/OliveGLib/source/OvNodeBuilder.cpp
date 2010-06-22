#include "OvNodeBuilder.h"
#include "OvXNode.h"
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvStringUtility.h"
#include "OvMeshBuilder.h"
#include "OvTransformController.h"
#include "tinyxml.h"
#include "OvTranslateTable.h"
#include "OvRotateTable.h"

#include "OvCamera.h"

std::string OvGetMeshFileFromNodeFile(const string strFile,int iHandle)
{
	string kstrDirectory = OvGetDirectoryInFullFilePath(strFile);
	string kstrFileName = OvGetFileNameInFullFilePath(strFile);
	string kstrExtention = OvGetExtentionInFullFilePath(strFile);

	string kstrMeshFile = OvFormatString("%s%s_mesh_%d%s",kstrDirectory.data(),kstrFileName.data(),iHandle,kstrExtention.data());
	return kstrMeshFile;
}

// SNodeInheritInfo	OvNodeBuilder::BuildNodeInfo(const char* pFile)
// {
// 	TiXmlDocument	kDoc("NodeBuild");
// 	SNodeInheritInfo kNodeInfo;
// 
// 	if (kDoc.LoadFile(pFile))
// 	{
// 		int				kiNodeHandle = -1;
// 		int				kiParentNodeHandle = -1;
// 		OvXObjectSPtr	kpLeafObject = NULL;
// 		OvXNodeSPtr		kpBuildObj = new OvXNode;
// 		OvPoint3		kPosition;
// 		OvQuaternion	kRotation;
// 		OvPoint3		kScaleSize;
// 		TiXmlElement*	kpRoot = kDoc.FirstChildElement("Node");
// 		if (kpRoot)
// 		{
// 			TiXmlElement*	kpEle = NULL;
// 
// 			kpEle = kpRoot->FirstChildElement("NodeInfo");
// 			if (kpEle)
// 			{
// 				kpEle->Attribute("Handle",&kiNodeHandle);
// 			}
// 
// 			kpEle = kpRoot->FirstChildElement("ParentInfo");
// 			if (kpEle)
// 			{
// 				kpEle->Attribute("Handle",&kiParentNodeHandle);
// 			}
// 
// 			kpEle = kpRoot->FirstChildElement("LocalCoord");
// 			if (kpEle)
// 			{
// 				TiXmlElement*	kpCoordData = NULL;
// 
// 				kpCoordData = kpEle->FirstChildElement("Position");
// 				if (kpCoordData)
// 				{
// 					double	kx,ky,kz;
// 					kpCoordData->Attribute("x",&kx);
// 					kpCoordData->Attribute("y",&ky);
// 					kpCoordData->Attribute("z",&kz);
// 					kPosition = OvPoint3((float)kx,(float)kz,(float)ky);
// 				}
// 
// 				kpCoordData = kpEle->FirstChildElement("Rotation");
// 				if (kpCoordData)
// 				{
// 					double	kx,ky,kz,kw;
// 					kpCoordData->Attribute("x",&kx);
// 					kpCoordData->Attribute("y",&ky);
// 					kpCoordData->Attribute("z",&kz);
// 					kpCoordData->Attribute("w",&kw);
// 					kRotation = OvQuaternion((float)kx,(float)kz,(float)ky,(float)kw);
// 				}
// 
// 				kpCoordData = kpEle->FirstChildElement("Scale");
// 				if (kpCoordData)
// 				{
// 					double	kx,ky,kz;
// 					kpCoordData->Attribute("x",&kx);
// 					kpCoordData->Attribute("y",&ky);
// 					kpCoordData->Attribute("z",&kz);
// 					kScaleSize = OvPoint3((float)kx,(float)kz,(float)ky);
// 				}
// 			}
// 
// 			kpEle = kpRoot->FirstChildElement("Animation");
// 			if (kpEle)
// 			{
// 				TiXmlElement*	kpAnimKind = NULL;
// 				OvTransformControllerSPtr	kpTransformCtrler = new OvTransformController;
// 				kpTransformCtrler->SetTargetObject(kpBuildObj);
// 
// 				kpAnimKind	=	kpEle->FirstChildElement("Animate_Position");
// 				if (kpAnimKind)
// 				{
// 					int kiKeyCount = 0;
// 					TiXmlElement*	kpAnimData = NULL;
// 					kpAnimData = kpAnimKind->FirstChildElement("AnimData");
// 					kpAnimKind->Attribute("KeyCount",&kiKeyCount);
// 					if (kiKeyCount)
// 					{
// 						OvTranslateTableSPtr	kpPositionTable = new OvTranslateTable;
// 						kpTransformCtrler->SetTranslateTable(kpPositionTable);
// 						for (;kpAnimData;kpAnimData = kpAnimData->NextSiblingElement())
// 						{
// 							double	kdTick,kx,ky,kz;
// 							kpAnimData->Attribute("Tick",&kdTick);
// 							kpAnimData->Attribute("x",&kx);
// 							kpAnimData->Attribute("y",&ky);
// 							kpAnimData->Attribute("z",&kz);
// 
// 							kpPositionTable->AddPoint3((float)kdTick,OvPoint3((float)kx,(float)kz,(float)ky));
// 						}
// 					}
// 				}
// 
// 				kpAnimKind	=	kpEle->FirstChildElement("Animate_Rotation");
// 				if (kpAnimKind)
// 				{
// 					int kiKeyCount = 0;
// 					TiXmlElement*	kpAnimData = NULL;
// 					kpAnimData = kpAnimKind->FirstChildElement("AnimData");
// 					kpAnimKind->Attribute("KeyCount",&kiKeyCount);
// 					if (kiKeyCount)
// 					{
// 						float kfPI = 3.14f;
// 						float kfConvertRate = kfPI/180.0f;
// 						OvEulerTableSPtr kRotKeyTable = new OvEulerTable;
// 						kpTransformCtrler->SetRotateTable(kRotKeyTable);
// 						for (;kpAnimData;kpAnimData = kpAnimData->NextSiblingElement())
// 						{
// 							double	kdTick,kx,ky,kz,kw;
// 							kpAnimData->Attribute("Tick",&kdTick);
// 							kpAnimData->Attribute("x_rotation",&kx);
// 							kpAnimData->Attribute("y_rotation",&ky);
// 							kpAnimData->Attribute("z_rotation",&kz);
// 
// 							float kfx_rot = ((float)kx) * kfConvertRate;
// 							float kfy_rot = ((float)kz)	* kfConvertRate;
// 							float kfz_rot = ((float)ky) * kfConvertRate;
// 							//kpTransformCtrler->AddRotKey((float)kdTick,OvQuaternion((float)kx,(float)kz,(float)ky,(float)kw));
// 							kRotKeyTable->AddXYZEuler((float)kdTick,kfx_rot,kfy_rot,kfz_rot);
// 						}
// 					}
// 				}
// 			}
// 
// 			kpEle = kpRoot->FirstChildElement("NodeTrait");
// 			if (kpEle)
// 			{
// 				kpEle = kpEle->FirstChildElement();
// 				if (kpEle)
// 				{
// 					string kstrClass = kpEle->Value();
// 					if ("camera" == kstrClass)
// 					{
// 						OvCameraSPtr kpCameraLeaf = new OvCamera;
// 						OvCamera::eCameraType keType = (kpEle->Attribute("Type") == "#free")? OvCamera::eCameraType_Free : OvCamera::eCameraType_Target;
// 
// 						float	kfValue = 0;
// 						double	kdbFOV,kdbNear,kdbFar;
// 						kpEle->Attribute("FOV",&kdbFOV);
// 						kpEle->Attribute("NearClip",&kdbNear);
// 						kpEle->Attribute("FarClip",&kdbFar);
// 
// 						kpCameraLeaf->SetCameraType(keType);
// 
// 						kfValue = (float)kdbFOV;
// 						kpCameraLeaf->SetFOV((3.14f*kfValue)/180.0f);
// 
// 						kfValue = (float)kdbNear;
// 						kfValue = (kfValue < 1.0f)? 1.0f : kfValue;
// 						kpCameraLeaf->SetNearClip(kfValue);
// 
// 						kfValue = (float)kdbFar;
// 						kpCameraLeaf->SetFarClip(kfValue);
// 
// 						kpLeafObject = kpCameraLeaf;
// 					}
// 					else if ("mesh" == kstrClass)
// 					{
// 						int kiHandle = 0;
// 						kpEle->Attribute("Handle",&kiHandle);
// 						OvMeshBuilderSPtr	kMeshBuilder = new OvMeshBuilder;
// 						string kstrMeshFile = OvGetMeshFileFromNodeFile(pFile,kiHandle);
// 						OvMeshSPtr kpMesh = kMeshBuilder->Build(kstrMeshFile.data());
// 						OvMeshObjectSPtr	kpMeshObj = new OvMeshObject;
// 						kpMeshObj->SetMesh(kpMesh);
// 
// 
// 						TiXmlElement* kpOffsetCoord = kpEle->FirstChildElement("OffsetCoord");
// 						if (kpOffsetCoord)
// 						{
// 							OvPoint3		kOffsetPosition;
// 							OvQuaternion	kOffsetRotation;
// 							OvPoint3		kOffsetScaleSize;
// 							TiXmlElement*	kpCoordData = NULL;
// 
// 							kpCoordData = kpOffsetCoord->FirstChildElement("Position");
// 							if (kpCoordData)
// 							{
// 								double	kx,ky,kz;
// 								kpCoordData->Attribute("x",&kx);
// 								kpCoordData->Attribute("y",&ky);
// 								kpCoordData->Attribute("z",&kz);
// 								kOffsetPosition = OvPoint3((float)kx,(float)kz,(float)ky);
// 							}
// 
// 							kpCoordData = kpOffsetCoord->FirstChildElement("Rotation");
// 							if (kpCoordData)
// 							{
// 								double	kx,ky,kz,kw;
// 								kpCoordData->Attribute("x",&kx);
// 								kpCoordData->Attribute("y",&ky);
// 								kpCoordData->Attribute("z",&kz);
// 								kpCoordData->Attribute("w",&kw);
// 								kOffsetRotation = OvQuaternion((float)kx,(float)kz,(float)ky,(float)kw);
// 							}
// 
// 							kpCoordData = kpOffsetCoord->FirstChildElement("Scale");
// 							if (kpCoordData)
// 							{
// 								double	kx,ky,kz;
// 								kpCoordData->Attribute("x",&kx);
// 								kpCoordData->Attribute("y",&ky);
// 								kpCoordData->Attribute("z",&kz);
// 								kOffsetScaleSize = OvPoint3((float)kx,(float)kz,(float)ky);
// 							}
// 							kpMeshObj->SetTranslate(kOffsetPosition);
// 							kpMeshObj->SetRotation(kOffsetRotation);
// 							kpMeshObj->SetScale(kOffsetScaleSize);
// 						}
// 
// 						kpLeafObject = kpMeshObj;
// 					}
// 				}
// 			}
// 		}
// 		kpBuildObj->SetTranslate(kPosition);
// 		kpBuildObj->SetRotation(kRotation);
// 		kpBuildObj->SetScale(kScaleSize);
// 		kpBuildObj->AttachChild(kpLeafObject);
// 		kNodeInfo.mObject = kpBuildObj;
// 		kNodeInfo.mHandle = kiNodeHandle;
// 		kNodeInfo.mParentHandle = kiParentNodeHandle;
// 	}
// 
// 	return kNodeInfo;
// 
// 
// }
OvXNodeSPtr OvNodeBuilder::Build(const char* pFile)
{
	SNodeInheritInfo kNodeInfo = BuildNodeInfo(pFile);
	return (OvXNodeSPtr)kNodeInfo.mObject;
}