#pragma once

template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>())
SIMD_OPT auto operator+(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_add_epi32,VI32x8,A,B>(a,b);
}

template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>())
SIMD_OPT auto operator-(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_sub_epi32,VI32x8,A,B>(a,b);
}

template<typename A,typename B> requires (IFMT<YMM_I,YMM_I>::check<A,B>())
SIMD_OPT auto operator&(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_and_si256,YMM_I,A,B>(a,b);
}

template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>())
SIMD_OPT auto operator*(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_mul_epu32,VI64x4,A,B>(a,b);
}
