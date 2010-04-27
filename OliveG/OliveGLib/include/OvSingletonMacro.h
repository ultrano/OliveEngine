#pragma once

#define OvSingleton_IMPL(classname)\
	classname*	classname::Instance()\
	{\
	static classname skSingletonInstance;\
	return &skSingletonInstance;\
};\



//! �̱��� ��ũ�θ� ����ϸ� �⺻ �����ڿ� �⺻�Ҹ��ڿ� ���� ������ �ڵ� ����ȴ�.(�׷��Ƿ� ��������� �Ѵ�.)
#define OvSingleton_DECL(classname)\
protected:\
	classname();\
	virtual ~classname();\
public:\
	static classname*	Instance();

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

#define OvSingletonEx_DECL(classname)\
	friend class OvSingletonContextList;\
public:\
	static classname* GetInstance();\
private:\
	classname();\
	~classname();\
	void	Singleton_InitializeProcessing();\
	void	Singleton_TerminateProcessing();\
private:\
	static classname* __msh__pSingletonInstance;


#define OvSingletonEx_IMPL(classname)\
	classname* classname::__msh__pSingletonInstance = NULL;\
	classname* classname::GetInstance()\
{\
	if (__msh__pSingletonInstance)\
	{\
	return __msh__pSingletonInstance;\
	}\
	else if(OvSingletonPool::IsPoolStartedUp())\
	{\
	OvAssertMsg("��ϵ��� ���� �̱��� �Դϴ�.\n"\
	"[OvSingletonContextList]�� ��ϵ� �̱��濡 ���Ͽ�\n"\
	"[OvSingletonPool]�� ������ �Բ� ����� �����մϴ�.");\
	}\
	else\
	{\
	OvAssertMsg("[OvSingletonPool]�� ���� ���� �ʾҽ��ϴ�.\n"\
	"[OvSingletonPool::StartUp()]�� ȣ���ؾ� �̱������ ��밡���մϴ�.");\
	}\
	return NULL;\
};\
	classname::classname()\
{\
	if(NULL == __msh__pSingletonInstance)\
	{\
		__msh__pSingletonInstance = this;\
		Singleton_InitializeProcessing();\
	}\
	else\
	{\
	OvAssertMsg("["#classname"]�� ���� ����������\n"\
				"�̱��� �����õ��� �����ƽ��ϴ�.\n"\
				"[OvSingletonPool::StartUp()]�� �̿���\n"\
				"�̱��� �ʱ�ȭ�� ���ֽñ� �ٶ��ϴ�.");\
	}\
}\
	classname::~classname()\
{\
	Singleton_TerminateProcessing();\
	__msh__pSingletonInstance = NULL;\
}
