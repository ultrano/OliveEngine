#include "OvOutputStream.h"

OvREF_POINTER( OvBuffer );
OvREF_POINTER( OvBufferOutputStream );
class OvBufferOutputStream : public OvOutputStream
{
public:
	OvBufferOutputStream( OvBuffer * buffer );
	OvBufferOutputStream( OvBufferSPtr buffer );

	virtual OvBool WriteByte( OvByte write ) override;
	virtual OvSize WriteBytes( OvByte * src, OvSize write_size ) override;

	template<typename T>
	OvBool	Write( T& data )
	{
		return !!WriteBytes( (OvByte*)&data, sizeof(T) );
	};

	OvBool Write( OvString& data )
	{
		OvSize size = (OvSize)data.size();
		Write( size );
		return !!WriteBytes( (OvByte*)&data[0], size );
	};

private:
	OvBufferSPtr m_buffer;
	OvSize		 m_write_caret;
};