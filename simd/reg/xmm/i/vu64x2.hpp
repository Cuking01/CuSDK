#pragma once

struct VU64x2:XMM_I
{
	SIMD_OPT void load  (const u3*p){i=_mm_load_si128((const __m128i*)p);}
	SIMD_OPT void loadu (const u3*p){i=_mm_loadu_si128((const __m128i*)p);}
	SIMD_OPT void store (u3*p) const{_mm_store_si128((__m128i*)p,i);}
	SIMD_OPT void storeu(u3*p) const{_mm_storeu_si128((__m128i*)p,i);}
	SIMD_OPT void stream(u3*p) const{_mm_stream_si128((__m128i*)p,i);}
	SIMD_OPT operator __m128i()const{return i;}
};
