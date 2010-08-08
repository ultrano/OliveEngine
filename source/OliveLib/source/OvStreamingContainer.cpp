//#include "OvStreamingContainer.h"
//
//
//
//
//OvStreamingContainer::OvStreamingContainer()
//:m_objectData(OvObjectData::INVALID)
//{
//
//}
//
//OvStreamingContainer::~OvStreamingContainer()
//{
//
//}
//
//void			OvStreamingContainer::SetObjectData(OvObjectData& objData)
//{
//	m_objectData = objData;
//}
//OvObjectData&	OvStreamingContainer::GetObjectData()
//{
//	return m_objectData;
//}
//
//
//void	OvStreamingContainer::PushComponentObject(OvObject* componentObject)
//{
//	m_queObjects.push(componentObject);
//}
//OvObject*	OvStreamingContainer::PopComponentObject()
//{
//	if (m_queObjects.size())
//	{
//		OvObject* kpObj = m_queObjects.front();
//		m_queObjects.pop();
//		return kpObj;
//	}
//	return NULL;
//}