#pragma once

struct ZMM:Vec_Reg_Base
{
	union
	{
		__m512i i;
		__m512 f;
		__m512d d;
		__m512h h;
	};

	template<ZMM_T T,ZMM_T B>
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<ZMM,B>&)self;
	}

	SIMD_OPT void operator=(const __m512i&i){this->i=i;}
	SIMD_OPT void operator=(const __m512 &f){this->f=f;}
	SIMD_OPT void operator=(const __m512d&d){this->d=d;}
	SIMD_OPT void operator=(const __m512h&h){this->h=h;}

};

