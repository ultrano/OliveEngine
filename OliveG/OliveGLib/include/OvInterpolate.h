#pragma once

template<typename Type_0>
Type_0	OvLinearInterpolate(float fRate,const Type_0& _rScr,const Type_0& _rDest)
{
	return (_rDest * fRate) + (_rScr * (1.0f - fRate));
}
