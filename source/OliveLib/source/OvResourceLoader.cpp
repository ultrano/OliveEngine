#include "OvResourceLoader.h"
#include "OvResource.h"
#include "OvDataStream.h"
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
	fopen_s( &file, fileLocation.c_str(), "rb" ); // 바이너리로 읽어들이는게 뽀인트!
	if ( file )
	{
		size_t filesize = _filelength( _fileno( file ) );
		
		OvAutoPtr<OvDataStream> data = OvNew OvDataStream( filesize );

		fseek( file, 0, SEEK_SET );
		fread( (void*)data->Ptr(), 1, filesize, file );

		fclose( file );
		//LeaveCriticalSection( &section.m_section );

		return Load( *data );
	}
	//LeaveCriticalSection( &section.m_section );
	return NULL;
}