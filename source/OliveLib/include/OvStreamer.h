//#pragma once
//#include "OvMemObject.h"
//#include "OvAutoPtr.h"
//#include "OvSmartPointer.h"
//#include "tinyxml.h"
//#include "OvObject.h"
//
//class OvObjectData;
//
//class OvStreamer : public OvMemObject
//{
//public:
//
//	OvStreamer();
//	~OvStreamer();
//
//	void	Store(const char* pFile);
//	void	Restore(const char* pFile);
//
////private:
//
//	void	StoreObject	 (OvObjectSPtr pObj);
//	void	RestoreObject(OvObjectData& rStore);
//
//	bool	ExtractProperty	(OvObjectSPtr pObj,OvObjectData& rStore);
//	bool	InjectProperty	(OvObjectSPtr pObj,OvObjectData& rStore);
//
//	void	WriteProperty(OvObjectData& rStore);
//	//void	ReadStore(OvObjectSPtr _pObj);
//
//	//OvObjectSPtr RestoreRelationshipTable();
//
//private:
//
//	struct OvPimple;
//	OvAutoPtr< OvPimple> m_pPimple;
//
//};
