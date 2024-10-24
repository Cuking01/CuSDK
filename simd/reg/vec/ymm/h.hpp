#pragma once

struct YMM_H:YMM
{
	SIMD_OPT void operator=(const __m256h&h){this->h=h;}
};

#include "h/vf16x16.hpp"
