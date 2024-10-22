#pragma once

struct VF32x4:XMM_F
{
	SIMD_OPT void load  (const f2*p){f=_mm_load_ps(p);}
	SIMD_OPT void loadu (const f2*p){f=_mm_loadu_ps(p);}
	SIMD_OPT void store (f2*p) const{_mm_store_ps(p,f);}
	SIMD_OPT void storeu(f2*p) const{_mm_storeu_ps(p,f);}
	SIMD_OPT void stream(f2*p) const{_mm_stream_ps(p,f);}
	SIMD_OPT operator __m128()const{return f;}
};
