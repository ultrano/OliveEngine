#include "include_header.h"

GL_TEST_CASE_FUNC( simple_testing )
{
	OvSingletonPool::StartUp();
	{		
	OvObjectSPtr objTest = new OvCamera;
	objTest->SetName("��ʹ� ����");

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
	OvMessageBox("�ų�?","�̰͵� �Ŵ°ǰ�?!");
	throw "lskfjaslkfja";
	OvMessageBox("���� �߱�°ǰ�?","�������?");
};

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GlTestManager::GetInstance()->RunAllTest();
};
