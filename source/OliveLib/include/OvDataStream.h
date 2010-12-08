#pragma once
#include "OvIOStream.h"

class OvDataStream : public OvIOStream, public OvMemObject
{
	OvRTTI_DECL(OvDataStream);
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

	virtual OvInputStream& Read( OvString& buf, OvUInt read_size ) override ;
	virtual OvInputStream& ReadLine( OvString& buf )  override ;

private:

	OvString	m_buffer;
	size_t		m_read_caret;
};