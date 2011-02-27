#pragma once
#include "OvObject.h"

namespace OliveValue{ OvREF_POINTER(Value); };
//! Object Nexus Layer
OvREF_POINTER(OvObjectNex);
class OvObjectNex : public OvObject
{
	OvRTTI_DECL( OvObjectNex );
public:

	//!< Extra Property�� ������ ���� �Ǵ� �������� 
	//!< �ѰԸ� �޴� ���·� ���� �ƴ�.
	//!< ���� �������� �ʿ��Ѱ�� Table�� ������ ����ϸ� �ȴ�.
// 	void	SetExtraProperty( OliveValue::ValueSPtr val );
// 	OliveValue::ValueSPtr GetExtraProperty( const OvString& key );

	//! Object Name
	void			SetName(const OvChar* _pName);
	const OvString&	GetName();

private:

	OvString				m_name;

};