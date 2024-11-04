#pragma once

struct MM:Vec_Reg_Base
{
	__m64 reg;

	template<XMM_T T,typename B> requires (MM_T<std::remove_const_t<B>>)
	ALWAYS_INLINE decltype(auto) as(this B&self)
	{
		return (const_with_t<T,B>&)(const_with_t<XMM,B>&)self;
	}

	SIMD_OPT void operator=(const __m64&reg){this->reg=reg;}
	SIMD_OPT operator __m64() const {return this->reg;}
};



struct MM_I:MM{};

struct MM_F:MM{};

struct MM_D:MM{};

struct V8x8:Vec_Reg_Format_Base{};
struct V16x4:Vec_Reg_Format_Base{};
struct V32x2:Vec_Reg_Format_Base{};
struct V64x1:Vec_Reg_Format_Base{};


using VI8x8=Vec_Reg<s0,8,MM_I,V8x8>;
using VI16x4=Vec_Reg<s1,4,MM_I,V16x4>;
using VI32x2=Vec_Reg<s2,2,MM_I,V32x2>;
using VI64x1=Vec_Reg<s3,1,MM_I,V64x1>;

using VU8x8=Vec_Reg<u0,8,MM_I,V8x8>;
using VU16x4=Vec_Reg<u1,4,MM_I,V16x4>;
using VU32x2=Vec_Reg<u2,2,MM_I,V32x2>;
using VU64x1=Vec_Reg<u3,1,MM_I,V64x1>;

using VF32x2=Vec_Reg<f2,2,MM_F,V32x2>;

using VF64x1=Vec_Reg<f3,1,MM_D,V64x1>;
