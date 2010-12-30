
#include "include_header.h"
#include "OliveValue.h"
#include "OvTexture.h"
#include "OvResourceManager.h"
#include "OvShaderCodeIncluder.h"
#include "OliveDevice.h"
#include "OvObjectFactory.h"
//#include "OvRegisterableProperties.h"

GL_TEST_CASE_FUNC( value_object_test )
{
	OvSingletonPool::StartUp();
	{
		Ov::ValueSPtr test = OvCreateObject( "Value_OvPoint3" );
		OvString str = test->ToString();
		test->FromString( str );
	}
	OvSingletonPool::ShutDown();
}
GL_TEST_CASE_FUNC( rtti_modify )
{
	OvSingletonPool::StartUp();
	{
		OvXObjectSPtr obj = OvNew OvXObject;
		OvModelSPtr model = OvIsTypeOf<OvModel>(obj);
	}
	OvSingletonPool::ShutDown();
}
GL_TEST_CASE_FUNC( excuted_location_test )
{
	OvSingletonPool::StartUp();
	{
		string excuted_location;
		excuted_location.resize( 1024 );
		GetModuleFileName(NULL,(LPCH)excuted_location.c_str(),excuted_location.size());
		excuted_location.data();

		std::string	directory = OvGetDirectoryInFullFilePath( excuted_location );
		directory = OvGetDirectoryInFullFilePath( directory );
		directory = OvGetDirectoryInFullFilePath( directory );
		std::string	file_name = OvGetFileNameInFullFilePath( excuted_location );
		std::string	file_ext = OvGetExtentionInFullFilePath( excuted_location );
	}
	OvSingletonPool::ShutDown();
}