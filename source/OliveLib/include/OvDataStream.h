#pragma once
#pragma warning( disable : 4521)

#include "OvTypeDef.h"
#include "OvMemObject.h"

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

	OvString&	Read( OvString& , size_t );
	OvString&	ReadLine( OvString&, OvString delimiter = "\n" );

private:

	OvString	m_buffer;
	size_t		m_read_caret;
};