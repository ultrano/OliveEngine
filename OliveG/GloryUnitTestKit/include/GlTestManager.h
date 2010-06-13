#pragma once

#include <map>
#include <utility>
using namespace std;

class GlBaseTestEnviroment;

class GlTestManager
{
public:

	static GlTestManager* GetInstance();

	void	AddTestCase( GlBaseTestEnviroment* testCase );

	GlBaseTestEnviroment* FindTestCase( const string& envName, const string& caseTitle );

	void	RunAllTest();

private:

	typedef	pair<string,string>	testcase_table_key;
	typedef pair< testcase_table_key, GlBaseTestEnviroment* > testcase_table_element;
	typedef map< testcase_table_key, GlBaseTestEnviroment* > testcase_table;
	testcase_table m_testCaseTable;

};