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
			OvAssertMsg("����������\n"
				"�̱��� �����õ��� �����ƽ��ϴ�.\n"
				"[OvSingletonPool::StartUp()]�� �̿���\n"
				"�̱��� �ʱ�ȭ�� ���ֽñ� �ٶ��ϴ�.");
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
			OvAssertMsg("��ϵ��� ���� �̱��� �Դϴ�.\n"
				"[OvSingletonContextList]�� ��ϵ� �̱��濡 ���Ͽ�\n"
				"[OvSingletonPool]�� ������ �Բ� ����� �����մϴ�.");
		}
		else
		{
			OvAssertMsg("[OvSingletonPool]�� ���� ���� �ʾҽ��ϴ�.\n"
				"[OvSingletonPool::StartUp()]�� ȣ���ؾ� �̱������ ��밡���մϴ�.");
		}
		return 0;
	};
};