#pragma once

struct XMM_D:XMM
{
	SIMD_OPT void operator=(const __m128d&d){this->d=d;}
};

#include "d/vf64x2.hpp"
