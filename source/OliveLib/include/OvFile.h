#pragma once
#include "OvRefBase.h"
#include "OvFileInputStream.h"
#include "OvFileOutputStream.h"

OvREF_POINTER(OvFile);
class OvFile : public OvRefBase
{
public:

	OvFile();
	OvFile( const OvString& file, const OvString& mode = "a+b" );
	~OvFile();

	OvBool Open( const OvString& file, const OvString& mode );
	void   Close();

	OvBool IsExist();
	OvBool IsDirectory();
	OvBool IsFile();

	OvString GetPath();
	OvString GetBasePath();

	OvString GetExtention();
	OvString GetFileName();
	
	FILE* GetHandle();

private:

	FILE* m_file;
	OvString m_path;

};