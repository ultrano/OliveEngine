#include "OvFileOutputStream.h"
#include "OvFile.h"

OvFileOutputStream::OvFileOutputStream( OvFileSPtr file )
: m_file( file )
{
	if ( m_file )
	{
		m_file->Open();
	}
}

OvFileOutputStream::OvFileOutputStream( const OvString& file, const OvString& mode )
: m_file( OvNew OvFile( file, mode ) )
{
}

OvSize OvFileOutputStream::WriteBytes( OvByte * write_buf, OvSize write_size )
{
	FILE* file = m_file->GetHandle();
	if ( file && write_buf && write_size )
	{
		fwrite( write_buf, write_size, 1, file );
		return write_size;
	}
	return 0;
}

OvSize OvFileOutputStream::Skip( OvSize offset )
{
	if ( offset > 0 )
	{
		FILE* file = m_file->GetHandle();
		fseek( file, offset, SEEK_CUR );
		return offset;
	}
	return 0;
}

OvBool OvFileOutputStream::Open( const OvString& file, const OvString& mode /*= "w+b" */ )
{
	m_file = OvNew OvFile();
	return m_file->Open( file, mode );
}

void OvFileOutputStream::Close()
{
	if ( m_file )
	{
		m_file->Close();
	}
}

OvFileSPtr OvFileOutputStream::GetFile()
{
	return m_file;
}
