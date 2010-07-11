#include "OvTexture.h"
#include "OvRenderer.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvTexture);

OvTexture::OvTexture()
{
};
OvTexture::~OvTexture()
{
};
LPDIRECT3DTEXTURE9 OvTexture::ToDxTexture()
{
	return m_texture;
}