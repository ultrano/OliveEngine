#include "OvFileInputStream.h"
#include "OvFile.h"

OvFileInputStream::OvFileInputStream( const OvString& file, const OvString& mode )
: m_file( OvNew OvFile( file, mode ) )
{
}

OvBool OvFileInputStream::ReadByte( OvByte & read )
{
	return !!ReadBytes( &read, sizeof(OvByte) );
}

OvSize OvFileInputStream::ReadBytes( OvByte * dest, OvSize dest_size )
{
	FILE* file = m_file->GetHandle();
	if ( file && dest && dest_size )
	{
		fread( dest, dest_size, 1, file );
		return dest_size;
	}
	return 0;
}

OvBool OvFileInputStream::Open( const OvString& file, const OvString& mode /*= "r+b" */ )
{
	m_file = OvNew OvFile();
	return m_file->Open( file, mode );
}

void OvFileInputStream::Close()
{
	if ( m_file )
	{
		m_file->Close();
	}
}

OvFileSPtr OvFileInputStream::GetFile()
{
	return m_file;
}
