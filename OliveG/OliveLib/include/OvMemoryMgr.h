// 2008 12 11
// maker : Han,sang woon
// OvMemoryMgr
#pragma once
#include "OvUtility.h"
#include "OvSingleton.h"

class OvMemoryPool;

struct OvMemoryPoolList ;

//	클레스 이름 : OvMemoryMgr
//	설명
//	{
//		Olive엔진의 모든 메모리를 할당하고 삭제하는 클레스.
//		엔진에서 사용되는 대부분의 클레스들은 이 클레스에서
//		메모리 할당을 받는다.
//		
//		이 메모리관리 클레스의 차이점은
//		메모리관리를 클레스단위가 아닌
//		요청된 메모리 크기에 따라 다르게 
//		메모리 할당은 해준다.
//		그렇기 때문에 OvMemObject(OvMemoryMgr에게 메모리 요청을 담당하는 클레스)이 직계
//		부모클레스가 아닌 한참 위쪽에 자리한 조상클레스라서 자식클레스의 크기들이 각기
//		다르더라도 크기에 맞는 메모리를 할당해주고 없을시 그 크기에 맞는 메모리 풀을
//		생성해서 재사용 목록에 추가시킨후
//		OvMemoryMgr자신이 삭제될때 일괄삭제시킨다.
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

	// 함수이름 : get_pool
	// 설명 : 인수로 들어온 메모리크기의 메모리풀을 리턴한다. (OvMemoryPool에 대한설명은 해당 헤더를참조)
	//		  인수로 전달되는 _size_type는 메모리풀의 이름,ID,인덱스 정도로 생각해도 된다.
	// 리턴 : OvMemoryPool포인터
	OvMemoryPool* get_pool(std::size_t _size_type);

	// 함수 이름 : add_memory_pool
	// 설명 : get_pool에서 인수로 요청된 크기의 메모리풀이 없으면 메모리풀을 추가시킨고 리턴한다.
	// 리턴 : OvMemoryPool포인터
	OvMemoryPool* add_memory_pool(std::size_t _size_type);
protected:
	// 함수 이름 : Alloc
	// 설명 : get_pool()을 호출하고 해당크기의 메모리를 리턴한다.
	// 리턴 : _size_type사이즈의 메모리
	void*		  Alloc(std::size_t _size_type);

	// 함수 이름 : Free
	// 설명 : alloc과는 반대의 일을 한다.
	// 리턴 : 없떠염 'ㅅ'
	void		  Free(void* _memory);

#ifdef _OvMEMORY_DEBUG_
	void*		  Alloc_Debug(char* _pBlock,int _iLine,std::size_t _size_type);
	void		  Free_Debug(void* _memory);
#endif

private:

	// 변수 이름 : m_pMemoryPoolList
	// 설명 : 보시다시피 이름 그대로 입죠 -_- 아... 밤새겠네 이거...
	//		  이게 주석처리 첫번째 헤더파일인데 =_=;;;
	OvMemoryPoolList*	m_pMemoryPoolList;
};
