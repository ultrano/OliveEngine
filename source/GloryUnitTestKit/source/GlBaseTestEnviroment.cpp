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

void	GlBaseTestEnviroment::SetEnvName( const string& enviromentName )
{
	m_enviromentName = enviromentName;
}
void	GlBaseTestEnviroment::SetCaseTitle( const string& testCaseTitle )
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