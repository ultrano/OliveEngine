#pragma once

class OvInterpolator;

namespace OvInterpMethod
{
	typedef float(*MethodType)( OvInterpolator* interplator, float src, float dest );
	float Linear( OvInterpolator* interplator, float src, float dest );
}