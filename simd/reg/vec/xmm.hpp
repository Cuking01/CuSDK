#pragma once

struct XMM:Vec_Reg_Base
{
	union
	{
		__m128i i;
		__m128 f;
		__m128d d;
		__m128h h;
	};

	template<XMM_T T,typename B> requires (XMM_T<std::remove_const_t<B>>)
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<XMM,B>&)self;
	}

	SIMD_OPT void load  (const void*p){i=_mm_load_si128((const __m128i*)p);}
	SIMD_OPT void loadu (const void*p){i=_mm_loadu_si128((const __m128i*)p);}
	SIMD_OPT void stream_load(const void*p){i=_mm_stream_load_si128((const __m128i*)p);}
	SIMD_OPT void store (void*p) const{_mm_store_si128((__m128i*)p,i);}
	SIMD_OPT void storeu(void*p) const{_mm_storeu_si128((__m128i*)p,i);}
	SIMD_OPT void stream(void*p) const{_mm_stream_si128((__m128i*)p,i);}
	SIMD_OPT setzero(){i=_mm_setzero_si128();}
};

struct XMM_I:XMM
{
	SIMD_OPT void operator=(const __m128i&i){this->i=i;}
	SIMD_OPT operator __m128i() const {return this->i;}
	SIMD_OPT XMM_I(){}
	SIMD_OPT XMM_I(__m128i x){i=x;}
};

struct XMM_F:XMM
{
	SIMD_OPT void operator=(const __m128 &f){this->f=f;}
	SIMD_OPT operator __m128() const {return this->f;}
	SIMD_OPT XMM_F(){}
	SIMD_OPT XMM_F(__m128 x){f=x;}
};

struct XMM_D:XMM
{
	SIMD_OPT void operator=(const __m128d&d){this->d=d;}
	SIMD_OPT operator __m128d() const {return this->d;}
	SIMD_OPT XMM_D(){}
	SIMD_OPT XMM_D(__m128d x){d=x;}
};

struct XMM_H:XMM
{
	SIMD_OPT void operator=(const __m128h&h){this->h=h;}
	SIMD_OPT operator __m128h() const {return this->h;}
	SIMD_OPT XMM_H(){}
	SIMD_OPT XMM_H(__m128h x){h=x;}
};

struct V8x16:Vec_Reg_Format_Base{};
struct V16x8:Vec_Reg_Format_Base{};
struct V32x4:Vec_Reg_Format_Base{};
struct V64x2:Vec_Reg_Format_Base{};
struct V128x1:Vec_Reg_Format_Base{};


using VI8x16=Vec_Reg<s0,16,XMM_I,V8x16>;
using VI16x8=Vec_Reg<s1,8,XMM_I,V16x8>;
using VI32x4=Vec_Reg<s2,4,XMM_I,V32x4>;
using VI64x2=Vec_Reg<s3,2,XMM_I,V64x2>;
using VI128x1=Vec_Reg<s4,1,XMM_I,V128x1>;

using VU8x16=Vec_Reg<u0,16,XMM_I,V8x16>;
using VU16x8=Vec_Reg<u1,8,XMM_I,V16x8>;
using VU32x4=Vec_Reg<u2,4,XMM_I,V32x4>;
using VU64x2=Vec_Reg<u3,2,XMM_I,V64x2>;
using VU128x1=Vec_Reg<u4,1,XMM_I,V128x1>;

using VF32x4=Vec_Reg<f2,4,XMM_F,V32x4>;

using VF64x2=Vec_Reg<f3,2,XMM_D,V64x2>;

#ifdef __AVX512FP16__
using VF16x8=Vec_Reg<_Float16,8,XMM_H,V16x8>;
#endif
