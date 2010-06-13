#include "include_header.h"

GL_TEST_CASE_FUNC( simple_testing )
{
	OvSingletonPool::StartUp();
	{		
	OvObjectSPtr objTest = new OvCamera;
	objTest->SetName("써너버 비취");

	OvRTTI_Util::IsKindOf<OvObject>(objTest);

	string kstrName = objTest->GetName();

	OvStorage kStorage;

	OvObjectProperties kObjStore;
	kStorage.ExtractProperty(objTest,kObjStore);
	kStorage.RestoreObject(kObjStore);

	}
	OvSingletonPool::ShutDown();
};
GL_TEST_CASE_FUNC( simple_testing_again )
{
	OvMessageBox("돼나?","이것도 돼는건가?!");
	throw "lskfjaslkfja";
	OvMessageBox("여긴 쌩까는건가?","오긴오냐?");
};

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GlTestManager::GetInstance()->RunAllTest();
};
