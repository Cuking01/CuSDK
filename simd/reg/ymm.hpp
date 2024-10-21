#pragma once

struct YMM
{
	union
	{
		__m256i i;
		__m256 f;
		__m256d d;
		__m256h h;
	};
};

#include "ymm/i.hpp"
#include "ymm/f.hpp"
#include "ymm/d.hpp"
#include "ymm/h.hpp"
