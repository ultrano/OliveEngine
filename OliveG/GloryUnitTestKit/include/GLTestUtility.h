#pragma once
#include <string>

class GLException
{
public:
	GLException(const std::string& expMsg):m_expMsg(expMsg){};
	const std::string& GetExceptionMsg(){return m_expMsg;};
	std::string m_expMsg;
};

#define GL_ASSERT( exp ) {if (!(exp)){throw GLException((#exp));}}