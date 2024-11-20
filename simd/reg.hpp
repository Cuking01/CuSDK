#pragma once

struct Reg_Base
{
	template<Reg_T Self,Lazy_Eval_Record_T LER>
	SIMD_OPT void operator=(this Self&self,LER ler)
	{
		ler.eval(Pack_Ref<Self,1>(self));
	}

	SIMD_OPT decltype(auto) operator[](this auto&self,u2 idx)
	{
		return (self);
	}
};

#ifdef __AVX512F__
#include "reg/k.hpp"
#endif

#include "reg/vec.hpp"
