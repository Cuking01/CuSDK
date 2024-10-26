#pragma once

struct K_Reg_Base:Reg_Base
{
	
};

struct Mask8:K_Reg_Base
{
	using ele_type=__mmask8;
	static constexpr u2 ele_num=1;
	__mmask8 mask;
	SIMD_OPT operator __mmask8() const {return mask;}
	SIMD_OPT void operator=(const __mmask8&mask){this->mask=mask;}

};

struct Mask16:K_Reg_Base
{
	using ele_type=__mmask16;
	static constexpr u2 ele_num=1;
	__mmask16 mask;
	SIMD_OPT operator __mmask16() const {return mask;}
	SIMD_OPT void operator=(const __mmask16&mask){this->mask=mask;}
};

struct Mask32:K_Reg_Base
{
	using ele_type=__mmask32;
	static constexpr u2 ele_num=1;
	__mmask32 mask;
	SIMD_OPT operator __mmask32() const {return mask;}
	SIMD_OPT void operator=(const __mmask32&mask){this->mask=mask;}
};

struct Mask64:K_Reg_Base
{
	using ele_type=__mmask64;
	static constexpr u2 ele_num=1;
	__mmask64 mask;
	SIMD_OPT operator __mmask64() const {return mask;}
	SIMD_OPT void operator=(const __mmask64&mask){this->mask=mask;}
};
