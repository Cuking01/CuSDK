#pragma once

template<typename A,typename M> requires (IFMT<V32x8,FMT_Imm>::check<A,M>()&&avx)
SIMD_OPT auto shuffle(const A&a,const M&m)
{
	return Lazy_Eval_Record<_mm256_shuffle_epi32,get_reg<A>,A,M>(a,m);
}

