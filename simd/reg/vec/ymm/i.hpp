#pragma once

struct YMM_I:YMM
{
	SIMD_OPT void operator=(const __m256i&i){this->i=i;}
};

#include "i/vi8x32.hpp"
#include "i/vi16x16.hpp"
#include "i/vi32x8.hpp"
#include "i/vi64x4.hpp"
#include "i/vi128x2.hpp"

#include "i/vu8x32.hpp"
#include "i/vu16x16.hpp"
#include "i/vu32x8.hpp"
#include "i/vu64x4.hpp"
#include "i/vu128x2.hpp"

