#include "OvResourceLoader.h"
#include "OvResource.h"

OvRTTI_IMPL( OvResourceLoader );

OvResourceSPtr OvResourceLoader::_load_resource( const std::string& fileLocation )
{
	return Load( fileLocation );
}