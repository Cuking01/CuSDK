#pragma once

struct YMM_F:YMM
{
	SIMD_OPT void operator=(const __m256 &f){this->f=f;}
};

#include "f/vf32x8.h"
