#pragma once
#include <string>
using namespace std;

class GlBaseTestEnviroment
{
public:

	GlBaseTestEnviroment();
	virtual ~GlBaseTestEnviroment();

public:

	virtual void	SetUp();
	virtual void	TearDown();

	virtual void	TestBody() = 0;

public:

	void	SetEnvName( const char* );
	void	SetCaseTitle( const char* );

	const string&	GetEnvName();
	const string&	GetCaseTitle();

private:

	std::string	m_enviromentName;

	std::string	m_testCaseTitle;

};

//_enviroment_name( const std::string& envName, const std::string& caseTitle ):GlBaseTestEnviroment(envName,caseTitle){};

#define GL_TEST_ENVIROMENT( _enviroment_name ) \
class _enviroment_name : public GlBaseTestEnviroment

#define GL_ENV_SET_UP \
virtual void	SetUp() override

#define GL_ENV_TEAR_DOWN \
virtual void	TearDown() override


#define	GL_TEST_CASE_ENV( _enviroment, _testcase_title ) \
class _enviroment##_##_testcase_title : public _enviroment\
{\
	virtual void	TestBody() override ;\
};\
struct _enviroment##_##_testcase_title##_TestCaseRegister\
{\
	_enviroment##_##_testcase_title m_testCaseInstance;\
	\
	_enviroment##_##_testcase_title##_TestCaseRegister()\
	{\
		m_testCaseInstance.SetEnvName(#_enviroment);\
		m_testCaseInstance.SetCaseTitle(#_testcase_title);\
		GlTestManager::GetInstance()->AddTestCase( &m_testCaseInstance );\
	}\
} _enviroment##_##_testcase_title##_TestCaseRegister##_Instance;\
void	_enviroment##_##_testcase_title::TestBody()


GL_TEST_ENVIROMENT(BasicTestingEnviroment)
{
	GL_ENV_SET_UP
	{
	};

	GL_ENV_TEAR_DOWN
	{
	};
};

#define GL_TEST_CASE_FUNC( _testcase_title ) \
	GL_TEST_CASE_ENV( BasicTestingEnviroment, _testcase_title )