#pragma once
#include "OvInputStream.h"

OvREF_POINTER(OvFile);
OvREF_POINTER(OvFileOutputStream);
class OvFileInputStream : public OvInputStream
{
private:
	OvFileInputStream();
public:

	OvFileInputStream( const OvString& file, const OvString& mode = "r+b" );

	virtual OvBool ReadByte( OvByte & read ) override;
	virtual OvSize ReadBytes( OvByte * dest, OvSize dest_size ) override;

	OvBool Open( const OvString& file, const OvString& mode = "r+b" );
	void Close();
	OvFileSPtr GetFile();

private:

	OvFileSPtr m_file;

};