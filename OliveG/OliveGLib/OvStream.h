#pragma once
#include "OvUtility.h"
namespace Olive
{
	class OvActiveObject;
	class OvNode;
	class OvSamplingAnimData;

	
	class OvClassDllType OvStream :	public OvMemObject
	{
	public:
		OvStream();
		//bool				LoadFromX(const char* _File);
		bool				LoadFromOlive(const char* _File);
		OvActiveObject*		GetObject();
		inline void			ReleaseAllObjects(){m_lpBuildedNode = NULL;};

		void				SaveObject(const char* _pFileName,OvActiveObject* _pObject);
		void				WriteData(const char* _pBuffer,DWORD _dSize);

	protected:
		void				SearchStreamObject(OvActiveObject* _pObject);
		void				BuildNode(OvNodePtr* _Node,D3DXFRAME* _Frame);
		void				BuildInheritLocalTransform(OvActiveObject* _TopNode);
		void				ConvertLocalOliveAnim(OvActiveObject* _Obj,OvSamplingAnimData* _Anim);
	private:
		OvNode*			m_lpBuildedNode;
		OvActiveObject*		m_model;
		list<OvStreamObject*> m_listStreamArray;
		FILE* m_pSaveFile;
	};
}