#pragma once

template<typename A,typename B> requires (IFMT<V32x8,V32x8>::check<A,B>()&&avx&&std::same_as<A,B>)
SIMD_OPT auto unpackhi(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_unpackhi_epi32,get_reg<A>,A,B>(a,b);
}

template<typename A,typename B> requires (IFMT<V64x4,V64x4>::check<A,B>()&&avx&&std::same_as<A,B>)
SIMD_OPT auto unpackhi(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_unpackhi_epi64,get_reg<A>,A,B>(a,b);
}
