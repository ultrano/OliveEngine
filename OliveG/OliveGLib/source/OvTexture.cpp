#include "OvTexture.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvTexture,OvRefBase);
struct OvTexture::OvPimple : OvMemObject
{
	LPDIRECT3DTEXTURE9 m_pTexture;
};


OvTexture::OvTexture(void* pTexture)
:m_pPimple(OvNew OvTexture::OvPimple)
{
	LPDIRECT3DTEXTURE9 kpDXTexture = (LPDIRECT3DTEXTURE9)pTexture;
	if (kpDXTexture)
	{
		m_pPimple->m_pTexture = kpDXTexture;
	}
};
OvTexture::~OvTexture()
{
	if (m_pPimple->m_pTexture)
	{
		m_pPimple->m_pTexture->Release();
	}
};
void*	OvTexture::GetTexture()
{
	return (void*)m_pPimple->m_pTexture;
}