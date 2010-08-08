#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"

class Ov2DBuffer : public OvMemObject
{
public:
	Ov2DBuffer();
	~Ov2DBuffer();

	bool	AllocBuffer(size_t stWidth,size_t stHeight);
	//bool	ReallocBuffer(size_t stWidth,size_t stHeight);
	void	ClearBuffer();
	void	ReleaseBuffer();

	BYTE*	GetBuffer();
	size_t	GetBufferSize();

	bool	IsBufferAlive();

private:
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;

};