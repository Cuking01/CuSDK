#pragma once

template<typename A> requires (IFMT<VI32x16>::check<A>()&&avx512f)
SIMD_OPT auto reduce_add(const A&a)
{
	return Lazy_Eval_Record<_mm512_reduce_add_epi32,s2,A>(a);
}

