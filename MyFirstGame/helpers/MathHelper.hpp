#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace MathHelper
{
	float DegreesToRadians(float degrees)
	{
		return (degrees / 180) * M_PI;
	}
}