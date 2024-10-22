#pragma once

struct VI128x2:YMM_I
{
	SIMD_OPT void load  (const void*p){i=_mm256_load_si256((const __m256i*)p);}
	SIMD_OPT void loadu (const void*p){i=_mm256_loadu_si256((const __m256i*)p);}
	SIMD_OPT void store (void*p) const{_mm256_store_si256((__m256i*)p,i);}
	SIMD_OPT void storeu(void*p) const{_mm256_storeu_si256((__m256i*)p,i);}
	SIMD_OPT void stream(void*p) const{_mm256_stream_si256((__m256i*)p,i);}
	SIMD_OPT operator __m256i()const{return i;}
};
