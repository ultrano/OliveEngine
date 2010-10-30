#include "OvResourceLoader.h"
#include "OvResource.h"

OvResourceSPtr OvResourceLoader::_load_resource( const std::string& fileLocation )
{
	return Load( fileLocation );
}