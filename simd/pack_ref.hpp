#pragma once

template<Reg_T Reg,u2 n>
struct Pack_Ref
{
	struct Ref
	{
		Reg& ref;
	};

	Ref ref[n];

	ALWAYS_INLINE Reg& operator[](u2 idx){return ref[idx].ref;} 
};
