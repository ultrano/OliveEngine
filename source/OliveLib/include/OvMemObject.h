// 2008 12 11
// maker : Han,sang woon
// OvMemObject
#pragma once
#pragma warning( disable : 4291 )

//	Ŭ���� �̸� : OvMemObject
//	����
//	{
//		
//		�� Ŭ������ OvMemoryMgr���� ��� �޸𸮸� �Ҵ�޴� 
//		������ �Ѵ�.
//		�����ɶ��� OvMemoryMgr���� �޸𸮸� ȯ���ϴ� ��������
//		�޸��� ������ ���� ����� ����.
//		Olive������ ��κ��� Ŭ������ �� Ŭ������ ��ӹ޴���.
//		��ӹ��� Ŭ������ ������ �ް� �����Ƿ� �޸� ������ ������ 
//		�ش�ȴ�.
//		
//		PS.�ڼ��� �޸� ���� ������ OvMemoryMgrŬ���� ������ ����.
//			���߾� �Լ��� ���� �ȵȴ� (�Ҹ��� ����)
//	}
#ifdef _DEBUG

#define OvNew	new(__FUNCTION__,__LINE__)
#define OvDelete delete

#define OvMemAlloc(mem_size) OvMemAlloc_Debug(__FUNCTION__,__LINE__,mem_size);
#define OvMemFree(mem_pointer) OvMemFree_Debug(mem_pointer);

#else

#define OvNew	new
#define OvDelete delete

#define OvMemAlloc(mem_size) OvMemAlloc_Release(mem_size);
#define OvMemFree(mem_pointer) OvMemFree_Release(mem_pointer);

#endif

class 	OvMemObject //: public OvMultiThreadSync<OvMemObject>
{
public:

#ifdef _DEBUG
	static	void*	operator new(size_t _size, char* _pBlock,int _iLine);
	static	void*	operator new[](size_t _size, char* _pBlock,int _iLine);
#endif

	static	void*	operator new(size_t, void* location);

	static	void*	operator new(size_t _size);
	static	void*	operator new[](size_t _size);

	static	void	operator delete(void* _memory);
	static	void	operator delete[](void* _memory);

protected:
private:
};


#ifdef _DEBUG
void*	OvMemAlloc_Debug(char* _pBlock,int _iLine,const size_t _szMemSize);
void	OvMemFree_Debug(void* _pMemory);
#endif

void*	OvMemAlloc_Release(const size_t _szMemSize);
void	OvMemFree_Release(void* _pMemory);





