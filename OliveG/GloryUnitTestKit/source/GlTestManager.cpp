#include "GlTestManager.h"
#include "GlBaseTestEnviroment.h"
#include <windows.h>

GlTestManager* GlTestManager::GetInstance()
{
	static GlTestManager staticInstance;
	return &staticInstance;
}
void	GlTestManager::AddTestCase( GlBaseTestEnviroment* testCase )
{
	if ( testCase )
	{
		m_testCaseTable.insert( 
			pair< testcase_table_key, GlBaseTestEnviroment* >(
			testcase_table_key( string(testCase->GetEnvName())
			, string(testCase->GetCaseTitle()) ), testCase
			)
			);
	}
}

GlBaseTestEnviroment* GlTestManager::FindTestCase( const string& envName, const string& caseTitle )
{
	
	testcase_table::iterator tableIter = m_testCaseTable.find
		( 
		testcase_table_key( string(envName), string(caseTitle) )
		);
	if ( tableIter != m_testCaseTable.end() )
	{
		return tableIter->second;
	}
	return NULL;
}
void	GlTestManager::RunAllTest()
{
	testcase_table::iterator tableIter = m_testCaseTable.begin();

	for each( testcase_table_element tableElement in m_testCaseTable)
	{
		GlBaseTestEnviroment* testCase = tableElement.second;

		if (testCase)
		{
			string	testReport = "������ �׽�Ʈ�� �����մϴ�";
			testReport += "\n";
			testReport += "\n";
			testReport += "�׽�Ʈ ȯ�� : " + testCase->GetEnvName();
			testReport += "\n";
			testReport += "�׽�Ʈ Ÿ��Ʋ : " + testCase->GetCaseTitle();
			MessageBox( NULL, testReport.c_str(), "Simple unit testing kit - Glory - ", MB_OK | MB_ICONINFORMATION );

			try
			{
				testCase->SetUp();

				testCase->TestBody();

				testCase->TearDown();
			}
			catch (...)
			{
				testCase->TearDown();
			}
		}
	}
}