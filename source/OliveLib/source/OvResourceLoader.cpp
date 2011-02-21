#include "OvResourceLoader.h"
#include "OvResource.h"
#include "OvBuffer.h"
#include "OvBufferInputStream.h"
#include <io.h>

OvRTTI_IMPL( OvResourceLoader );

OvResourceSPtr OvResourceLoader::_load_resource( const OvString& fileLocation )
{
	static OvCriticalSection section;
	//EnterCriticalSection( &section.m_section );

	OvString filename = OvGetFileNameInFullFilePath( fileLocation );
	filename += OvGetExtentionInFullFilePath( fileLocation );
	OutputDebugStr( filename.c_str() );
	OutputDebugStr( "\n" );

	FILE* file = NULL;
	fopen_s( &file, fileLocation.c_str(), "rb" ); // ���̳ʸ��� �о���̴°� ����Ʈ!
	if ( file )
	{
		size_t filesize = _filelength( _fileno( file ) );
		
		OvBufferSPtr buf = OvBuffer::CreateBuffer( filesize );

		fseek( file, 0, SEEK_SET );
		fread( (void*)buf->Pointer(), 1, filesize, file );

		fclose( file );

		OvBufferInputStream bis( buf );
		return Load( bis );
	}

	return NULL;
}