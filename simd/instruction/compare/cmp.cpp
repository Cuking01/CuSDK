#pragma once

#ifdef __AVX512BW__

namespace ins_details
{

	//等于 _MM_CMPINT_EQ
	//小于 _MM_CMPINT_LT
	//小于等于 _MM_CMPINT_LE
	SIMD_OPT mm512_cmple_epu16(__m512i a,__m512i b){return _mm512_cmp_epu16_mask(a,b,_MM_CMPINT_LE);}
	SIMD_OPT mm512_cmple_epu64(__m512i a,__m512i b){return _mm512_cmp_epu64_mask(a,b,_MM_CMPINT_LE);}
	//不等于 _MM_CMPINT_NE
	//大于 _MM_CMPINT_NLE
	//大于等于 _MM_CMPINT_NLT



};

make_i_2(operator<=,ins_details::mm512_cmple_epu16,K32,avx512bw,1,VU16x32,VU16x32)
make_i_2(operator<=,ins_details::mm512_cmple_epu64,K8,avx512bw,1,VU64x8,VU64x8)

#endif
