
#include "include_header.h"
#include "OliveValue.h"
#include "OvTexture.h"
#include "OvRenderTexture.h"
#include "OvResourceManager.h"
#include "OvShaderCodeIncluder.h"

GL_TEST_CASE_FUNC( rtti_modify )
{
	OvSingletonPool::StartUp();
	{
		OvXObjectSPtr obj = OvNew OvXObject;
		OvModelSPtr model = OvRTTI_Util::IsTypeOf<OvModel>(obj);
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
GL_TEST_CASE_FUNC( olive_value_addtional_operator_test )
{

	OliveValue::Integer ovint(10);
	OliveValue::Float ovfloat(11);
	OliveValue::Bool ovbool(false);

	int kint = ovint.GetInteger();
	float kfloat = ovfloat.GetFloat();
	bool kbool = ovbool.GetBool();

	kint = ovint;
	kfloat = ovfloat;
	kbool = ovbool;

	kint = 20;
	kfloat = 22;
	kbool = true;

	ovint = kint;
	ovfloat = kfloat;
	ovbool = kbool;

	ovbool.FromString("False");
	ovbool.FromString("True");

}