#pragma once
#include "OvIOStream.h"

class OvDataStream : public OvMemObject
{
private:
	OvDataStream();
	OvDataStream( OvDataStream& );
	OvDataStream( const OvDataStream& );
public:

	OvDataStream( const OvString& buf );
	OvDataStream( size_t reserve_size );
	~OvDataStream();

	const OvChar*	Ptr();
	size_t	Size();

	const OvChar*	CaretPtr();
	size_t	CaretPos();

	OvUInt Read( OvString& buf, OvUInt read_size ) ;
	OvUInt ReadLine( OvString& buf )  ;

private:

	OvString	m_buffer;
	size_t		m_read_caret;
};