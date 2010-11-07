// 2008 12 11
// maker : Han,sang woon
// OvMemObject
#pragma once
#pragma warning( disable : 4291 )

//	클레스 이름 : OvMemObject
//	설명
//	{
//		
//		이 클레스는 OvMemoryMgr에서 모든 메모리를 할당받는 
//		역할을 한다.
//		삭제될때도 OvMemoryMgr에게 메모리를 환원하는 형식으로
//		메모리의 재사용을 위해 만들어 졌다.
//		Olive엔진의 대부분의 클레스는 이 클레스를 상속받던가.
//		상속받은 클레스의 재상속을 받고 있으므로 메모리 관리의 범위에 
//		해당된다.
//		
//		PS.자세한 메모리 관리 내용은 OvMemoryMgr클레스 설명을 참조.
//			버추얼 함수가 들어가선 안된다 (소멸자 포함)
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





