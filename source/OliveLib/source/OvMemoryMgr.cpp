// 2008 12 11
// maker : Han,sang woon
#define OvExportDll
#include "OvMemoryMgr.h"
#include "OvMemoryPool.h"
#include "OvThreadSync.h"

struct OvMemoryPoolList 
{
	OvMemoryPoolList*	mNext;
	OvMemoryPool		mMemPool;
	void _constructor(std::size_t _size_type)
	{
		mNext = NULL;
		mMemPool._constructor(_size_type);
	}
	void _destructor()
	{
		mMemPool._destructor();
	}
};


OvMemoryMgr::OvMemoryMgr()
{
	m_pMemoryPoolList = NULL;
	InitializeCriticalSection( &m_section );
}
OvMemoryMgr::~OvMemoryMgr()
{
	OvMemoryPoolList* k_list = m_pMemoryPoolList;
	OvMemoryPoolList* k_target = NULL;
	do 
	{
		k_target = k_list;

		k_list = k_list->mNext;

		k_target->_destructor();
		free((void*)k_target);

	} while (k_list);
	m_pMemoryPoolList = NULL;
	DeleteCriticalSection( &m_section );

}

OvMemoryPool* OvMemoryMgr::get_pool(std::size_t _size_type)
{
	OvMemoryPoolList* k_search = NULL;
	OvMemoryPool*	  k_mem_pool = NULL;
	// 모든 메모리풀리스트를 뒤진다.
	for (k_search = m_pMemoryPoolList;k_search;k_search = k_search->mNext)
	{
		// 리스트가 관리하는 메모리풀의 주소를 준다.
		k_mem_pool = &(k_search->mMemPool);
		// 이 메모리풀이 요청된 크기의 메모리들을 담을수 있는 메모리풀인지 검사한다.
		if (k_mem_pool->get_size_type() == _size_type)
		{
			//맞으면 리턴.
			return k_mem_pool;
		}
	}
	// 여기까지 왔단건 요청크기의 메모리들을 담는 메모리풀이 없다는것이므로
	// 새로 만들어서 리턴.
	return add_memory_pool(_size_type);
}

OvMemoryPool*		  OvMemoryMgr::add_memory_pool(std::size_t _size_type)
{
	OvMemoryPoolList*	k_pool_list = NULL;

	// 인수크기의 메모리들을 담는 메모리풀을 만든다.
	// 메모리 관리 객체들은 new나 ::new 대신 malloc으로 통일 한다.
	// 그렇기 때문에 명시적인 생성자와 소멸자를 대신 두었다.

	k_pool_list	=	(OvMemoryPoolList*)malloc(sizeof(BYTE)*sizeof(OvMemoryPoolList));
	if (k_pool_list)
	{
		k_pool_list->_constructor(_size_type);

		// 새로 만들 메모리풀리스트의 다음을 현재 리스로 설정하고
		// 새로만들것을 전체 메모리리스트의 맨 앞으로 설정한다.
		// 이는 메모리풀 관리에 있어, 연결됨이 중요하지
		// 연결된 순서까진 중요하지 않기때문이다.
		// (이해가 안된다면 그림을 그려보면 된다. 
		// 연결을 되데, 순서는 마지막에 추가된게 맨 앞에 놓이는 그림이된다.)
		k_pool_list->mNext	=	m_pMemoryPoolList;
		m_pMemoryPoolList	=	k_pool_list;
		return &(k_pool_list->mMemPool);
	}
	return NULL;
}

void*		  OvMemoryMgr::Alloc(std::size_t _size_type)
{
	OvAutoSection guardian( m_section );
	// 인수크기의 메모리들을 담는 메모리풀에서 메모리를 리턴한다.
	return get_pool(_size_type)->alloc_memory();
}

void		  OvMemoryMgr::Free(void* _memory)
{
	OvAutoSection guardian( m_section );
	// 이부분은 OvMemoryPool헤더를 보고오면 편하다.
	// 읽었다 가정하고 설명 ㄱㄱ
	// OvMemoryPool는 메모리를 담을때
	// 자신이 담당하는 크기의 메모리단위로 자르는것이 아닌
	// 앞쪽에 4바이트를 더해서 경우에 따라 2종류의 역할로 사용한다.
	// 지금같은 경우는 메모리가 alloc()으로 할당되기 전에
	// 할당된 메모리를 해당 메모리풀에게 다시 환원시키기 위해서
	// 자신이 돌아갈 메모리풀의 포인터를 담는다.


	/*
	예시.
	10바이트의 메모리를 요청□■■
	■■■■□□□□□□□□□□  <= 10개    ("□"를 1바이트로 가정)
	□는 리턴용 메모리이고
	■는 메모리풀이나 OvMemoryMgr이 사용할 공간으로 비워둔다.

	이쯤에서 들어오는 질문 "그럼 1바이트를 요청하면 배보다 배꼽이 더 크잖아?"
	답변 : "네 사실입니다."
	그래도 관리 되는게 어딥니까.
	1바이트가 쌓이면 1키로,메가,기가 로 진화합니다 -┌
	*/


	// 쉽게 말하면.
	// 아래와 같이 메모리는 언제나 자신이 돌아갈 집을 기억하고
	// 집을 나서는것과 같다. (뭐랄까 디아2에서 엑트5까지 열씸히 가서 포탈타고 캠프로 돌아오는 간지?)
	OvMemoryPool* kMemPool = HEADER(_memory)->mMemPool;
	kMemPool->free_memory(_memory);
}

#ifdef _DEBUG
void*		  OvMemoryMgr::Alloc_Debug(char* _pBlock,int _iLine,std::size_t _size_type)
{
	OvAutoSection guardian( m_section );
	return get_pool(_size_type)->alloc_memory_debug(_pBlock,_iLine);
}
void		  OvMemoryMgr::Free_Debug(void* _memory)
{
	OvAutoSection guardian( m_section );
	OvMemoryPool* kMemPool = HEADER(_memory)->mMemPool;
	kMemPool->free_memory_debug(_memory);
}
#endif