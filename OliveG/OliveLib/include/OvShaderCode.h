#pragma once
#include "OvResource.h"
#include <string>
using namespace std;

OvREF_POINTER(OvShaderCode);
class OvShaderCode : public OvResource
{
	OvRTTI_DECL( OvShaderCode );
public:
	OvShaderCode( const string& code);
	const string&	GetCodeString();
	void*			GetCodeBuffer();
	size_t			GetCodeSize();

private:
	string m_code;
};