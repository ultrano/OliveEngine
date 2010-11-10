#pragma once
#pragma warning( disable : 4521)

#include "OvMemObject.h"
#include <string>

class OvDataStream : public OvMemObject
{
private:
	OvDataStream();
	OvDataStream( OvDataStream& );
	OvDataStream( const OvDataStream& );
public:

	OvDataStream( const std::string& buf );
	OvDataStream( const char* data, size_t data_size );
	~OvDataStream();

	const char*	Ptr();
	size_t	Size();

	const char*	CaretPtr();
	size_t	CaretPos();

	std::string&	Read( std::string& , size_t );
	std::string&	ReadLine( std::string&, std::string delimiter = "\n" );

private:

	std::string	m_buffer;
	size_t		m_read_caret;
};