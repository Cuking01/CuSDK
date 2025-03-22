#pragma once

template<typename... Args> requires (IFMT<s2,s2,s2,s2,s2,s2,s2,s2>::check<Args...>()&&avx)
SIMD_OPT auto set(const Args&... args)
{
	return Lazy_Eval_Record<_mm256_setr_epi32,VI32x8,Args...>(args...);
}

//处理set是宏的问题
SIMD_OPT __m512i mm512_setr_epi64_helper(s3 e0,s3 e1,s3 e2,s3 e3,s3 e4,s3 e5,s3 e6,s3 e7)
{
	return _mm512_setr_epi64(e0,e1,e2,e3,e4,e5,e6,e7);
}

template<typename... Args> requires (IFMT<u3,u3,u3,u3,u3,u3,u3,u3>::check<Args...>()&&avx512f)
SIMD_OPT auto set(const Args&... args)
{
	return Lazy_Eval_Record<mm512_setr_epi64_helper,VU64x8,Args...>(args...);
}

