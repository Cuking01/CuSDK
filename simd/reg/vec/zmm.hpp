#pragma once

struct ZMM:Vec_Reg_Base
{
	union
	{
		__m512i i;
		__m512 f;
		__m512d d;
		__m512h h;
	};

	template<ZMM_T T,ZMM_T B>
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<ZMM,B>&)self;
	}

	SIMD_OPT void load  (const void*p){i=_mm512_load_si512((__m512i*)p);}
	SIMD_OPT void loadu (const void*p){i=_mm512_loadu_si512((__m512i*)p);}
	SIMD_OPT void stream_load(const void*p){i=_mm512_stream_load_si512((__m512i*)p);}
	SIMD_OPT void store (void*p) const{_mm512_store_si512((__m512i*)p,i);}
	SIMD_OPT void storeu(void*p) const{_mm512_storeu_si512((__m512i*)p,i);}
	SIMD_OPT void stream(void*p) const{_mm512_stream_si512((__m512i*)p,i);}
};

struct ZMM_I:ZMM
{
	SIMD_OPT void operator=(const __m512i&i){this->i=i;}
	SIMD_OPT operator __m512i() const {return this->i;}
};

struct ZMM_F:ZMM
{
	SIMD_OPT void operator=(const __m512 &f){this->f=f;}
	SIMD_OPT operator __m512() const {return this->f;}
};

struct ZMM_D:ZMM
{
	SIMD_OPT void operator=(const __m512d&d){this->d=d;}
	SIMD_OPT operator __m512d() const {return this->d;}
};

struct ZMM_H:ZMM
{
	SIMD_OPT void operator=(const __m512h&h){this->h=h;}
	SIMD_OPT operator __m512h() const {return this->h;}
};

using VI8x64=Vec_Reg<s0,64,ZMM_I>;
using VI16x32=Vec_Reg<s1,32,ZMM_I>;
using VI32x16=Vec_Reg<s2,16,ZMM_I>;
using VI64x8=Vec_Reg<s3,8,ZMM_I>;
using VI128x4=Vec_Reg<s4,4,ZMM_I>;

using VU8x64=Vec_Reg<u0,64,ZMM_I>;
using VU16x32=Vec_Reg<u1,32,ZMM_I>;
using VU32x16=Vec_Reg<u2,16,ZMM_I>;
using VU64x8=Vec_Reg<u3,8,ZMM_I>;
using VU128x4=Vec_Reg<u4,4,ZMM_I>;

using VF32x16=Vec_Reg<f2,16,ZMM_F>;

using VF64x8=Vec_Reg<f3,8,ZMM_D>;

using VF16x32=Vec_Reg<_Float16,32,ZMM_H>;

