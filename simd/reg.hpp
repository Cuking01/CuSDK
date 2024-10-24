#pragma once

struct Reg_Base
{
	template<Reg_T Self,Lazy_Eval_Record_T LER>
	SIMD_OPT void operator=(this Self&self,LER ler)
	{
		ler.eval(Pack_Ref<Self,1>(self));
	}
};

#include "reg/k.hpp"
#include "reg/vec.hpp"
