#include "OvResourceLoader.h"
#include "OvResource.h"
#include "OvDataStream.h"
#include <io.h>

OvRTTI_IMPL( OvResourceLoader );

OvResourceSPtr OvResourceLoader::_load_resource( const std::string& fileLocation )
{
	FILE* file = NULL;
	fopen_s( &file, fileLocation.c_str(), "rb" ); // ���̳ʸ��� �о���̴°� ����Ʈ!
	if ( file )
	{
		size_t filesize = _filelength( _fileno( file ) );
		
		OvAutoPtr<OvDataStream> data = OvNew OvDataStream( filesize );

		fseek( file, 0, SEEK_SET );
		fread( (void*)data->Ptr(), 1, filesize, file );

		fclose( file );

		return Load( *data );
	}
	return NULL;
}