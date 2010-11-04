#include "GlBaseTestEnviroment.h"
#include "GlTestManager.h"

GlBaseTestEnviroment::GlBaseTestEnviroment()
{

}

GlBaseTestEnviroment::~GlBaseTestEnviroment()
{

}


void	GlBaseTestEnviroment::SetUp()
{
};
void	GlBaseTestEnviroment::TearDown()
{
};

void	GlBaseTestEnviroment::SetEnvName( const char* enviromentName )
{
	m_enviromentName = enviromentName;
}
void	GlBaseTestEnviroment::SetCaseTitle( const char* testCaseTitle )
{
	m_testCaseTitle = testCaseTitle;
}
const string&	GlBaseTestEnviroment::GetEnvName()
{
	return m_enviromentName;
}
const string&	GlBaseTestEnviroment::GetCaseTitle()
{
	return m_testCaseTitle;
}