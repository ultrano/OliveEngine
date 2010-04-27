#pragma once

#ifndef NULL
#define NULL 0
#endif

extern "C" {
#include "lua.h"
}
struct lua_State;

#define LuaGlue extern "C" int
extern "C" {
typedef int (*LuaFunctionType)(struct lua_State *pLuaState);
};

class cLua
{
public:
	cLua();
	cLua(lua_State* pWrapState);
	virtual ~cLua();

	// ��ƽ�ũ��Ʈ�� ��θ� ������ ���� �̸��� ����.
	bool		RunScript(const char *pFilename);

	// ��ٷ� ����Ǵ� ��� ��ũ��Ʈ ��� �Է�
	bool		RunString(const char *pCommand);

	// ���� ��Ʈ���� ��´�.
	const char *GetErrorString(void);

	// ��Ʊ۷� �Լ��� ��ƽ�����Ʈ�� ��������.
	bool		AddFunction(const char *pFunctionName, LuaFunctionType pFunction);

	// ��� ���ÿ� �ִ� ���ڿ��� ���´�.
	const char *GetStringArgument(int num, const char *pDefault=NULL);

	// ��� ���ÿ� �ִ� ���ڸ� ���´�.
	double		GetNumberArgument(int num, double dDefault=0.0);

	// ��� ���ÿ� �ִ� ���������͸� ���´�.
	void*		GetUserDataArgument(int num, void* dDefault=NULL);

	// ��� ���ÿ� ���ڿ��� �о� �ִ´�.
	void		PushString(const char *pString);

	// ��� ���ÿ� ���ڸ� �о� �ִ´�.
	void		PushNumber(double value);

	// ��� ���ÿ� ���������͸� �о� �ִ´�.
	void		PushUserData(void* pUserData);

	void		SetErrorHandler(void(*pErrHandler)(const char *pError)) {m_pErrorHandler = pErrHandler;}

	lua_State	*GetScriptContext(void)		{return m_pScriptContext;}

private:
	lua_State	*m_pScriptContext;
	void(*m_pErrorHandler)(const char *pError);
};
