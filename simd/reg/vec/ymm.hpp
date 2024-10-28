#pragma once

struct YMM:Vec_Reg_Base
{
	union
	{
		__m256i i;
		__m256 f;
		__m256d d;
		__m256h h;
	};

	template<YMM_T T,YMM_T B>
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<YMM,B>&)self;
	}

	SIMD_OPT void load  (const void*p){i=_mm256_load_si256((__m256i*)p);}
	SIMD_OPT void loadu (const void*p){i=_mm256_loadu_si256((__m256i*)p);}
	SIMD_OPT void stream_load(const void*p){i=_mm256_stream_load_si256((__m256i*)p);}
	SIMD_OPT void store (void*p) const{_mm256_store_si256((__m256i*)p,i);}
	SIMD_OPT void storeu(void*p) const{_mm256_storeu_si256((__m256i*)p,i);}
	SIMD_OPT void stream(void*p) const{_mm256_stream_si256((__m256i*)p,i);}
};

struct YMM_I:YMM
{
#ifdef __AVX__
	SIMD_OPT void operator=(const __m256i&i){this->i=i;}
	SIMD_OPT operator __m256i() const {return this->i;}
#endif
};

struct YMM_F:YMM
{
#ifdef __AVX__
	SIMD_OPT void operator=(const __m256 &f){this->f=f;}
	SIMD_OPT operator __m256() const {return this->f;}
#endif
};

struct YMM_D:YMM
{
#ifdef __AVX__
	SIMD_OPT void operator=(const __m256d&d){this->d=d;}
	SIMD_OPT operator __m256d() const {return this->d;}
#endif
};


struct YMM_H:YMM
{
#ifdef __AVX__
	SIMD_OPT void operator=(const __m256h&h){this->h=h;}
	SIMD_OPT operator __m256h() const {return this->h;}
#endif
};

struct V8x32:Vec_Reg_Format_Base{};
struct V16x16:Vec_Reg_Format_Base{};
struct V32x8:Vec_Reg_Format_Base{};
struct V64x4:Vec_Reg_Format_Base{};
struct V128x2:Vec_Reg_Format_Base{};


using VI8x32=Vec_Reg<s0,32,YMM_I,V8x32>;
using VI16x16=Vec_Reg<s1,16,YMM_I,V16x16>;
using VI32x8=Vec_Reg<s2,8,YMM_I,V32x8>;
using VI64x4=Vec_Reg<s3,4,YMM_I,V64x4>;
using VI128x2=Vec_Reg<s4,2,YMM_I,V128x2>;

using VU8x32=Vec_Reg<u0,32,YMM_I,V8x32>;
using VU16x16=Vec_Reg<u1,16,YMM_I,V16x16>;
using VU32x8=Vec_Reg<u2,8,YMM_I,V32x8>;
using VU64x4=Vec_Reg<u3,4,YMM_I,V64x4>;
using VU128x2=Vec_Reg<u4,2,YMM_I,V128x2>;

using VF32x8=Vec_Reg<f2,8,YMM_F,V32x8>;

using VF64x4=Vec_Reg<f3,4,YMM_D,V64x4>;

using VF16x16=Vec_Reg<_Float16,16,YMM_H,V16x16>;

