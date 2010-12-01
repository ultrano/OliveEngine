//#include "OvLua.h"
//#include "cLua.h"
//#include <vector>
//
//struct OvLua::OvPimple : OvMemObject
//{
//	OvPimple(){};
//	OvPimple(lua_State* _pLuaState):mLuaInstance(_pLuaState)
//	{
//	}
//	cLua	mLuaInstance;
//};
//
//void	OvLuaDefaultErrorHandler(const char* pErrorMsg)
//{
//	OvMessageBox(pErrorMsg,"OvLuaDefaultErrorHandler");
//};
//
//OvLua::OvLua():m_pPimple(OvNew OvPimple)
//{
//	SetErrorHandler(OvLuaDefaultErrorHandler);
//};
//OvLua::OvLua(lua_State* _pLuaState):m_pPimple(OvNew OvPimple(_pLuaState))
//{
//	SetErrorHandler(OvLuaDefaultErrorHandler);
//}
//OvLua::~OvLua(){
//};
//
//bool		OvLua::RunScript(const char *pFilename){
//	return m_pPimple->mLuaInstance.RunScript(pFilename);
//};
//
//bool		OvLua::RunString(const char *pCommand){
//	return m_pPimple->mLuaInstance.RunString(pCommand);
//};
////
////void		OvLua::ReadyFunction(const char* _pFuncName,int _iArgCount,int _iReturnCount){
////
////	lua_getglobal(GetScriptContext(),_pFuncName);
////
////	m_iArgCount = _iArgCount;
////	m_iReturnCount = _iReturnCount;
////
////	m_bIsFunctionReady = true;
////
////};
////
////void		OvLua::RunFunction(){
////
////	if(m_bIsFunctionReady){
////		lua_call(GetScriptContext(),m_iArgCount,m_iReturnCount);
////	}
////
////	m_bIsFunctionReady = false;
////
////};
//
//bool		OvLua::ExecuteFunctionWithArg(const char* _pFuncName,const char* _pArgRex,...)
//{
//	lua_getglobal(GetScriptContext(),_pFuncName);
//	vector<OvString> kArgTypeArray;
//	if (_pArgRex)
//	{
//		char pArgRexCopy[256] = {0,};
//		strcpy(pArgRexCopy,_pArgRex);
//		char* kpTok = strtok(pArgRexCopy,",");
//
//		va_list kvaArgs;
//		va_start(kvaArgs,_pArgRex);
//
//		while (kpTok != NULL)
//		{
//			kArgTypeArray.push_back(kpTok);
//			kpTok = strtok(NULL,",");
//		}
//
//
//
//		for(size_t i=0;i<kArgTypeArray.size();++i)
//		{
//			if (kArgTypeArray[i] == "%s")
//			{
//				char* kpPushStr = va_arg(kvaArgs,char*);
//				PushString(kpPushStr);
//			}else if(kArgTypeArray[i] == "%p")
//			{
//				void* kpPushUdata = va_arg(kvaArgs,void*);
//				PushUserData(kpPushUdata);
//			}
//			else if(kArgTypeArray[i] == "%d")
//			{
//				int kpPushNum = va_arg(kvaArgs,int);
//				PushNumber(kpPushNum);
//			}else if(kArgTypeArray[i] == "%f")
//			{
//				float kpPushNum = va_arg(kvaArgs,float);
//				PushNumber(kpPushNum);
//			}
//		}
//
//		va_end(kvaArgs);
//	}
//
//	if (!lua_pcall(GetScriptContext(),kArgTypeArray.size(),LUA_MULTRET,0))
//	{
//		OvAssertMsg(GetErrorString());
//	}
//	return true;
//}
//
//const char *OvLua::GetErrorString(void)
//{
//	return m_pPimple->mLuaInstance.GetErrorString();
//};
//
//bool		OvLua::AddFunction(const char *pFunctionName, LuaFunctionType pFunction)
//{
//	return m_pPimple->mLuaInstance.AddFunction(pFunctionName,pFunction);
//};
//
//const char *OvLua::GetStringArgument(int num, const char *pDefault)
//{
//	return m_pPimple->mLuaInstance.GetStringArgument(num,pDefault);
//};
//
//double		OvLua::GetNumberArgument(int num, double dDefault)
//{
//	return m_pPimple->mLuaInstance.GetNumberArgument(num,dDefault);
//};
//
//void*		OvLua::GetUserDataArgument(int num, void* dDefault)
//{
//	return m_pPimple->mLuaInstance.GetUserDataArgument(num,dDefault);
//}
//
//void		OvLua::PushString(const char *pString)
//{
//	m_pPimple->mLuaInstance.PushString(pString);
//};
//
//void		OvLua::PushNumber(double value)
//{
//	m_pPimple->mLuaInstance.PushNumber(value);
//};
//
//void		OvLua::PushUserData(void* pUserData)
//{
//	m_pPimple->mLuaInstance.PushUserData(pUserData);
//}
//
//void		OvLua::SetErrorHandler(void(*pErrHandler)(const char *pError)) 
//{
//	m_pPimple->mLuaInstance.SetErrorHandler(pErrHandler);
//}
//
//lua_State	*OvLua::GetScriptContext(void)		
//{
//	return m_pPimple->mLuaInstance.GetScriptContext();
//}
//
//void		OvLua::ReadyFunction(const char* _pFuncName)
//{
//	lua_getglobal(GetScriptContext(),_pFuncName);
//}
//bool		OvLua::CallFunction(DWORD _dArgCount)
//{
//	if (!lua_pcall(GetScriptContext(),_dArgCount,LUA_MULTRET,0))
//	{
//		OvAssertMsg(GetErrorString());
//		return false;
//	}
//	return true;
//}