#pragma once

#include "OvObjectData.h"


class OvStreamingContainer : public OvMemObject
{
public:

	OvStreamingContainer();
	~OvStreamingContainer();

	void			SetObjectData(OvObjectData& objData);
	OvObjectData&	GetObjectData();

	void		PushComponentObject(OvObject* componentObject);
	OvObject*	PopComponentObject();

private:
	OvObjectData		m_objectData;
	queue<OvObject*>	m_queObjects;
};