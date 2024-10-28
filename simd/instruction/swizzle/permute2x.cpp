#pragma once

template<typename A,typename B,typename M> requires (IFMT<YMM,YMM,FMT_Imm>::check<A,B,M>()&&std::same_as<A,B>&&avx)
SIMD_OPT auto permute2x(const A&a,const B&b,const M&imm)
{
	return Lazy_Eval_Record<_mm256_permute2f128_si256,get_reg<A>,A,B,M>(a,b,imm);
}
