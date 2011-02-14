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
	// ��� �޸�Ǯ����Ʈ�� ������.
	for (k_search = m_pMemoryPoolList;k_search;k_search = k_search->mNext)
	{
		// ����Ʈ�� �����ϴ� �޸�Ǯ�� �ּҸ� �ش�.
		k_mem_pool = &(k_search->mMemPool);
		// �� �޸�Ǯ�� ��û�� ũ���� �޸𸮵��� ������ �ִ� �޸�Ǯ���� �˻��Ѵ�.
		if (k_mem_pool->get_size_type() == _size_type)
		{
			//������ ����.
			return k_mem_pool;
		}
	}
	// ������� �Դܰ� ��ûũ���� �޸𸮵��� ��� �޸�Ǯ�� ���ٴ°��̹Ƿ�
	// ���� ���� ����.
	return add_memory_pool(_size_type);
}

OvMemoryPool*		  OvMemoryMgr::add_memory_pool(std::size_t _size_type)
{
	OvMemoryPoolList*	k_pool_list = NULL;

	// �μ�ũ���� �޸𸮵��� ��� �޸�Ǯ�� �����.
	// �޸� ���� ��ü���� new�� ::new ��� malloc���� ���� �Ѵ�.
	// �׷��� ������ ������� �����ڿ� �Ҹ��ڸ� ��� �ξ���.

	k_pool_list	=	(OvMemoryPoolList*)malloc(sizeof(BYTE)*sizeof(OvMemoryPoolList));
	if (k_pool_list)
	{
		k_pool_list->_constructor(_size_type);

		// ���� ���� �޸�Ǯ����Ʈ�� ������ ���� ������ �����ϰ�
		// ���θ������ ��ü �޸𸮸���Ʈ�� �� ������ �����Ѵ�.
		// �̴� �޸�Ǯ ������ �־�, ������� �߿�����
		// ����� �������� �߿����� �ʱ⶧���̴�.
		// (���ذ� �ȵȴٸ� �׸��� �׷����� �ȴ�. 
		// ������ �ǵ�, ������ �������� �߰��Ȱ� �� �տ� ���̴� �׸��̵ȴ�.)
		k_pool_list->mNext	=	m_pMemoryPoolList;
		m_pMemoryPoolList	=	k_pool_list;
		return &(k_pool_list->mMemPool);
	}
	return NULL;
}

void*		  OvMemoryMgr::Alloc(std::size_t _size_type)
{
	OvAutoSection guardian( m_section );
	// �μ�ũ���� �޸𸮵��� ��� �޸�Ǯ���� �޸𸮸� �����Ѵ�.
	return get_pool(_size_type)->alloc_memory();
}

void		  OvMemoryMgr::Free(void* _memory)
{
	OvAutoSection guardian( m_section );
	// �̺κ��� OvMemoryPool����� ������� ���ϴ�.
	// �о��� �����ϰ� ���� ����
	// OvMemoryPool�� �޸𸮸� ������
	// �ڽ��� ����ϴ� ũ���� �޸𸮴����� �ڸ��°��� �ƴ�
	// ���ʿ� 4����Ʈ�� ���ؼ� ��쿡 ���� 2������ ���ҷ� ����Ѵ�.
	// ���ݰ��� ���� �޸𸮰� alloc()���� �Ҵ�Ǳ� ����
	// �Ҵ�� �޸𸮸� �ش� �޸�Ǯ���� �ٽ� ȯ����Ű�� ���ؼ�
	// �ڽ��� ���ư� �޸�Ǯ�� �����͸� ��´�.


	/*
	����.
	10����Ʈ�� �޸𸮸� ��û����
	���������������  <= 10��    ("��"�� 1����Ʈ�� ����)
	��� ���Ͽ� �޸��̰�
	��� �޸�Ǯ�̳� OvMemoryMgr�� ����� �������� ����д�.

	���뿡�� ������ ���� "�׷� 1����Ʈ�� ��û�ϸ� �躸�� ����� �� ũ�ݾ�?"
	�亯 : "�� ����Դϴ�."
	�׷��� ���� �Ǵ°� ����ϱ�.
	1����Ʈ�� ���̸� 1Ű��,�ް�,�Ⱑ �� ��ȭ�մϴ� -��
	*/


	// ���� ���ϸ�.
	// �Ʒ��� ���� �޸𸮴� ������ �ڽ��� ���ư� ���� ����ϰ�
	// ���� �����°Ͱ� ����. (������ ���2���� ��Ʈ5���� ������ ���� ��ŻŸ�� ķ���� ���ƿ��� ����?)
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