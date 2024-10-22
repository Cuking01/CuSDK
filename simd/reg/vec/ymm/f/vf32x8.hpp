#pragma once

struct VF32x8:YMM_F
{
	SIMD_OPT void load  (const f2*p){f=_mm256_load_ps(p);}
	SIMD_OPT void loadu (const f2*p){f=_mm256_loadu_ps(p);}
	SIMD_OPT void store (f2*p) const{_mm256_store_ps(p,f);}
	SIMD_OPT void storeu(f2*p) const{_mm256_storeu_ps(p,f);}
	SIMD_OPT void stream(f2*p) const{_mm256_stream_ps(p,f);}
	SIMD_OPT operator __m256()const{return f;}
};
