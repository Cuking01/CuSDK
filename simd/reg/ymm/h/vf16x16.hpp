#pragma once

struct VF16x16:YMM_H
{
	SIMD_OPT void load  (const void*p){h=_mm256_load_ph(p);}
	SIMD_OPT void loadu (const void*p){h=_mm256_loadu_ph(p);}
	SIMD_OPT void store (void*p) const{_mm256_store_ph(p,h);}
	SIMD_OPT void storeu(void*p) const{_mm256_storeu_ph(p,h);}
	SIMD_OPT void stream(void*p) const{_mm256_stream_si256((__m256i*)p,i);} IMPL_ALTERNATIVE("ph emulated by si256")
	SIMD_OPT operator __m256h()const{return h;}
};
