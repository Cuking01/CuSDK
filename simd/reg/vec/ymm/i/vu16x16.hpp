#pragma once

struct VU16x16:YMM_I
{
	SIMD_OPT void load  (const u1*p){i=_mm256_load_si256((const __m256i*)p);}
	SIMD_OPT void loadu (const u1*p){i=_mm256_loadu_si256((const __m256i*)p);}
	SIMD_OPT void store (u1*p) const{_mm256_store_si256((__m256i*)p,i);}
	SIMD_OPT void storeu(u1*p) const{_mm256_storeu_si256((__m256i*)p,i);}
	SIMD_OPT void stream(u1*p) const{_mm256_stream_si256((__m256i*)p,i);}
	SIMD_OPT operator __m256i()const{return i;}
};
