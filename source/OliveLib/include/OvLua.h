//
//#pragma once
//#include "OvMemObject.h"
//#include "OvAutoPtr.h"
//#include "OvLuaUtil.h"
//
//struct lua_State;
//
//extern "C" {
//	typedef OvInt (*LuaFunctionType)(struct lua_State *pLuaState);
//};
//
//void	OvLuaDefaultErrorHandler(const char* pErrorMsg);
//
//class OvLua : public OvMemObject{
//
//public:
//
//	OvLua();
//
//	OvLua(lua_State* _pLuaState);
//
//	virtual ~OvLua();
//
//public:
//
//	OvBool		RunScript(const char *pFilename);
//	OvBool		RunString(const char *pCommand);
//	const char *GetErrorString(void);
//	OvBool		AddFunction(const char *pFunctionName, LuaFunctionType pFunction);
//	const char *GetStringArgument(OvInt num, const char *pDefault=NULL);
//	double		GetNumberArgument(OvInt num, double dDefault=0.0);
//	void*		GetUserDataArgument(OvInt num, void* dDefault=NULL);
//	void		PushString(const char *pString);
//	void		PushNumber(double value);
//	void		PushUserData(void* pUserData);
//	void		SetErrorHandler(void(*pErrHandler)(const char *pError)) ;
//	lua_State	*GetScriptContext(void);
//	void		ReadyFunction(const char* _pFuncName);
//	OvBool		CallFunction(DWORD _dArgCount);
// 
//	OvBool		ExecuteFunctionWithArg(const char* _pFuncName,const char* _pArgRex = NULL,...);
//
//	template< typename TArg0>
//	OvBool		ExecuteFunction(const char* _pFuncName,TArg0 _tArg0);
//
//	template< typename TArg0,typename TArg1>
//	OvBool		ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1);
//
//	template< typename TArg0,typename TArg1,typename TArg2>
//	OvBool		ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2);
//
//	template< typename TArg0,typename TArg1,typename TArg2,typename TArg3>
//	OvBool		ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3);
//
//	template< typename TArg0,typename TArg1,typename TArg2,typename TArg3,typename TArg4>
//	OvBool		ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3,TArg4 _tArg4);
//
//	template< typename TArg0,typename TArg1,typename TArg2,typename TArg3,typename TArg4,typename TArg5>
//	OvBool		ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3,TArg4 _tArg4,TArg5 _tArg5);
//
//	template< typename TArg0,typename TArg1,typename TArg2,typename TArg3,typename TArg4,typename TArg5,typename TArg6>
//	OvBool		ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3,TArg4 _tArg4,TArg5 _tArg5,TArg6 _tArg6);
//
//
//private:
//
//	struct OvPimple;
//	OvAutoPtr<OvPimple> m_pPimple;
//
//};
//
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(OvInt,PushNumber);
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(DWORD,PushNumber);
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(float,PushNumber);
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(double,PushNumber);
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(size_t,PushNumber);
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(char*,PushString);
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(const char*,PushString);
//OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(void*,PushUserData);
//
//#include "OvLua.inl"