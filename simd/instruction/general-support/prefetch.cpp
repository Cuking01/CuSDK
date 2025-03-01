#pragma once

SIMD_OPT void prefetch_L1_impl(const void*p)
{
	_mm_prefetch(p,_MM_HINT_T0);
}

SIMD_OPT void prefetch_L2_impl(const void*p)
{
	_mm_prefetch(p,_MM_HINT_T1);
}

SIMD_OPT void prefetch_L3_impl(const void*p)
{
	_mm_prefetch(p,_MM_HINT_T2);
}

SIMD_OPT void prefetch_NTA_impl(const void*p)
{
	_mm_prefetch(p,_MM_HINT_NTA);
}

make_i_1(prefetch_L1,prefetch_L1_impl,void,sse,1,const void*)
make_i_1(prefetch_L2,prefetch_L2_impl,void,sse,1,const void*)
make_i_1(prefetch_L3,prefetch_L3_impl,void,sse,1,const void*)
make_i_1(prefetch_NTA,prefetch_NTA_impl,void,sse,1,const void*)

