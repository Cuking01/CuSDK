#pragma once


// #define make_simd_opt(name,opt,ret_type,...) \
// template<typename...Args> requires (IFMT<__VA_ARGS__>::check<Args...>()) \
// SIMD_OPT auto name(const Args&...args) \
// { \
// 	return Lazy_Eval_Record<opt,ret_type,__VA_ARGS__>(args...); \
// }

// make_simd_opt(operator+,_mm256_add_epi32,VI32x8,VI32x8,VI32x8)

// make_simd_opt(operator-,_mm256_sub_epi32,VI32x8,VI32x8,VI32x8)


// template<typename...Args> requires (IFMT<VI32x8,VI32x8>::check<Args...>())
// SIMD_OPT auto operator+(const Args&...args)
// {
// 	return Lazy_Eval_Record<_mm256_add_epi32,VI32x8,Args...>(args...);
// }

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

