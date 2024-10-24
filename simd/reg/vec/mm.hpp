#pragma once

struct MM:Vec_Reg_Base
{
	__m64 reg;

	template<XMM_T T,XMM_T B>
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<XMM,B>&)self;
	}

	SIMD_OPT void operator=(const __m64&reg){this->reg=reg;}

};

