#pragma once

template<Reg_T Reg,u2 n>
struct Pack
{
	static constexpr u2 size=n;
	using Reg_Type=Reg;

	Reg reg[n];
	ALWAYS_INLINE Reg& operator[](u2 idx){return reg[idx];}
	ALWAYS_INLINE const Reg& operator[](u2 idx) const {return reg[idx];}
};




