
#include "include_header.h"
#include "OvUtility.h"
#include <regex>

GL_TEST_CASE_FUNC( container_utility_test )
{
	vector<int> vec;
	vec.push_back( 1 );
	vec.push_back( 2 );
	vec.push_back( 3 );
	vec.push_back( 4 );
	vec.push_back( 3 );
	vec.push_back( 2 );
	vec.push_back( 1 );

	vector<short> vec2 = OU::container::convert<vector<short>>( vec );;
	list<int> lst = OU::container::convert<list<int>>( vec );

	OU::container::remove( vec, 1 );

}

GL_TEST_CASE_FUNC( string_utility_test )
{
	OvString str = "d:\\project_olive\\source\\testproj\\utility_test.h";
	OvString newstr = OU::string::replace( str, "\\","");
}