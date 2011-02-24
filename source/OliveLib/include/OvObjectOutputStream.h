#pragma once
#include "OvOutputStream.h"

OvREF_POINTER(OvObject);
class OvObjectOutputStream : public OvOutputStream
{
public:

	OvObjectOutputStream( OvOutputStream* output );
	~OvObjectOutputStream();

	virtual OvSize WriteBytes( OvByte * write_buf, OvSize write_size ) override;

	OvBool	WriteObject( OvObjectSPtr obj );

	OvBool	Serialize( OvObjectSPtr obj );

private:

	OvOutputStream* m_output;

	OvSet<OvObjectSPtr>	m_serialize_targets;
	OvSet<OvObjectSPtr>	m_serialized;

};