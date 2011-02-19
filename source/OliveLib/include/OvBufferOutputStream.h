#include "OvOutputStream.h"

OvREF_POINTER( OvBuffer );
OvREF_POINTER( OvBufferOutputStream );
class OvBufferOutputStream : public OvOutputStream
{
public:
	OvBufferOutputStream( OvBuffer * buffer );
	OvBufferOutputStream( OvBufferSPtr buffer );

	virtual OvBool WriteByte( OvByte write ) override;
	virtual OvSize WriteBytes( OvByte * write_buf, OvSize write_size ) override;

private:
	OvBufferSPtr m_buffer;
	OvSize		 m_write_caret;
};