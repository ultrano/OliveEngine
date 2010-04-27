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

	// 루아스크립트의 경로를 포함한 파일 이름을 쓴다.
	bool		RunScript(const char *pFilename);

	// 곧바로 실행되는 루아 스크립트 언어 입력
	bool		RunString(const char *pCommand);

	// 에러 스트링을 얻는다.
	const char *GetErrorString(void);

	// 루아글루 함수를 루아스테이트로 내보낸다.
	bool		AddFunction(const char *pFunctionName, LuaFunctionType pFunction);

	// 루아 스택에 있는 문자열을 얻어온다.
	const char *GetStringArgument(int num, const char *pDefault=NULL);

	// 루아 스택에 있는 숫자를 얻어온다.
	double		GetNumberArgument(int num, double dDefault=0.0);

	// 루아 스택에 있는 유저데이터를 얻어온다.
	void*		GetUserDataArgument(int num, void* dDefault=NULL);

	// 루아 스택에 문자열을 밀어 넣는다.
	void		PushString(const char *pString);

	// 루아 스택에 숫자를 밀어 넣는다.
	void		PushNumber(double value);

	// 루아 스택에 유저데이터를 밀어 넣는다.
	void		PushUserData(void* pUserData);

	void		SetErrorHandler(void(*pErrHandler)(const char *pError)) {m_pErrorHandler = pErrHandler;}

	lua_State	*GetScriptContext(void)		{return m_pScriptContext;}

private:
	lua_State	*m_pScriptContext;
	void(*m_pErrorHandler)(const char *pError);
};
