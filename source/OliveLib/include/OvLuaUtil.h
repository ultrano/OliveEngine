
// �ڵ��� �ð��� �ٿ��� ��� ���ø� �� ��ũ���� ������ �޴´�.
// �Լ����ø��� �ߺ����縦 ���� �� �����ϰ����� ���� �浹�� ����.
// �׷��� Ŭ������ �κ�Ư��ȭ�� �̿��� �ణ ���� �ߴ�.

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