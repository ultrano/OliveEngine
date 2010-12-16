#pragma once
#include "OliveValue.h"

namespace OliveValue
{
	class Tuple : public OliveValue::Value
	{
		OvRTTI_DECL(Tuple);
	public:
		virtual void		FromString( const OvString& expData ) override;
		virtual OvString	ToString() override;
	public:
	};
}