#pragma once

struct VF16x8:XMM_H
{
	SIMD_OPT void load  (const void*p){h=_mm_load_ph(p);}
	SIMD_OPT void loadu (const void*p){h=_mm_loadu_ph(p);}
	SIMD_OPT void store (void*p) const{_mm_store_ph(p,h);}
	SIMD_OPT void storeu(void*p) const{_mm_storeu_ph(p,h);}
	SIMD_OPT void stream(void*p) const{_mm_stream_si128((__m128i*)p,i);} IMPL_ALTERNATIVE("ph emulated by si128")
	SIMD_OPT operator __m128h()const{return h;}
};
