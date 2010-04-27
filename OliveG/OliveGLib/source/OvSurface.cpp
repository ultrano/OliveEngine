#include "OvSurface.h"
#include <d3dx9.h>
struct OvSurface::OvPimple : OvMemObject
{
	LPDIRECT3DSURFACE9	m_pSurface;
};

OvSurface::OvSurface(void* pSurface)
:m_pPimple(OvNew OvSurface::OvPimple)
{
	m_pPimple->m_pSurface = (LPDIRECT3DSURFACE9)pSurface;
}
OvSurface::~OvSurface()
{

}

void*	OvSurface::GetSurface()
{
	return m_pPimple->m_pSurface;
}