#include "include_header.h"

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	OvSingletonPool::StartUp();
	{

		OvXNodeSPtr kpNode = new OvXNode;
		kpNode->SetName("써너버 비취");
		
		string kstrName = kpNode->GetName();

		kpNode->SetScale(5);
		kpNode->SetTranslate(10,11,12);
		kpNode->Update(0);

		OvStorage kStorage;

		OvObjectStore kObjStore;
		kStorage.ExtractProperty(kpNode,kObjStore);
		kStorage.RestoreObject(kObjStore);

	}
	OvSingletonPool::ShutDown();
};
