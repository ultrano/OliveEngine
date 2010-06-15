#include "include_header.h"

GL_ENVIROMENT(OliveLibTest)
{
	GL_ENV_SET_UP
	{
		OvSingletonPool::StartUp();
	};
	GL_ENV_TEAR_DOWN
	{
		OvSingletonPool::ShutDown();
	}
};

GL_TEST_CASE_ENV( OliveLibTest, property_bag_test )
{
	OvObjectSPtr objTest = new OvCamera;
	objTest->SetName("��ʹ� ����");

	OvRTTI_Util::IsKindOf<OvObject>(objTest);

	string kstrName = objTest->GetName();

	OvStorage kStorage;

	OvObjectProperties kObjStore;
	kStorage.ExtractProperty(objTest,kObjStore);
	kStorage.RestoreObject(kObjStore);

};
GL_TEST_CASE_ENV( OliveLibTest, simple_testing )
{
	OvMessageBox("�ų�?","�̰͵� �Ŵ°ǰ�?!");
};

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GlTestManager::GetInstance()->RunAllTest();
};
