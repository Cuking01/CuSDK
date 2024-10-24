#pragma once

struct YMM_D:YMM
{
	SIMD_OPT void operator=(const __m256d&d){this->d=d;}
};

#include "d/vf64x4.hpp"
