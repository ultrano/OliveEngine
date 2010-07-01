#include "GlTestManager.h"
#include "GlBaseTestEnviroment.h"
#include "GLTestUtility.h"
#include <string>
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
			string	testReport = "Simple unit testing kit - Glory - ";
			testReport += "\n";
			testReport += "������ �׽�Ʈ�� �����մϴ�";
			testReport += "\n";
			testReport += "\n";
			testReport += "�׽�Ʈ ȯ�� : " + testCase->GetEnvName();
			testReport += "\n";
			testReport += "�׽�Ʈ Ÿ��Ʋ : " + testCase->GetCaseTitle();
			testReport += "\n";
			OutputDebugString(testReport.c_str());

			try
			{
				testCase->SetUp();

				testCase->TestBody();

				testCase->TearDown();

				OutputDebugString("���������� �Ϸ�.\n");
			}
			catch ( GLException& e )
			{
				testCase->TearDown();
				std::string expMsg = e.GetExceptionMsg();
				OutputDebugString(expMsg.c_str());
				OutputDebugString("\n");
			}
		}
	}
}