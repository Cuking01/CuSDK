#pragma once

#define make_i_2(name,instrction,iflag,ret,...) \
template<typename A,typename B> requires(IFMT<__VA_ARGS__>::check<A,B>()&&(iflag)) \
SIMD_OPT auto name(const A&a,const B&b) \
{ \
	return Lazy_Eval_Record<instrction,ret,A,B>(a,b); \
}

make_i_2(operator+,_mm256_add_epi32,avx2,VI32x8,VI32x8,VI32x8)

// template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>()&&)
// SIMD_OPT auto operator+(const A&a,const B&b)
// {
// 	return Lazy_Eval_Record<_mm256_add_epi32,VI32x8,A,B>(a,b);
// }

template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>())
SIMD_OPT auto operator-(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_sub_epi32,VI32x8,A,B>(a,b);
}

template<typename A,typename B> requires (IFMT<YMM_I,YMM_I>::check<A,B>()&&avx2)
SIMD_OPT auto operator&(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_and_si256,YMM_I,A,B>(a,b);
}

template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>())
SIMD_OPT auto operator*(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_mul_epi32,VI64x4,A,B>(a,b);
}

template<typename A,typename B> requires (IFMT<VU32x8,VU32x8>::check<A,B>())
SIMD_OPT auto operator*(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_mul_epu32,VI64x4,A,B>(a,b);
}




#include "instruction/swizzle.cpp"


template<typename... Args> requires (IFMT<s2,s2,s2,s2,s2,s2,s2,s2>::check<Args...>()&&avx)
SIMD_OPT auto set(const Args&... args)
{
	return Lazy_Eval_Record<_mm256_setr_epi32,VI32x8,Args...>(args...);
}

template<typename... Args> requires (IFMT<s2>::check<Args...>())
SIMD_OPT auto set1(const Args&... args)
{
	return Lazy_Eval_Record<_mm256_set1_epi32,VI32x8,Args...>(args...);
}

template<typename A> requires (IFMT<VI32x16>::check<A>()&&avx512f)
SIMD_OPT auto reduce_add(const A&a)
{
	return Lazy_Eval_Record<_mm512_reduce_add_epi32,s2,A>(a);
}

