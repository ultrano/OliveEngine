
#ifdef _DEBUG
#pragma comment( lib, "lua_5_1_4_d" )
#else
#if (_MSC_VER == 1400 )
#pragma comment( lib, "lua_5_1_4_vs2005" )
#else if(_MSC_VER == 1500)
#pragma comment( lib, "lua_5_1_4_vs2008" )
#endif
#endif

extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include "lua_tinker.h"