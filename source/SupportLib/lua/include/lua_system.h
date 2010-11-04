
#ifdef _DEBUG
#pragma comment( lib, "lua_5_1_4_d" )
#else
#pragma comment( lib, "lua_5_1_4" )
#endif

extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include "lua_tinker.h"