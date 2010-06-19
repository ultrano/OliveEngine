#include "include_header.h"

GL_ENVIROMENT(OliveLibTest)
{
	GL_ENV_SET_UP
	{
		OvSingletonPool::StartUp();
#ifdef _WINDOWS
#ifdef _DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

		_CrtSetBreakAlloc(2106);
#endif
#endif


	};
	GL_ENV_TEAR_DOWN
	{
		OvSingletonPool::ShutDown();
	}
};

GL_TEST_CASE_ENV( OliveLibTest, property_bag_test )
{
	OvXNodeSPtr nodeTest = new OvXNode;
	OliveValue::Value* extraValue = NULL;

	nodeTest->RegisterExtraProperty( "Name", OliveValue::ValueFactory( "String" ) );
	nodeTest->RegisterExtraProperty( "Birth", OliveValue::ValueFactory( "String" ) );
	nodeTest->RegisterExtraProperty( "Gender", OliveValue::ValueFactory( "String" ) );
	nodeTest->RegisterExtraProperty( "Location", OliveValue::ValueFactory( "String" ) );
	nodeTest->RegisterExtraProperty( "Coordination", OliveValue::ValueFactory( "Point3" ) );

	GL_ASSERT( extraValue = nodeTest->FindExtraProperty( "Name" ) );
	extraValue->SetValue("Ultrano");
	GL_ASSERT( extraValue = nodeTest->FindExtraProperty( "Birth" ) );
	extraValue->SetValue("1987/06/26");
	GL_ASSERT( extraValue = nodeTest->FindExtraProperty( "Gender" ) );
	extraValue->SetValue("male");
	GL_ASSERT( extraValue = nodeTest->FindExtraProperty( "Location" ) );
	extraValue->SetValue("daegu");
	GL_ASSERT( extraValue = nodeTest->FindExtraProperty( "Coordination" ) );
	extraValue->SetValue("1,2,3");

	OvObjectSPtr childObject = NULL;
	childObject = new OvCamera;
	childObject->SetName("first");
	nodeTest->AttachChild( childObject );

	childObject = new OvCamera;
	childObject->SetName("second");
	nodeTest->AttachChild( childObject );


	childObject = new OvCamera;
	childObject->SetName("third");
	nodeTest->AttachChild( childObject );

	OvStorage kStorage;


	OvObjectCollector streamObject;
	streamObject.AddObject(nodeTest);
	nodeTest = NULL;
	kStorage.Save("../../export/testprop.xml", streamObject);
 	streamObject.Clear();
	kStorage.Load("../../export/testprop.xml", streamObject);
	//streamObject.Clear();
// 	kStorage.Save("../../export/testprop2.xml", streamObject);
// 	streamObject.Clear();
};

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GL_RUN_ALL_TEST();
};
