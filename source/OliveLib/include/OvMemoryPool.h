// 2008 12 11
// maker : Han,sang woon
// OvMemoryPool
#pragma once
#include <iostream>
using namespace std;
#include <Windows.h>
#include "OvUtility.h"

// OvPoolHeader,OvMemHeader에 관한 설명은 뒤로하고 일단.
// OvMemoryPool에 관한 설명부터 읽고 오세요~

// OvPoolHeader와 OvMemHeader는 같은 개념에서 출발한다.
// 단지 OvMemHeader는 리턴되고 사용될 메모리들 앞 4바이트를 더해서 그곳에 위치하고
// OvPoolHeader는 OvMemHeader들을 묶어 놓은 메모리 뭉치 앞 4바이트에 위치한다는 차이이다.

// 구조체 이름 : OvPoolHeader
// 설명 :
//	OvPoolHeader는 OvMemHeader과 OvMemHeader가 관리하는 메모리의 뭉치(pool이라고 표현함)의 앞 4바이트
//  에 위치하면서 같은 크기의 추가된 메모리풀을 같는다.
struct OvPoolHeader 
{
	OvPoolHeader*	mNext;
	OvPoolHeader():mNext(0)
	{};
};

class	OvMemoryPool;
// 구조체 이름 : OvMemHeader
// 설명 : 
//		OvMemHeader는 OvPoolHeader와 같은 역할을 하지만
//		OvPoolHeader와 달리 한가지 역할을 더한다.
//		그것은 자신이 소속된 메모리풀의 포인터를 담는것이다.
//		아래와 같이 union으로 묶인 2개의 포인터타입이 있다.

//		---------------- 여기서 union의 간단한 설명 ----------------------
//		union으로 묶인 변수들은 같은
//		메모리공간을 공유한다. 그렇기 때문에 union으로 묶인 변수중 가장큰변수로
//		메모리공간을 확보하고 변수타입마다 사용하는 공간크기를 달리 사용할뿐이다.
//		아래의 경우는 둘다 크기가 4바이트 이므로 OvMemHeader의 총크기는 4바이트뿐이다.
//		-----------------------------------------------------------

//		다시 본 설명으로 컴백.
//		그래서 OvMemHeader가 담당하는 메모리가 현재 사용중이 아닌 대기 상태일 경우에는 
//		같은 대기상태인 메모리끼리 묶어놓기 위해서 다음 대기메모리로의 포인터를 담고
//		OvMemHeader가 담당하는 메모리가 사용을 위해 OvMemoryPool을 떠나면
//		돌아올수 있도록 대기메모리로의 포인터로 사용하던 4바이트에 OvMemoryPool로의 포인터를 담는다.
//		어차피 사용중일때는 대기메모리로 묶일 필요가 없기때문이다.
//		그러다가 환원이 되면 다시 대기메모리로의 포인터를 셋팅해준다.
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

// 클레스 이름 : OvMemoryPool
// 설명 : OvMemoryPool는 처음 생설될때 생성자 인자로 자신이 담당하고 담을 메모리의 크기를
//		  부여받고 그 메모리크기에 관해서 메모리를 할당하고 환원하고를 한다.
//		  자신이 담당하는 크기의 메모리가 요청됐는데 부족하면
//		  풀을 늘려서 그곳에서 메모리를 할당해준다.
class  OvMemoryPool
{
	friend class OvMemoryMgr;
	friend struct OvMemoryPoolList;
private:
	// 함수 이름 : OvMemoryPool
	// 설명 : 생성자
	// OvMemoryPool의 기본 생성자는 막아놓는다.
	// OvMemoryPool는 생성되면서 담당할 크기를 부여받아야만 한다.
	// 리턴 : 없떠염 ∠('ㅅ')/
	OvMemoryPool():m_stTypeIndexFromMemSize(0),m_pFreeMemoryList(0),m_pPoolList(0)
	{};

	//! 아래 두 함수는 생성자,소멸자를 대신하는 함수다.
	//! 메모리 관리 차원에서, 메모리 관리를 하는 객체들은
	//! operator new 대신 malloc 사용하기 때문에 명시적으로 호출되게 된다.

	// 함수 이름 : pool_constructor
	// 설명 : 생성자
	// 담당할 크기를 인수로 받는 생성자만 허가한다.
	// 리턴 : 없떠염 ∠('ㅅ')/
	void	_constructor(std::size_t _size_type);

	// 함수 이름 : pool_destructor
	// 설명 : 소멸자
	// 파괴되면서 자신이 관리하는 모든 풀들을 해제한다.
	// 리턴 : 없뜸
	void	_destructor();

#ifdef _DEBUG
	// 함수 이름 : report_abnormal_memory_release
	// 설명 : 디버그용 비정상 메모리 해제 리포트 함수
	// 리턴 : 없뜸
	void		report_abnormal_memory_release(OvPoolHeader* _pPoolList);
#endif

protected:

	// alloc_memory()에서 호출하며, 메모리풀이 오링나면 새로만들고 관리리스트에 추가한다.
	bool				add_pool();

	// 자신이 담당하는 크기의 메모리를 리턴한다.
	void*				alloc_memory();

	// 메모리를 환원받고. 재사용가능한 여분의 메모리리스트에 다시 추가시킨다.
	void				free_memory(void* _memory);

#ifdef _DEBUG
	void*				alloc_memory_debug(char* _pBlock,int _iLine);
	void				free_memory_debug(void* _memory);
#endif

	// 이 메모리풀이 담당하는 메모리의 크기를 알아본다.
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
