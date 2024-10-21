#pragma once

struct VU32x8:YMM_I
{
	SIMD_OPT void load  (const u2*p){i=_mm256_load_si256((const __m256i*)p);}
	SIMD_OPT void loadu (const u2*p){i=_mm256_loadu_si256((const __m256i*)p);}
	SIMD_OPT void store (u2*p) const{_mm256_store_si256((__m256i*)p,i);}
	SIMD_OPT void storeu(u2*p) const{_mm256_storeu_si256((__m256i*)p,i);}
	SIMD_OPT void stream(u2*p) const{_mm256_stream_si256((__m256i*)p,i);}
	SIMD_OPT operator __m256i()const{return i;}
};
