#pragma once

template<Reg_T Reciver,u2 n,Lazy_Eval_Record_T LER>
void operator=(Pack_Ref<Reciver,n> reciver_ref,LER ler)
{
	ler.eval(reciver_ref);
}

template<Reg_T Reciver,Lazy_Eval_Record_T LER>
void operator=(Reciver&reciver_ref,LER ler)
{
	ler.eval(Pack_Ref<Reciver,1>(reciver_ref));
}




template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>())
SIMD_OPT auto operator+(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_add_epi32,VI32x8,A,B>(a,b);
	//return Lazy_Eval_Record<_mm256_add_epi32,VI32x8,Pack_CRef<VI32x8,n>,Pack_CRef<VI32x8,n>>{a,b};
}

