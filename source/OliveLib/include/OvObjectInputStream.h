#pragma once
#include "OvInputStream.h"

class OvObjectID;
OvREF_POINTER(OvObject);
OvREF_POINTER(OvObjectInputStream);
class OvObjectInputStream : public OvInputStream
{
public:

	OvObjectInputStream( OvInputStream* input );
	~OvObjectInputStream();

	virtual OvSize ReadBytes( OvByte * dest, OvSize dest_size ) override;
	virtual OvSize Skip( OvSize offset ) override;

	OvObject* ReadObject();

	OvObject*	Deserialize();

private:

	typedef OvMap<OvObjectID,OvObjectSPtr> restore_table;
	OvInputStream* m_input;
	restore_table	m_restore_table;
	OvSet<OvObjectSPtr>		m_deseiralied;

};