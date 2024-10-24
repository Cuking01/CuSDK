#pragma once

struct XMM_H:XMM
{
	SIMD_OPT void operator=(const __m128h&h){this->h=h;}
};

#include "h/vf16x8.hpp"
