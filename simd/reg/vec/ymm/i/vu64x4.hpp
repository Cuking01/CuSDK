#pragma once

struct VU64x4:YMM_I
{
	SIMD_OPT void load  (const u3*p){i=_mm256_load_si256((const __m256i*)p);}
	SIMD_OPT void loadu (const u3*p){i=_mm256_loadu_si256((const __m256i*)p);}
	SIMD_OPT void store (u3*p) const{_mm256_store_si256((__m256i*)p,i);}
	SIMD_OPT void storeu(u3*p) const{_mm256_storeu_si256((__m256i*)p,i);}
	SIMD_OPT void stream(u3*p) const{_mm256_stream_si256((__m256i*)p,i);}
	SIMD_OPT operator __m256i()const{return i;}
};
