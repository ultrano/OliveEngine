// 2008 12 11
// maker : Han,sang woon
// OvMemoryPool
#pragma once
#include <iostream>
using namespace std;
#include <Windows.h>
#include "OvUtility.h"

// OvPoolHeader,OvMemHeader�� ���� ������ �ڷ��ϰ� �ϴ�.
// OvMemoryPool�� ���� ������� �а� ������~

// OvPoolHeader�� OvMemHeader�� ���� ���信�� ����Ѵ�.
// ���� OvMemHeader�� ���ϵǰ� ���� �޸𸮵� �� 4����Ʈ�� ���ؼ� �װ��� ��ġ�ϰ�
// OvPoolHeader�� OvMemHeader���� ���� ���� �޸� ��ġ �� 4����Ʈ�� ��ġ�Ѵٴ� �����̴�.

// ����ü �̸� : OvPoolHeader
// ���� :
//	OvPoolHeader�� OvMemHeader�� OvMemHeader�� �����ϴ� �޸��� ��ġ(pool�̶�� ǥ����)�� �� 4����Ʈ
//  �� ��ġ�ϸ鼭 ���� ũ���� �߰��� �޸�Ǯ�� ���´�.
struct OvPoolHeader 
{
	OvPoolHeader*	mNext;
	OvPoolHeader():mNext(0)
	{};
};

class	OvMemoryPool;
// ����ü �̸� : OvMemHeader
// ���� : 
//		OvMemHeader�� OvPoolHeader�� ���� ������ ������
//		OvPoolHeader�� �޸� �Ѱ��� ������ ���Ѵ�.
//		�װ��� �ڽ��� �Ҽӵ� �޸�Ǯ�� �����͸� ��°��̴�.
//		�Ʒ��� ���� union���� ���� 2���� ������Ÿ���� �ִ�.

//		---------------- ���⼭ union�� ������ ���� ----------------------
//		union���� ���� �������� ����
//		�޸𸮰����� �����Ѵ�. �׷��� ������ union���� ���� ������ ����ū������
//		�޸𸮰����� Ȯ���ϰ� ����Ÿ�Ը��� ����ϴ� ����ũ�⸦ �޸� ����һ��̴�.
//		�Ʒ��� ���� �Ѵ� ũ�Ⱑ 4����Ʈ �̹Ƿ� OvMemHeader�� ��ũ��� 4����Ʈ���̴�.
//		-----------------------------------------------------------

//		�ٽ� �� �������� �Ĺ�.
//		�׷��� OvMemHeader�� ����ϴ� �޸𸮰� ���� ������� �ƴ� ��� ������ ��쿡�� 
//		���� �������� �޸𸮳��� ������� ���ؼ� ���� ���޸𸮷��� �����͸� ���
//		OvMemHeader�� ����ϴ� �޸𸮰� ����� ���� OvMemoryPool�� ������
//		���ƿü� �ֵ��� ���޸𸮷��� �����ͷ� ����ϴ� 4����Ʈ�� OvMemoryPool���� �����͸� ��´�.
//		������ ������϶��� ���޸𸮷� ���� �ʿ䰡 ���⶧���̴�.
//		�׷��ٰ� ȯ���� �Ǹ� �ٽ� ���޸𸮷��� �����͸� �������ش�.
struct	OvMemHeader 
{
	union
	{
		OvMemHeader*	mNext;
		OvMemoryPool*	mMemPool;
	};
#ifdef _DEBUG
	char*	m_pBlock;
	int		m_iLine;
	OvMemHeader():mNext(NULL),m_pBlock(NULL),m_iLine(NULL)
	{}
#else
	OvMemHeader():mNext(NULL)
	{};
#endif
};

// Ŭ���� �̸� : OvMemoryPool
// ���� : OvMemoryPool�� ó�� �����ɶ� ������ ���ڷ� �ڽ��� ����ϰ� ���� �޸��� ũ�⸦
//		  �ο��ް� �� �޸�ũ�⿡ ���ؼ� �޸𸮸� �Ҵ��ϰ� ȯ���ϰ� �Ѵ�.
//		  �ڽ��� ����ϴ� ũ���� �޸𸮰� ��û�ƴµ� �����ϸ�
//		  Ǯ�� �÷��� �װ����� �޸𸮸� �Ҵ����ش�.
class  OvMemoryPool
{
	friend class OvMemoryMgr;
	friend struct OvMemoryPoolList;
private:
	// �Լ� �̸� : OvMemoryPool
	// ���� : ������
	// OvMemoryPool�� �⺻ �����ڴ� ���Ƴ��´�.
	// OvMemoryPool�� �����Ǹ鼭 ����� ũ�⸦ �ο��޾ƾ߸� �Ѵ�.
	// ���� : ������ ��('��')/
	OvMemoryPool():m_stTypeIndexFromMemSize(0),m_pFreeMemoryList(0),m_pPoolList(0)
	{};

	//! �Ʒ� �� �Լ��� ������,�Ҹ��ڸ� ����ϴ� �Լ���.
	//! �޸� ���� ��������, �޸� ������ �ϴ� ��ü����
	//! operator new ��� malloc ����ϱ� ������ ��������� ȣ��ǰ� �ȴ�.

	// �Լ� �̸� : pool_constructor
	// ���� : ������
	// ����� ũ�⸦ �μ��� �޴� �����ڸ� �㰡�Ѵ�.
	// ���� : ������ ��('��')/
	void	_constructor(std::size_t _size_type);

	// �Լ� �̸� : pool_destructor
	// ���� : �Ҹ���
	// �ı��Ǹ鼭 �ڽ��� �����ϴ� ��� Ǯ���� �����Ѵ�.
	// ���� : ����
	void	_destructor();

#ifdef _DEBUG
	// �Լ� �̸� : report_abnormal_memory_release
	// ���� : ����׿� ������ �޸� ���� ����Ʈ �Լ�
	// ���� : ����
	void		report_abnormal_memory_release(OvPoolHeader* _pPoolList);
#endif

protected:

	// alloc_memory()���� ȣ���ϸ�, �޸�Ǯ�� �������� ���θ���� ��������Ʈ�� �߰��Ѵ�.
	bool				add_pool();

	// �ڽ��� ����ϴ� ũ���� �޸𸮸� �����Ѵ�.
	void*				alloc_memory();

	// �޸𸮸� ȯ���ް�. ���밡���� ������ �޸𸮸���Ʈ�� �ٽ� �߰���Ų��.
	void				free_memory(void* _memory);

#ifdef _DEBUG
	void*				alloc_memory_debug(char* _pBlock,int _iLine);
	void				free_memory_debug(void* _memory);
#endif

	// �� �޸�Ǯ�� ����ϴ� �޸��� ũ�⸦ �˾ƺ���.
	inline std::size_t	get_size_type()const{return m_stTypeIndexFromMemSize;};

private:

	std::size_t	m_stTypeIndexFromMemSize;
	OvMemHeader*		m_pFreeMemoryList;
	OvPoolHeader*		m_pPoolList;
};

#define MEM_HEADER_SIZE	(sizeof(OvMemHeader))
#define MEM_BLOCK_SIZE  (MEM_HEADER_SIZE+m_stTypeIndexFromMemSize)
#define STATIC_ALLOC_COUNT	(16)
#define MEM_POOL_SIZE	((MEM_BLOCK_SIZE*STATIC_ALLOC_COUNT)+sizeof(OvPoolHeader))
#define HEADER(__mem_ptr)	((OvMemHeader*)(((BYTE*)__mem_ptr)-MEM_HEADER_SIZE))
#define MEMORY(__mem_header_ptr)	((BYTE*)(((BYTE*)__mem_header_ptr)+MEM_HEADER_SIZE))
#define POOL(__pool_header_ptr)		((BYTE*)(((BYTE*)__pool_header_ptr)+(sizeof(OvPoolHeader))))
