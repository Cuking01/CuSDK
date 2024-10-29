#pragma once

template<typename... Args> requires (IFMT<s2,s2,s2,s2,s2,s2,s2,s2>::check<Args...>()&&avx)
SIMD_OPT auto set(const Args&... args)
{
	return Lazy_Eval_Record<_mm256_setr_epi32,VI32x8,Args...>(args...);
}
