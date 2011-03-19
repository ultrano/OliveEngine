// 2008 12 11
// maker : Han,sang woon
#define OvExportDll
#include "OvMemoryPool.h"

#ifdef _DEBUG
#include "OvUtility.h"
DWORD	g_dMemoryCount = 0;
void		OvMemoryPool::report_abnormal_memory_release(OvPoolHeader* _pPoolList)
{
	if (_pPoolList)
	{
		for (;_pPoolList;_pPoolList = _pPoolList->mNext)
		{
			for (int i=0;i < STATIC_ALLOC_COUNT;i++)
			{
				OvMemHeader*	k_sequence  = NULL;
				k_sequence			=	(OvMemHeader*)(POOL(_pPoolList)+(MEM_BLOCK_SIZE*i));
				if (k_sequence && k_sequence->m_pBlock )
				{
					OutputDebugString(
						OU::string::format(
						"=================================================\n"
						"[Block: %8s]\n"
						"[Line: %5d]\n"
						"[Size: %5d Byte]\n"
						"[Address: %p]\n"
						"=================================================\n"
						,k_sequence->m_pBlock
						,k_sequence->m_iLine
						,m_stTypeIndexFromMemSize
						,MEMORY(k_sequence)
						).c_str()
						);
				}
			}
		}
	}
}
#endif


void	OvMemoryPool::_constructor(std::size_t _size_type)
{
	m_stTypeIndexFromMemSize = _size_type;
	m_pFreeMemoryList = NULL;
	m_pPoolList = NULL;
}

void	OvMemoryPool::_destructor()
{
#ifdef _DEBUG
	report_abnormal_memory_release(m_pPoolList);
#endif
	// 별거 없다.
	OvPoolHeader*	k_next	=	m_pPoolList;
	OvPoolHeader*	k_header	=	NULL;
	do 
	{
		k_header = k_next;

		if(k_next)
			k_next	 = k_next->mNext;

		free(((void*)k_header));
#ifdef _DEBUG
		OutputDebugString(OU::string::format("Olive Memory Pool Report Free(%8d byte) CallCount: %4d\n",MEM_POOL_SIZE,g_dMemoryCount).c_str());
		g_dMemoryCount--;
#endif
	} while (k_next);

}

bool		OvMemoryPool::add_pool()
{
	// MEM_POOL_SIZE는 매크로다.
	// MEM_POOL_SIZE = ( 담당크기 * 기본할당용갯수(256개로 임의설정) ) + sizeof(OvPoolHeader)
	OvPoolHeader*	k_pool = (OvPoolHeader*)malloc(sizeof(BYTE)*MEM_POOL_SIZE);
	
	// 비트들을 0으로 싹 정리, 굳이 안해줘도 되지만 신생아니까.
	memset(k_pool,0,sizeof(BYTE)*MEM_POOL_SIZE);
	OvPoolHeader*	k_search = NULL;

	// 리스트에 추가. 이해가 안가면 그림으로 해보면 답, 금방나온다.
	// 연결만 된다.
	k_pool->mNext	=	m_pPoolList;
	m_pPoolList		=	k_pool;

	// 사용 가능한 메모리뭉치를 대기메모리 포인터에 셋팅한다.
	m_pFreeMemoryList	=	(OvMemHeader*)POOL(k_pool);
	OvMemHeader*	k_sequence  = NULL;
	// 할단된 메모리뭉치 = ( 담당크기 * 기본할당용갯수(256개로 임의설정) )
	// 를 사용가능하게 ( sizeof(OvMemHeader) + 담당크기 )로 짜르고,
	// OvMemHeader를 위한 앞쪽 4바이트롤 이요해서 서로를 묶는다.
	for (int i=0;i<(STATIC_ALLOC_COUNT - 1);i++)
	{
		k_sequence			=	(OvMemHeader*)(POOL(k_pool)+(MEM_BLOCK_SIZE*i));
		k_sequence->mNext	=	(OvMemHeader*)(POOL(k_pool)+(MEM_BLOCK_SIZE*(i+1)));
#ifdef _DEBUG
		k_sequence->m_pBlock=	NULL;
		k_sequence->m_iLine	=	0;
#endif
	}
#ifdef _DEBUG
	g_dMemoryCount++;
	OutputDebugString(OU::string::format("Olive Memory Pool Report Alloc(%8d byte) CallCount: %4d\n",MEM_POOL_SIZE,g_dMemoryCount).c_str());
#endif
	return true;
}

// 메모리를 할당해준다.
void*		OvMemoryPool::alloc_memory()
{
	// 사용가능한 메모리가 없으면 풀을 늘린다.
	if ( ! m_pFreeMemoryList)
	{
		add_pool();
	}

	OvMemHeader* k_alloc = NULL;

	// 대기메모리를 담당하는 헤더를 불러온다.
	k_alloc		=	m_pFreeMemoryList;

	// 메모리헤더로부터 사용메모리를 추출한다.
	void*	k_return_mem = MEMORY(k_alloc);
	
	// 다음 대기메모리를 셋팅한다.
	m_pFreeMemoryList = m_pFreeMemoryList->mNext;

	// 이부분이 중요하다.
	// 집떠나는 메모리에게 "넌 우리집 세끼다"라는 주소를
	// 목걸이에 걸어주고 떠나보낸다.
	// 그렇게되면 메모리가 해제요청이 왔을때, 부사귀환 할수 있다.
	// 아... 진짜 이맛에 프로그래밍 공부하지 ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ
	// 웃기달까 잼있달까.
	k_alloc->mMemPool	=	this;
	return k_return_mem;

}
void		OvMemoryPool::free_memory(void* _memory)
{

	// 목에 걸어준 집주소로 무사귀환 했다면
	// 이제 집주소를 지우고 다음 대기메모리로의 주소를 셋팅해준다.
	OvMemHeader*	k_mem_header = NULL;
	k_mem_header	=	HEADER(_memory);
	k_mem_header->mNext	=	m_pFreeMemoryList;
	m_pFreeMemoryList		=	k_mem_header;

}

#ifdef _DEBUG
void*		OvMemoryPool::alloc_memory_debug(char* _pBlock,int _iLine)
{
	if ( ! m_pFreeMemoryList)
	{
		add_pool();
	}

	OvMemHeader* k_alloc = NULL;

	k_alloc		=	m_pFreeMemoryList;

	void*	k_return_mem = MEMORY(k_alloc);

	m_pFreeMemoryList = m_pFreeMemoryList->mNext;

	k_alloc->mMemPool	=	this;
	k_alloc->m_pBlock	=	_pBlock;
	k_alloc->m_iLine	=	_iLine;

	return k_return_mem;
}
void		OvMemoryPool::free_memory_debug(void* _memory)
{
	OvMemHeader*	k_mem_header = NULL;
	k_mem_header			=	HEADER(_memory);
	k_mem_header->m_iLine	=	NULL;
	k_mem_header->m_pBlock	=	NULL;
	k_mem_header->mNext		=	m_pFreeMemoryList;
	m_pFreeMemoryList		=	k_mem_header;
}
#endif