#pragma once

SIMD_OPT void prefetch_L1_impl(const void*p)
{
	_mm_prefetch(p,_MM_HINT_T0);
}

//make_i_2(prefetch,_mm_prefetch,void,sse,1,Addr_T<const void*>,FMT_Imm)


template<typename A,typename B> requires(IFMT<const void*,FMT_Imm>::check<A,B>()&&(sse))
SIMD_OPT auto prefetch(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm_prefetch,void,A,B>(a,b);
}
