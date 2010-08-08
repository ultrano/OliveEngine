template< typename TArg0>
bool		OvLua::ExecuteFunction(const char* _pFuncName,TArg0 _tArg0)
{
	ReadyFunction(_pFuncName);
	OvPushLuaStackData(this,_tArg0);
	CallFunction(1);
	return true;
};
template< typename TArg0,typename TArg1>
bool		OvLua::ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1)
{
	ReadyFunction(_pFuncName);
	OvPushLuaStackData(this,_tArg0);
	OvPushLuaStackData(this,_tArg1);
	CallFunction(2);
	return true;
}
template< typename TArg0,typename TArg1,typename TArg2>
bool		OvLua::ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2)
{
	ReadyFunction(_pFuncName);
	OvPushLuaStackData(this,_tArg0);
	OvPushLuaStackData(this,_tArg1);
	OvPushLuaStackData(this,_tArg2);
	CallFunction(3);
	return true;
}
template< typename TArg0,typename TArg1,typename TArg2,typename TArg3>
bool		OvLua::ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3)
{
	ReadyFunction(_pFuncName);
	OvPushLuaStackData(this,_tArg0);
	OvPushLuaStackData(this,_tArg1);
	OvPushLuaStackData(this,_tArg2);
	OvPushLuaStackData(this,_tArg3);
	CallFunction(4);
	return true;
}
template< typename TArg0,typename TArg1,typename TArg2,typename TArg3,typename TArg4>
bool		OvLua::ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3,TArg4 _tArg4)
{
	ReadyFunction(_pFuncName);
	OvPushLuaStackData(this,_tArg0);
	OvPushLuaStackData(this,_tArg1);
	OvPushLuaStackData(this,_tArg2);
	OvPushLuaStackData(this,_tArg3);
	OvPushLuaStackData(this,_tArg4);
	CallFunction(5);
	return true;
}
template< typename TArg0,typename TArg1,typename TArg2,typename TArg3,typename TArg4,typename TArg5>
bool		OvLua::ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3,TArg4 _tArg4,TArg5 _tArg5)
{
	ReadyFunction(_pFuncName);
	OvPushLuaStackData(this,_tArg0);
	OvPushLuaStackData(this,_tArg1);
	OvPushLuaStackData(this,_tArg2);
	OvPushLuaStackData(this,_tArg3);
	OvPushLuaStackData(this,_tArg4);
	OvPushLuaStackData(this,_tArg5);
	CallFunction(6);
	return true;
}

template< typename TArg0,typename TArg1,typename TArg2,typename TArg3,typename TArg4,typename TArg5,typename TArg6>
bool		OvLua::ExecuteFunction(const char* _pFuncName,TArg0 _tArg0,TArg1 _tArg1,TArg2 _tArg2,TArg3 _tArg3,TArg4 _tArg4,TArg5 _tArg5,TArg6 _tArg6)
{
	ReadyFunction(_pFuncName);
	OvPushLuaStackData(this,_tArg0);
	OvPushLuaStackData(this,_tArg1);
	OvPushLuaStackData(this,_tArg2);
	OvPushLuaStackData(this,_tArg3);
	OvPushLuaStackData(this,_tArg4);
	OvPushLuaStackData(this,_tArg5);
	OvPushLuaStackData(this,_tArg6);
	CallFunction(7);
	return true;
}
