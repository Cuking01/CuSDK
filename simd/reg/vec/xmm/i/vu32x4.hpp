#pragma once

struct VU32x4:XMM_I
{
	SIMD_OPT void load  (const u2*p){i=_mm_load_si128((const __m128i*)p);}
	SIMD_OPT void loadu (const u2*p){i=_mm_loadu_si128((const __m128i*)p);}
	SIMD_OPT void store (u2*p) const{_mm_store_si128((__m128i*)p,i);}
	SIMD_OPT void storeu(u2*p) const{_mm_storeu_si128((__m128i*)p,i);}
	SIMD_OPT void stream(u2*p) const{_mm_stream_si128((__m128i*)p,i);}
	SIMD_OPT operator __m128i()const{return i;}
};