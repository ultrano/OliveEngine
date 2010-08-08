//#pragma once
//#include "OvAutoPtr.h"
//
//#include "OvSingleton.h"
//struct lua_State;
//
//class OvCoreCommander : public OvSingletonBase< OvCoreCommander >
//{
//
//public:
//	OvCoreCommander();
//	~OvCoreCommander();
//
//	void		Initialize();
//
//	lua_State*	GetCoreLuaState();
//
//	bool		ExcuteCommand(const char* pCommand);
//
//	bool		ExcuteScriptFile(const char* pFilePath);
//
//private:
//
//	//! Member Values (Ensconsed for encapsulation)
//	//! Application can access member only using get,set interface
//	struct OvPimple;
//	OvAutoPtr<OvPimple> m_pPimple;
//};
//
//bool	OvExitProgram();