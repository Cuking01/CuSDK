#pragma once

struct XMM:Vec_Reg_Base
{
	union
	{
		__m128i i;
		__m128 f;
		__m128d d;
		__m128h h;
	};

	template<XMM_T T,XMM_T B>
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<XMM,B>&)self;
	}

	ALWAYS_INLINE void operator=(const __m128i&i){this->i=i;}
	ALWAYS_INLINE void operator=(const __m128 &f){this->f=f;}
	ALWAYS_INLINE void operator=(const __m128d&d){this->d=d;}
	ALWAYS_INLINE void operator=(const __m128h&h){this->h=h;}
};

#include "xmm/i.hpp"
#include "xmm/f.hpp"
#include "xmm/d.hpp"
#include "xmm/h.hpp"

