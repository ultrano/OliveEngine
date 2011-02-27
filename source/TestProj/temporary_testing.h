#include "include_header.h"
#include "OliveValue.h"
#include "OvTexture.h"
#include "OvResourceManager.h"
#include "OvShaderCodeIncluder.h"
#include "OliveDevice.h"

GL_TEST_CASE_FUNC( olive_value_streaming_test )
{
	OvSingletonPool::StartUp();
	{
		OliveValue::Table table;
		OliveValue::Table table2;
		OliveValue::Table table3;

		OliveValue::Integer integer0( 100 );
		OliveValue::String  str("六六六腎釭?");
		OliveValue::Color   col(OvColor(255,255,255,255));

		table.Insert( "integer", integer0 );
		table.Insert( "string", str );
		table.Insert( "color", col );

		table2.CopyFrom( table );
		table2.Insert( "table", table );

		OvString tostr = table2.ToString();
		tostr = table2.ToString();

		table3.CopyFrom( table2 );
		tostr = table3.ToString();
	}
	OvSingletonPool::ShutDown();
}
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
GL_TEST_CASE_FUNC( olive_value_test )
{
	OliveDevice::EngineOn();
	OvString exp;
	{
		OliveValue::Bool val( OvBool( false ) );
		exp = val.ToString();
		exp = "true";
		val.FromString( exp );
		OvBool val2 = val;
	}
	{
		OliveValue::Float  val( OvFloat( 1357.548f ) );
		exp = val.ToString();
		exp = "112.119";
		val.FromString( exp );
		OvFloat val2 = val;
	}
	{
		OliveValue::Point2 val( OvPoint2( 123.123f, 456.456f ) );
		exp = val.ToString();
		exp = "111.111,222.222";
		val.FromString( exp );
		OvPoint2 val2 = val;
	}
	{
		OliveValue::Point3 val( OvPoint3( 987.987f, 654.654f, 321.321f ) );
		exp = val.ToString();
		exp = "111.111,222.222,333.333";
		val.FromString( exp );
		OvPoint3 val2 = val;
	}
	{
		OliveValue::Quaternion val( OvQuaternion( 123.123f, 456.456f, 789.789f, 753.753f ) );
		exp = val.ToString();
		exp = "111.111,222.222,333.333,444.444";
		val.FromString( exp );
		OvQuaternion val2 = val;
	}
	{
		OliveValue::Integer val( OvInt( 123456789 ) );
		exp = val.ToString();
		exp = "987654321";
		val.FromString( exp );
		OvInt val2 = val;
	}
	{
		OliveValue::String val( OvString( "六六?六六六番六六六" ) );
		exp = val.ToString();
		exp = "滲п嫁 曉";
		val.FromString( exp );
		OvString val2 = val;
	}
	{
		OliveValue::ObjectID val( OvObjectID( 119 ) );
		exp = val.ToString();
		exp = "911";
		val.FromString( exp );
		OvObjectID val2 = val;
	}
	{
		OliveValue::UserData val ( (void*)NULL ) ;
		exp = val.ToString();
		exp = "11111";
		val.FromString( exp );
		void* val2 = val;
	}
	{
		OliveValue::Color val( OvColor( 234, 111, 231, 255 ) ) ;
		exp = val.ToString();
		exp = "a:1,r:2,g:3,b:4";
		val.FromString( exp );
		OvColor val2 = val;
	}

	{
		OliveValue::Table table;
		OliveValue::Table table2;
		OliveValue::Table table3;
		
		OliveValue::Integer integer0( 100 );
		OliveValue::String  str("六六六腎釭?");
		OliveValue::Color   col(OvColor(255,255,255,255));

		table.Insert( "integer", integer0 );
		table.Insert( "string", str );
		table.Insert( "color", col );

		table2.CopyFrom( table );
		table2.Insert( "table", table );

		OvString tostr = table2.ToString();
		tostr = table2.ToString();
		
		table3.CopyFrom( table2 );
		tostr = table3.ToString();

	}
	OliveDevice::EngineOff();

}