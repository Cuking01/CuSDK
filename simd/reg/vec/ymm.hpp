#pragma once

struct YMM:Vec_Reg_Base
{
	union
	{
		__m256i i;
		__m256 f;
		__m256d d;
		__m256h h;
	};

	template<YMM_T T,YMM_T B>
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<YMM,B>&)self;
	}	
};

#include "ymm/i.hpp"
#include "ymm/f.hpp"
#include "ymm/d.hpp"
#include "ymm/h.hpp"
