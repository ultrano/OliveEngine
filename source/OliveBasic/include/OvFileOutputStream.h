#pragma once
#include "OvOutputStream.h"

OvREF_POINTER(OvFile);
OvREF_POINTER(OvFileOutputStream);
class OvFileOutputStream : public OvOutputStream
{
private:
	OvFileOutputStream();
public:

	OvFileOutputStream( OvFileSPtr file );
	OvFileOutputStream( const OvString& file, const OvString& mode = "w+b" );

	virtual OvSize WriteBytes( OvByte * write_buf, OvSize write_size ) override;
	virtual OvSize Skip( OvSize offset ) override;

	OvBool Open( const OvString& file, const OvString& mode = "w+b" );
	void Close();
	OvFileSPtr GetFile();

private:

	OvFileSPtr m_file;

};