#pragma once

struct VF64x4:YMM_D
{
	SIMD_OPT void load  (const f3*p){d=_mm256_load_pd(p);}
	SIMD_OPT void loadu (const f3*p){d=_mm256_loadu_pd(p);}
	SIMD_OPT void store (f3*p) const{_mm256_store_pd(p,d);}
	SIMD_OPT void storeu(f3*p) const{_mm256_storeu_pd(p,d);}
	SIMD_OPT void stream(f3*p) const{_mm256_stream_pd(p,d);}
	SIMD_OPT operator __m256d()const{return d;}

	
};
