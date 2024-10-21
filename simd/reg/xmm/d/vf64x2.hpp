#pragma once

struct VF64x2:XMM_D
{
	SIMD_OPT void load  (const f3*p){d=_mm_load_pd(p);}
	SIMD_OPT void loadu (const f3*p){d=_mm_loadu_pd(p);}
	SIMD_OPT void store (f3*p) const{_mm_store_pd(p,d);}
	SIMD_OPT void storeu(f3*p) const{_mm_storeu_pd(p,d);}
	SIMD_OPT void stream(f3*p) const{_mm_stream_pd(p,d);}
	SIMD_OPT operator __m128d()const{return d;}
};
