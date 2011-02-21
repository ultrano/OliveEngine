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
	// ���� ����.
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
	// MEM_POOL_SIZE�� ��ũ�δ�.
	// MEM_POOL_SIZE = ( ���ũ�� * �⺻�Ҵ�밹��(256���� ���Ǽ���) ) + sizeof(OvPoolHeader)
	OvPoolHeader*	k_pool = (OvPoolHeader*)malloc(sizeof(BYTE)*MEM_POOL_SIZE);
	
	// ��Ʈ���� 0���� �� ����, ���� �����൵ ������ �Ż��ƴϱ�.
	memset(k_pool,0,sizeof(BYTE)*MEM_POOL_SIZE);
	OvPoolHeader*	k_search = NULL;

	// ����Ʈ�� �߰�. ���ذ� �Ȱ��� �׸����� �غ��� ��, �ݹ泪�´�.
	// ���Ḹ �ȴ�.
	k_pool->mNext	=	m_pPoolList;
	m_pPoolList		=	k_pool;

	// ��� ������ �޸𸮹�ġ�� ���޸� �����Ϳ� �����Ѵ�.
	m_pFreeMemoryList	=	(OvMemHeader*)POOL(k_pool);
	OvMemHeader*	k_sequence  = NULL;
	// �Ҵܵ� �޸𸮹�ġ = ( ���ũ�� * �⺻�Ҵ�밹��(256���� ���Ǽ���) )
	// �� ��밡���ϰ� ( sizeof(OvMemHeader) + ���ũ�� )�� ¥����,
	// OvMemHeader�� ���� ���� 4����Ʈ�� �̿��ؼ� ���θ� ���´�.
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

// �޸𸮸� �Ҵ����ش�.
void*		OvMemoryPool::alloc_memory()
{
	// ��밡���� �޸𸮰� ������ Ǯ�� �ø���.
	if ( ! m_pFreeMemoryList)
	{
		add_pool();
	}

	OvMemHeader* k_alloc = NULL;

	// ���޸𸮸� ����ϴ� ����� �ҷ��´�.
	k_alloc		=	m_pFreeMemoryList;

	// �޸�����κ��� ���޸𸮸� �����Ѵ�.
	void*	k_return_mem = MEMORY(k_alloc);
	
	// ���� ���޸𸮸� �����Ѵ�.
	m_pFreeMemoryList = m_pFreeMemoryList->mNext;

	// �̺κ��� �߿��ϴ�.
	// �������� �޸𸮿��� "�� �츮�� ������"��� �ּҸ�
	// ����̿� �ɾ��ְ� ����������.
	// �׷��ԵǸ� �޸𸮰� ������û�� ������, �λ��ȯ �Ҽ� �ִ�.
	// ��... ��¥ �̸��� ���α׷��� �������� ����������������������������������������������������������������������������������������������
	// ����ޱ� ���ִޱ�.
	k_alloc->mMemPool	=	this;
	return k_return_mem;

}
void		OvMemoryPool::free_memory(void* _memory)
{

	// �� �ɾ��� ���ּҷ� �����ȯ �ߴٸ�
	// ���� ���ּҸ� ����� ���� ���޸𸮷��� �ּҸ� �������ش�.
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