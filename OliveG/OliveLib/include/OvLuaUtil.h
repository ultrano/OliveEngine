
// 코딩의 시간을 줄여줄 몇가지 템플릿 및 매크로의 도움을 받는다.
// 함수템플릿의 중복적재를 쓰면 더 간단하겠지만 뭔가 충돌이 난다.
// 그래서 클레스의 부분특수화를 이용해 약간 경유 했다.

class OvLua;
template<typename TArg >
void	OvPushLuaStackData(OvLua* _pLua,TArg _tArg)
{
	OvLuaTypeSelector<TArg>(_pLua).PushData(_tArg);
};

template<typename TArg>
struct OvLuaTypeSelector;

#define OLIVE_LUA_SELECT_PUSH_METHOD_MACRO(TYPENAME,PUSHMETHODNAME) template<> \
struct OvLuaTypeSelector<TYPENAME>\
{\
	OvLuaTypeSelector(OvLua* _pLua){m_pLua = _pLua;};\
	void PushData(TYPENAME _tArg){m_pLua->PUSHMETHODNAME(_tArg);};\
	OvLua* m_pLua;\
}