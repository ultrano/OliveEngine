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
	OliveValue::Value* extraValue = NULL;

	objTest->RegisterExtraProperty( "Name", OliveValue::ValueFactory( "String" ) );
	objTest->RegisterExtraProperty( "Birth", OliveValue::ValueFactory( "String" ) );
	objTest->RegisterExtraProperty( "Gender", OliveValue::ValueFactory( "String" ) );
	objTest->RegisterExtraProperty( "Location", OliveValue::ValueFactory( "String" ) );


	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Name" ) );
	extraValue->SetValue("Ultrano");
	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Birth" ) );
	extraValue->SetValue("1987/06/26");
	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Gender" ) );
	extraValue->SetValue("male");
	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Location" ) );
	extraValue->SetValue("daegu");


	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Name" ) );
	OutputDebugString(extraValue->GetValue().c_str());
	OutputDebugString("\n");
	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Birth" ) );
	OutputDebugString(extraValue->GetValue().c_str());
	OutputDebugString("\n");
	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Gender" ) );
	OutputDebugString(extraValue->GetValue().c_str());
	OutputDebugString("\n");
	GL_ASSERT( extraValue = objTest->FindExtraProperty( "Location" ) );
	OutputDebugString(extraValue->GetValue().c_str());
	OutputDebugString("\n");


	OvStorage kStorage;

	OvObjectProperties kObjStore;
	kStorage.ExtractProperty(objTest,kObjStore);
	kStorage.RestoreObject(kObjStore);
	
	kStorage.ReadProperty("../../export/testprop.xml");
};

int	APIENTRY	WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int)
{
	GL_RUN_ALL_TEST();
};
