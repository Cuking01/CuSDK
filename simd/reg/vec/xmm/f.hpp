#pragma once

struct XMM_F:XMM
{
	SIMD_OPT void operator=(const __m128 &f){this->f=f;}
};

#include "f/vf32x4.h"
