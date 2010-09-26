#include "OvShaderCodeIncluder.h"
#include "OvGlobalFunc.h"
#include "OvResourceManager.h"
#include "OvShaderCode.h"
#include <iostream>
#include <fstream>
using namespace std;


OvShaderCodeIncluder::OvShaderCodeIncluder( const std::string& basePath )
: m_basePath( basePath )
{

}

STDMETHODIMP OvShaderCodeIncluder::Open( THIS_ D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes )
{
	string fileLocation;
	switch ( IncludeType )
	{
	case D3DXINC_SYSTEM : 
		fileLocation = m_basePath + "/" + pFileName;
		break;
	case D3DXINC_LOCAL : 
		fileLocation = OvResourceLocation( pFileName );
		break;
	}

	OvShaderCodeSPtr code_resource = OvResourceManager::GetInstance()->LoadResource<OvShaderCode>( fileLocation );

	if ( code_resource )
	{
		OvResourceManager::GetInstance()->ResourceCache( code_resource );
		*ppData = code_resource->GetCodeBuffer();
		*pBytes = code_resource->GetCodeSize();
		return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP OvShaderCodeIncluder::Close( THIS_ LPCVOID pData )
{
	return S_OK;
}