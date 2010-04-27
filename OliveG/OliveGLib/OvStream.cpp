
#define OvExportDll
#include "OvStream.h"
#include "OvMgrDepository.h"
#include "OvAVMesh.h"
#include "OvGeomObject.h"
#include "OvXGeomData.h"
#include "OvXFileExporter.h"
#include "OvOliveFileImporter.h"
#include "OvOliveGeomData.h"
#include "OvTextureMgr.h"
#include "OvTransformSupporter.h"
#include "OvDirectLightEffect.h"
#include "OvOmniLightEffect.h"
#include "OvCamera.h"
#include "OvSkinInstance.h"
#include "OvSkinData.h"
#include <algorithm>
#include "OvStringUtils.h"

using namespace Olive;

OvStream::OvStream():m_lpBuildedNode(0),m_pSaveFile(0)
{

}
//
//bool OvStream::LoadFromX(const char* _file)
//{
//
//	OvDeviceMgr*	k_device_mgr = (OvDeviceMgr*)OvMgrDepository::Instance()->GetMgr(e_Mgr_OvDevice);
//
//	LPDIRECT3DDEVICE9 k_device = (LPDIRECT3DDEVICE9)k_device_mgr->GetDevice();
//
//	OvXFileExporter	k_allocator;
//	D3DXFRAME*				k_lp_frame;
//	OvAVMesh*	k_lp_model = NULL;
//
//	OvActiveObject*	k_lp_model_node;
//	k_allocator;
//	k_allocator.LoadMesh(_file,D3DXMESH_MANAGED,k_device,NULL,&k_lp_model_node,NULL);
//	k_lp_frame	=	k_allocator.GetFrame();
//
//	BuildNode(&m_lpBuildedNode,k_lp_frame);
//
//	m_lpBuildedNode->Update(0);
//
//	return m_lpBuildedNode;
//
//}

bool	OvStream::LoadFromOlive(const char* _File)
{

	OvOliveFileImporterPtr	klpExporter = new OvOliveFileImporter;

	klpExporter->Export(_File);;

	map<string,OvActiveObjectPtr>	kNodeTable;

	vector<OvSkinInstancePtr>		kSkinArray;

	DWORD	kObjCount = klpExporter->GetObjectCount();

	OvOliveObject*	kObject = NULL;

	for(int i=0;i<kObjCount;++i)
	{

		kObject = klpExporter->GetObjectAt(i);

		OvActiveObjectPtr	kAvNode = NULL;

		if(OvRTTI_IsKindOf(OvOliveObject,kObject))
		{
			OvNodePtr	kNode = new OvNode;

			kAvNode	=	(OvActiveObject*)kNode;

		};

		if(OvRTTI_IsKindOf(OvOliveGeomObject,kObject))
		{
			vector<OvGeomObjectPtr>	kGeomArray;
			OvOliveGeomObject*	kOliveGeomObject = static_cast<OvOliveGeomObject*>(kObject);
			for(DWORD i=0;i<kOliveGeomObject->mGeoms.size();++i)
			{
				OvOliveGeomDataPtr kGeomData = new OvOliveGeomData(kOliveGeomObject->mGeoms[i].mMesh,kOliveGeomObject->mGeoms[i].mPolygonCount);
				OvGeomObjectPtr	kGeomObject = new OvGeomObject(kGeomData);
				OvOliveMaterial*	kOliveMaterial = klpExporter->GetOliveMaterial(kOliveGeomObject->mMaterialRef);

				if(kOliveMaterial )
				{
					if(kOliveMaterial->mSubMatarials.size()>kOliveGeomObject->mGeoms[i].mMaterialRef)
						kOliveMaterial	=	kOliveMaterial->mSubMatarials[kOliveGeomObject->mGeoms[i].mMaterialRef];

					kGeomObject->SetBaseMaterial(kOliveMaterial->mD3DMT9);
					if(kOliveMaterial->mTexture)
					{
						kGeomObject->SetBaseTexture(OvTextureMgr::Instance()->LoadResource(kOliveMaterial->mTexture->mFile.data()));
					};

					/////////////  수정 요망 //////////////////////////
					if(kOliveMaterial->mOpacity)
					{
						kGeomObject->SetBaseTexture(OvTextureMgr::Instance()->LoadResource(kOliveMaterial->mOpacity->mFile.data()));
						kGeomObject->SetProperty(OvGeomObject::Property_Alpha,true);
					};
					////////////////////////////////////////////////////

				};

				if(kOliveGeomObject->mSkinData)
				{
					OvSkinInstancePtr	kSkinInstance	=	new OvSkinInstance(kOliveGeomObject->mSkinData,kGeomObject,NULL);
					kGeomObject->SetSkinInstance(kSkinInstance);
					kSkinArray.push_back(kSkinInstance);
				};

				OvBound	kBound;
				kBound.SetCenter(kOliveGeomObject->mGeoms[i].mCenter);
				kBound.SetRadius(kOliveGeomObject->mGeoms[i].mRadius);
				kGeomObject->SetWorldBound(kBound);

				kGeomArray.push_back(kGeomObject);
			}
			if(kGeomArray.size()>1)
			{
				OvNodePtr	kNode = new OvNode;

				kAvNode	=	(OvActiveObject*)kNode;
				for(DWORD i=0;i<kGeomArray.size();++i)
				{
					OvLexical	kLex;
					string kNewName	=	kObject->mObjName;
					kNewName	+=	' ';
					kNewName	+=	kLex(i);
					kGeomArray[i]->SetName(kNewName.data());
					kGeomArray[i]->SetLocalTransform(kObject->mMatrix);
					kNode->AttachChild(kGeomArray[i]);
				};
			}else{
				kAvNode	=	(OvActiveObject*)kGeomArray[0];
			};

		}

		if(OvRTTI_IsKindOf(OvOliveLightObject,kObject))
		{
			OvOliveLightObject* kLightObject = (OvOliveLightObject*)kObject;

			OvPoint3 kColor = kLightObject->mLightColor;
			float	kColorPower = kLightObject->mLightPower;

			OvColor kDiffuse(kColor.x*kColorPower,kColor.y*kColorPower,kColor.z*kColorPower,1*kColorPower);

			switch(kLightObject->mLightType)
			{
			case OvOliveLightObject::eDirect: 
				{
					OvLightEffectPtr	kNode = new OvDirectLightEffect(kDiffuse,kDiffuse,kDiffuse);

					kAvNode	=	kNode;
				}
				break;
			case OvOliveLightObject::eOmni: 
				{
					OvLightEffectPtr	kNode = new OvOmniLightEffect(kDiffuse,kDiffuse,kDiffuse);

					kAvNode	=	kNode;
				}
				break;
			}


		}
		if(OvRTTI_IsKindOf(OvOliveCameraObject,kObject))
		{
			OvCameraPtr		kNode = new OvCamera();
			kAvNode	=	kNode;
			OvOliveCameraObject* kCameraObjet = (OvOliveCameraObject*)kObject;
			kNode->SetNearPlaneDistance(kCameraObjet->mNearPlane);
			kNode->SetFarPlaneDistance(kCameraObjet->mFarPlane);
			kNode->SetFOV(kCameraObjet->mFOV);
			kNode->SetTargetDistance(kCameraObjet->mTDist);

		}
		if(kAvNode)
		{
			kAvNode->SetName(kObject->mObjName.data());
			//	매트릭스에서 스케일정보 얻어오는법을 모르겠다 ㅠㅠ
			kAvNode->SetLocalTransform(kObject->mPos,kObject->mRot,kObject->mScale.x);
			kAvNode->SetLocalTransform(kObject->mMatrix);
			kNodeTable[kObject->mObjName] = kAvNode;
		}

	};

	vector<OvDynamicEffect*> kEffects;

	for(int i=0;i<kObjCount;++i)
	{

		OvActiveObjectPtr	kParentObject = NULL;

		kObject = klpExporter->GetObjectAt(i);
		if((kNodeTable.find(kObject->mParentName) != kNodeTable.end()))
		{
			kParentObject = (OvNode*)&*kNodeTable[kObject->mParentName];
			if( ! kParentObject->IsNode())
			{
				OvNodePtr kParentNode = new OvNode;
				kParentNode->SetName(kParentObject->GetName());
				kParentObject->SetName("");
				kParentNode->SetLocalTransform(kParentObject->GetLocalTransform());
				kParentNode->AttachChild(kParentObject);
				/*static int ksA;
				if(++ksA==30)
					int a=0;*/

				if(OvRTTI_IsStemFrom(OvDynamicEffect,kParentObject))
				{
					kEffects.push_back((OvDynamicEffect *)&*kParentObject);
				};
				kNodeTable[kObject->mParentName] = kParentNode;
			};
		}
	}

	for(DWORD i=0;i<kSkinArray.size();++i)
	{
		OvSkinInstance*	kSkin	=	kSkinArray[i];
		OvSkinData* kSkinData	=	kSkin->GetSkinData();

		for(DWORD kIndex = 0 ; const char* kBoneName = kSkinData->GetBoneNameByIndex(kIndex) ; ++kIndex)
		{
			kSkin->SetBone(kIndex,NULL);
			if(kNodeTable.find(kBoneName) != kNodeTable.end())
				kSkin->SetBone(kIndex,kNodeTable[kBoneName]);
		}

	};

	for(int i=0;i<kObjCount;++i)
	{

		OvNodePtr	kParentNode = NULL;
		OvActiveObjectPtr	kChildNode = NULL;

		kObject = klpExporter->GetObjectAt(i);
		if((kNodeTable.find(kObject->mObjName) != kNodeTable.end()) && (kNodeTable.find(kObject->mParentName) != kNodeTable.end()))
		{
			kParentNode = (OvNode*)&*kNodeTable[kObject->mParentName];
			kChildNode = kNodeTable[kObject->mObjName];
			kParentNode->AttachChild(kChildNode);

			if(OvRTTI_IsStemFrom(OvDynamicEffect,kChildNode))
			{
				kEffects.push_back((OvDynamicEffect *)&*kChildNode);
			};
		}else
		{
			if(!m_lpBuildedNode)
			m_lpBuildedNode = (OvNode*)&*kNodeTable[kObject->mObjName];
		};

	};

	for(long i=0;i<kEffects.size();++i)
	{
		m_lpBuildedNode->AttachEffect(kEffects[i]);
	};

	BuildInheritLocalTransform( m_lpBuildedNode );

	for(int i=0;i<kObjCount;++i)
	{

		OvNodePtr	kNode = NULL;

		kObject = klpExporter->GetObjectAt(i);
		if((kNodeTable.find(kObject->mObjName) != kNodeTable.end()) && kObject->mAnim)
		{
			ConvertLocalOliveAnim(kNodeTable[kObject->mObjName],kObject->mAnim);

			OvTransformSupporterPtr kTrans = new OvTransformSupporter(*kObject->mAnim);
			kNodeTable[kObject->mObjName]->PrependSupporter(kTrans);

		};

	};

	kNodeTable.clear();

	return true;
};



void		OvStream::ConvertLocalOliveAnim(OvActiveObject* _Obj,OvSamplingAnimData* _Anim)
{

	OvSamplingAnimData::OvPosTable::iterator kPIt = _Anim->mPosTable.begin();
	OvSamplingAnimData::OvRotTable::iterator kRIt = _Anim->mRotTable.begin();
	//OvSamplingAnimData::OvPosTable::iterator kPIt = _Anim->mPosTable.begin();

	while(kPIt != _Anim->mPosTable.end())
	{
		kPIt->second	=	kPIt->second - OvPoint3(_Obj->GetLocalTransform()._41,_Obj->GetLocalTransform()._42,_Obj->GetLocalTransform()._43);
		D3DXQUATERNION kInvQuat;
		D3DXMATRIXA16	kInvMat;

		D3DXQuaternionRotationMatrix(&kInvQuat,&_Obj->GetLocalTransform());

		D3DXQuaternionInverse(&kInvQuat,&kInvQuat);

		D3DXMatrixRotationQuaternion(&kInvMat,&kInvQuat);

		D3DXVec3TransformCoord(&kPIt->second,&kPIt->second,&kInvMat);

		++kPIt;
	};

	while(kRIt != _Anim->mRotTable.end())
	{	
		D3DXQUATERNION kInvQuat;

		D3DXQuaternionRotationMatrix(&kInvQuat,&_Obj->GetLocalTransform());

		D3DXQuaternionInverse(&kInvQuat,&kInvQuat);

		D3DXQuaternionNormalize(&kInvQuat,&kInvQuat);

		kRIt->second	=	kRIt->second * kInvQuat;

		//D3DXQuaternionNormalize(&kRIt->second,&kRIt->second);

		++kRIt;
	};

};

OvActiveObject*	OvStream::GetObject()
{
	if (m_lpBuildedNode)
	{
		return m_lpBuildedNode;
	}
	return NULL;
}

void OvStream::SaveObject(const char* _pFileName,OvActiveObject* _pObject)
{
	if(!_pObject || !_pFileName)
		return ;

	m_listStreamArray.clear();

	m_pSaveFile = fopen(_pFileName,"wt");

	SearchStreamObject(_pObject);

	struct SaveFunctor
	{
		OvStream* mpStream;
		SaveFunctor(OvStream* _pStream):mpStream(_pStream){};
		void operator()(OvStreamObject* _pStreamObj)
		{
			_pStreamObj->SaveMemento(mpStream);
		}
	};

	for_each(m_listStreamArray.begin(),m_listStreamArray.end(),SaveFunctor(this));

	fclose(m_pSaveFile);
	m_pSaveFile = NULL;

}

void OvStream::SearchStreamObject(OvActiveObject* _pObject)
{
	if(OvRTTI_IsStemFrom(OvStreamObject,_pObject))
	{
		if (OvSTL_Find(m_listStreamArray,_pObject) == m_listStreamArray.end())
		{
			m_listStreamArray.push_back(_pObject);
		}
	}
	if (_pObject->IsNode())
	{
		OvNode* kpNode = static_cast<OvNode*>(_pObject);
		for (DWORD i=0;i<kpNode->GetChildCount();++i)
		{
			SearchStreamObject(kpNode->GetChildAt(i));
		}
	}
}

void OvStream::WriteData(const char* _pBuffer,DWORD _dSize)
{
	if(!_pBuffer || !_dSize || !m_pSaveFile)
		return ;

	fwrite(_pBuffer,_dSize,1,m_pSaveFile);

}

void OvStream::BuildNode(OvNodePtr* _Node,D3DXFRAME* _Frame)
{
	if (_Frame)
	{
		OvNodePtr kNode = new OvNode;

		if(_Frame->Name)
			kNode->SetName(_Frame->Name);
		else
			kNode->SetName("");

		kNode->SetLocalTransform((OvMatrix)(_Frame->TransformationMatrix));
		if (_Frame->pMeshContainer)
		{
			OvXGeomDataPtr kGeomData	=	new OvXGeomData((D3DXMESHCONTAINER_DERIVE *)(_Frame->pMeshContainer));
			OvGeomObjectPtr kGeomObj	=	new OvGeomObject(kGeomData);
			kNode->AttachChild(kGeomObj);

		}
		_Frame = _Frame->pFrameFirstChild;
		while (_Frame)
		{

			OvNodePtr	kChild = NULL;
			BuildNode(&kChild,_Frame);
			kNode->AttachChild(kChild);
			_Frame = _Frame->pFrameSibling;
		}

		*_Node	=	kNode;
		return ;
	}
	*_Node = NULL;
	return ;
}

void		OvStream::BuildInheritLocalTransform(OvActiveObject* _TopNode)
{

	if(!_TopNode)
		return ;

	unsigned kCound;
	if(_TopNode->IsNode() && (kCound = ((OvNode*)_TopNode)->GetChildCount()))
	{
		OvNode* kNode = (OvNode*)_TopNode;
		for(unsigned i=0 ; i < kCound ; ++i)
		{
			BuildInheritLocalTransform(kNode->GetChildAt(i));
		}
	};

	OvNode*	kParentNode = _TopNode->GetParent();// Olive에서 뽑힐때 Local인줄 알았던게 월드기준 좌표였다.

	OvMatrix kInvMat;
	D3DXMatrixIdentity(&kInvMat);

	if(kParentNode)
	{
		if(kParentNode->GetLocalTransform() != _TopNode->GetLocalTransform())
		{
			kInvMat = kParentNode->GetLocalTransform();
			D3DXMatrixInverse(&kInvMat,0,&kInvMat);
			kInvMat = _TopNode->GetLocalTransform() * kInvMat;
		}
	}


	_TopNode->SetLocalTransform(kInvMat);

};