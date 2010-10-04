#pragma once
#include "OvMacro.h"
template<class Type_0>
class OvSingletonBase
{
private:
	static Type_0*& _standalone_instance_pointer(){static Type_0* static_pointer( 0 );return static_pointer;};
	friend class OvSingletonContextList;
protected:
	OvSingletonBase()
	{
		if( 0 == _standalone_instance_pointer())
		{
			_standalone_instance_pointer() = static_cast<Type_0*>( this );
			//Singleton_InitializeProcessing();
		}
		else
		{
			OvAssertMsg("비정상적인\n"
				"싱글톤 생성시도가 포착됐습니다.\n"
				"[OvSingletonPool::StartUp()]을 이용한\n"
				"싱글톤 초기화를 해주시기 바랍니다.");
		}
	}
	virtual ~OvSingletonBase()
	{
		_standalone_instance_pointer() = 0 ;\
	}
public:
	static Type_0*	GetInstance()
	{
		if (_standalone_instance_pointer())
		{
			return _standalone_instance_pointer();
		}
		else if(OvSingletonPool::IsPoolStartedUp())
		{
			OvAssertMsg("등록되지 않은 싱글톤 입니다.\n"
				"[OvSingletonContextList]에 등록된 싱글톤에 한하여\n"
				"[OvSingletonPool]의 가동과 함께 사용이 가능합니다.");
		}
		else
		{
			OvAssertMsg("[OvSingletonPool]이 가동 되지 않았습니다.\n"
				"[OvSingletonPool::StartUp()]을 호출해야 싱글톤들이 사용가능합니다.");
		}
		return 0;
	};
};