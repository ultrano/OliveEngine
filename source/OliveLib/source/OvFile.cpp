#include "OvFile.h"
#include <atlpath.h>
OvRTTI_IMPL(OvFile);

OvFile::OvFile()
: m_file( NULL )
{

}

OvFile::OvFile( const OvString& file, const OvString& mode )
: m_file( NULL )
{
	Open( file, mode );
}

OvFile::~OvFile()
{
	Close();
}

OvBool OvFile::Open( const OvString& file, const OvString& mode )
{
	m_path = file;
	m_mode = mode;
	fopen_s( &m_file, m_path.c_str(), m_mode.c_str() );
	return !!m_file;
}

OvBool OvFile::Open()
{
	fopen_s( &m_file, m_path.c_str(), m_mode.c_str() );
	return !!m_file;
}

void OvFile::Close()
{
	if ( m_file )
	{
		fclose( m_file );
	}
}

OvBool OvFile::IsExist()
{
	return !!ATL::ATLPath::FileExists( m_path.c_str() );
}

OvBool OvFile::IsDirectory()
{
	return !!ATL::ATLPath::IsDirectory( m_path.c_str() );
}

OvBool OvFile::IsFile()
{
	return !!ATL::ATLPath::IsFileSpec( m_path.c_str() );
}

OvString OvFile::GetPath()
{
	return m_path;
}

OvString OvFile::GetBasePath()
{
	OvString copy = m_path;
	ATL::ATLPath::RemoveFileSpec( &copy[0] );
	return copy;
}

OvString OvFile::GetExtention()
{
	return ATL::ATLPath::FindExtension( m_path.c_str() );
}

OvString OvFile::GetFileName()
{
	return ATL::ATLPath::FindFileName( m_path.c_str() );
}

FILE* OvFile::GetHandle()
{
	return m_file;
}
