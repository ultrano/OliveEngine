#include "Ov2DBuffer.h"
struct Ov2DBuffer::OvPimple : OvMemObject
{
	OvArrayAutoPtr<BYTE>	mpBuffer;
	size_t					mstBufferSize;
};

Ov2DBuffer::Ov2DBuffer()
:m_pPimple(OvNew Ov2DBuffer::OvPimple)
{
	m_pPimple->mpBuffer = NULL;
	m_pPimple->mstBufferSize = 0;
}
Ov2DBuffer::~Ov2DBuffer()
{

}
bool	Ov2DBuffer::AllocBuffer(size_t stWidth,size_t stHeight)
{

	if (IsBufferAlive())
	{
		OvAssertMsg("Buffer Still Alive.");
		return false;
	}

	size_t kstBufferSize = (stWidth * stHeight);
	if (kstBufferSize == 0)
	{
		return false;
	}
	
	OvArrayAutoPtr<BYTE>	kpBuffer = NULL;
	kpBuffer = new BYTE[kstBufferSize];

	if (kpBuffer == NULL)
	{
		return false;
	}

	m_pPimple->mpBuffer = kpBuffer;
	m_pPimple->mstBufferSize = kstBufferSize;

	return true;

}

//bool	Ov2DBuffer::ReallocBuffer(size_t stWidth,size_t stHeight)
//{
//	if (IsBufferAlive() == false)
//	{
//		return AllocBuffer(stWidth,stHeight);
//	}
//
//
//}
void	Ov2DBuffer::ClearBuffer()
{
	ZeroMemory(m_pPimple->mpBuffer.GetRear(), m_pPimple->mstBufferSize);
}
void	Ov2DBuffer::ReleaseBuffer()
{
	if (IsBufferAlive())
	{
		OvArrayAutoPtr<BYTE>	kpBuffer = m_pPimple->mpBuffer;

		//! �������� �����Ǹ鼭 �ڵ����� NULL�� ���� ������ ��Ȯ���Ѵ�.
		//! (�� ����� �������� �ּ����� �����ϻ�.���� �ϸ� �ȵȴ�.)
		m_pPimple->mpBuffer = NULL; 
		m_pPimple->mstBufferSize = 0;
	}
}

BYTE*	Ov2DBuffer::GetBuffer()
{
	return m_pPimple->mpBuffer.GetRear();
}

size_t	Ov2DBuffer::GetBufferSize()
{
	return m_pPimple->mstBufferSize;
}
bool	Ov2DBuffer::IsBufferAlive()
{
	return (m_pPimple->mpBuffer && m_pPimple->mstBufferSize);
}