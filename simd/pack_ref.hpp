#pragma once



template<Vec_Reg_T T,u2 n>
struct Pack_Ref
{
	struct Ref
	{
		T& ref;
	};

	Ref ref[n];
};
