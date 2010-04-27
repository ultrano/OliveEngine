#pragma once

#define OvSingleton_IMPL(classname)\
	classname*	classname::Instance()\
	{\
	static classname skSingletonInstance;\
	return &skSingletonInstance;\
};\



//! 싱글톤 매크로를 사용하면 기본 생성자와 기본소멸자에 대한 구현이 자동 선언된다.(그러므로 정의해줘야 한다.)
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
	OvAssertMsg("등록되지 않은 싱글톤 입니다.\n"\
	"[OvSingletonContextList]에 등록된 싱글톤에 한하여\n"\
	"[OvSingletonPool]의 가동과 함께 사용이 가능합니다.");\
	}\
	else\
	{\
	OvAssertMsg("[OvSingletonPool]이 가동 되지 않았습니다.\n"\
	"[OvSingletonPool::StartUp()]을 호출해야 싱글톤들이 사용가능합니다.");\
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
	OvAssertMsg("["#classname"]에 대한 비정상적인\n"\
				"싱글톤 생성시도가 포착됐습니다.\n"\
				"[OvSingletonPool::StartUp()]을 이용한\n"\
				"싱글톤 초기화를 해주시기 바랍니다.");\
	}\
}\
	classname::~classname()\
{\
	Singleton_TerminateProcessing();\
	__msh__pSingletonInstance = NULL;\
}
