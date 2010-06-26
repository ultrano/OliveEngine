// 2008 12 11
// maker : Han,sang woon
// OvMemoryMgr
#pragma once
#include "OvUtility.h"
#include "OvSingleton.h"

class OvMemoryPool;

struct OvMemoryPoolList ;

//	Ŭ���� �̸� : OvMemoryMgr
//	����
//	{
//		Olive������ ��� �޸𸮸� �Ҵ��ϰ� �����ϴ� Ŭ����.
//		�������� ���Ǵ� ��κ��� Ŭ�������� �� Ŭ��������
//		�޸� �Ҵ��� �޴´�.
//		
//		�� �޸𸮰��� Ŭ������ ��������
//		�޸𸮰����� Ŭ���������� �ƴ�
//		��û�� �޸� ũ�⿡ ���� �ٸ��� 
//		�޸� �Ҵ��� ���ش�.
//		�׷��� ������ OvMemObject(OvMemoryMgr���� �޸� ��û�� ����ϴ� Ŭ����)�� ����
//		�θ�Ŭ������ �ƴ� ���� ���ʿ� �ڸ��� ����Ŭ������ �ڽ�Ŭ������ ũ����� ����
//		�ٸ����� ũ�⿡ �´� �޸𸮸� �Ҵ����ְ� ������ �� ũ�⿡ �´� �޸� Ǯ��
//		�����ؼ� ���� ��Ͽ� �߰���Ų��
//		OvMemoryMgr�ڽ��� �����ɶ� �ϰ�������Ų��.
//		
//		
//		
//		
//		
//	}
class  OvMemoryMgr : public OvSingletonBase< OvMemoryMgr >
{
#ifdef _OvMEMORY_DEBUG_
	friend void* OvMemAlloc_Debug(char* ,int ,const size_t);
	friend void	OvMemFree_Debug(void*);
#endif

	friend void* OvMemAlloc_Release(const size_t);
	friend void	OvMemFree_Release(void*);
	friend class OvMemObject;
	friend class OvSingletonContextList;
	OvMemoryMgr();
	~OvMemoryMgr();

private:

	// �Լ��̸� : get_pool
	// ���� : �μ��� ���� �޸�ũ���� �޸�Ǯ�� �����Ѵ�. (OvMemoryPool�� ���Ѽ����� �ش� ���������)
	//		  �μ��� ���޵Ǵ� _size_type�� �޸�Ǯ�� �̸�,ID,�ε��� ������ �����ص� �ȴ�.
	// ���� : OvMemoryPool������
	OvMemoryPool* get_pool(std::size_t _size_type);

	// �Լ� �̸� : add_memory_pool
	// ���� : get_pool���� �μ��� ��û�� ũ���� �޸�Ǯ�� ������ �޸�Ǯ�� �߰���Ų�� �����Ѵ�.
	// ���� : OvMemoryPool������
	OvMemoryPool* add_memory_pool(std::size_t _size_type);
protected:
	// �Լ� �̸� : Alloc
	// ���� : get_pool()�� ȣ���ϰ� �ش�ũ���� �޸𸮸� �����Ѵ�.
	// ���� : _size_type�������� �޸�
	void*		  Alloc(std::size_t _size_type);

	// �Լ� �̸� : Free
	// ���� : alloc���� �ݴ��� ���� �Ѵ�.
	// ���� : ������ '��'
	void		  Free(void* _memory);

#ifdef _OvMEMORY_DEBUG_
	void*		  Alloc_Debug(char* _pBlock,int _iLine,std::size_t _size_type);
	void		  Free_Debug(void* _memory);
#endif

private:

	// ���� �̸� : m_pMemoryPoolList
	// ���� : ���ôٽ��� �̸� �״�� ���� -_- ��... ����ڳ� �̰�...
	//		  �̰� �ּ�ó�� ù��° ��������ε� =_=;;;
	OvMemoryPoolList*	m_pMemoryPoolList;
};
