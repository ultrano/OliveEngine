// 2008 12 11
// maker : Han,sang woon
#define OvExportDll
#include "OvMemObject.h"
#include "OvMemoryMgr.h"
#include "OvUtility.h"

void*	OvMemObject::operator new(size_t, void* location)
{
	return location;
}


#ifdef _OvMEMORY_DEBUG_
void*	OvMemObject::operator new(std::size_t _size, char* _pBlock,int _iLine)
{
	return OvMemAlloc_Debug(_pBlock,_iLine,_size);
}
void*	OvMemObject::operator new[](std::size_t _size, char* _pBlock,int _iLine)
{
	return OvMemAlloc_Debug(_pBlock,_iLine,_size);
}
#endif

void*	OvMemObject::operator new(std::size_t _size)
{
	return OvMemAlloc(_size);
}
void	OvMemObject::operator delete(void* _memory)
{
	OvMemFree(_memory);
}
void*	OvMemObject::operator new[](std::size_t _size)
{
	return OvMemAlloc(_size);
}
void	OvMemObject::operator delete[](void* _memory)
{
	OvMemFree(_memory);
}


#ifdef _OvMEMORY_DEBUG_

void*	OvMemAlloc_Debug(char* _pBlock,int _iLine,const size_t _szMemSize)
{
	return OvMemoryMgr::GetInstance()->Alloc_Debug(_pBlock, _iLine,_szMemSize);
}
void	OvMemFree_Debug(void* _pMemory)
{
	OvMemoryMgr::GetInstance()->Free_Debug(_pMemory);
}

#endif

void*	OvMemAlloc_Release(const size_t _szMemSize)
{
	return OvMemoryMgr::GetInstance()->Alloc(_szMemSize);
}
void	OvMemFree_Release(void* _pMemory)
{
	OvMemoryMgr::GetInstance()->Free(_pMemory);
}


