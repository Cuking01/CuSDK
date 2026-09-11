#pragma once

//等于 _MM_CMPINT_EQ
//小于 _MM_CMPINT_LT
//小于等于 _MM_CMPINT_LE
//不等于 _MM_CMPINT_NE
//大于 _MM_CMPINT_NLE
//大于等于 _MM_CMPINT_NLT

#ifdef __AVX512F__

namespace ins_details
{

	SIMD_OPT __mmask8 mm512_cmpeq_epu64(__m512i a,__m512i b){return _mm512_cmp_epu64_mask(a,b,_MM_CMPINT_EQ);}
	SIMD_OPT __mmask8 mm512_cmplt_epu64(__m512i a,__m512i b){return _mm512_cmp_epu64_mask(a,b,_MM_CMPINT_LT);}
	SIMD_OPT __mmask8 mm512_cmple_epu64(__m512i a,__m512i b){return _mm512_cmp_epu64_mask(a,b,_MM_CMPINT_LE);}
	SIMD_OPT __mmask8 mm512_cmpne_epu64(__m512i a,__m512i b){return _mm512_cmp_epu64_mask(a,b,_MM_CMPINT_NE);}
	SIMD_OPT __mmask8 mm512_cmpnle_epu64(__m512i a,__m512i b){return _mm512_cmp_epu64_mask(a,b,_MM_CMPINT_NLE);}
	SIMD_OPT __mmask8 mm512_cmpnlt_epu64(__m512i a,__m512i b){return _mm512_cmp_epu64_mask(a,b,_MM_CMPINT_NLT);}

}

make_i_2(operator==,ins_details::mm512_cmpeq_epu64,K8,avx512f,1,VU64x8,VU64x8)
make_i_2(operator!=,ins_details::mm512_cmpne_epu64,K8,avx512f,1,VU64x8,VU64x8)
make_i_2(operator<,ins_details::mm512_cmplt_epu64,K8,avx512f,1,VU64x8,VU64x8)
make_i_2(operator<=,ins_details::mm512_cmple_epu64,K8,avx512f,1,VU64x8,VU64x8)
make_i_2(operator>,ins_details::mm512_cmpnle_epu64,K8,avx512f,1,VU64x8,VU64x8)
make_i_2(operator>=,ins_details::mm512_cmpnlt_epu64,K8,avx512f,1,VU64x8,VU64x8)

#endif

#ifdef __AVX512BW__

namespace ins_details
{

	SIMD_OPT __mmask32 mm512_cmpeq_epu16(__m512i a,__m512i b){return _mm512_cmp_epu16_mask(a,b,_MM_CMPINT_EQ);}
	SIMD_OPT __mmask32 mm512_cmplt_epu16(__m512i a,__m512i b){return _mm512_cmp_epu16_mask(a,b,_MM_CMPINT_LT);}
	SIMD_OPT __mmask32 mm512_cmple_epu16(__m512i a,__m512i b){return _mm512_cmp_epu16_mask(a,b,_MM_CMPINT_LE);}
	SIMD_OPT __mmask32 mm512_cmpne_epu16(__m512i a,__m512i b){return _mm512_cmp_epu16_mask(a,b,_MM_CMPINT_NE);}
	SIMD_OPT __mmask32 mm512_cmpnle_epu16(__m512i a,__m512i b){return _mm512_cmp_epu16_mask(a,b,_MM_CMPINT_NLE);}
	SIMD_OPT __mmask32 mm512_cmpnlt_epu16(__m512i a,__m512i b){return _mm512_cmp_epu16_mask(a,b,_MM_CMPINT_NLT);}

}

make_i_2(operator==,ins_details::mm512_cmpeq_epu16,K32,avx512bw,1,VU16x32,VU16x32)
make_i_2(operator!=,ins_details::mm512_cmpne_epu16,K32,avx512bw,1,VU16x32,VU16x32)
make_i_2(operator<,ins_details::mm512_cmplt_epu16,K32,avx512bw,1,VU16x32,VU16x32)
make_i_2(operator<=,ins_details::mm512_cmple_epu16,K32,avx512bw,1,VU16x32,VU16x32)
make_i_2(operator>,ins_details::mm512_cmpnle_epu16,K32,avx512bw,1,VU16x32,VU16x32)
make_i_2(operator>=,ins_details::mm512_cmpnlt_epu16,K32,avx512bw,1,VU16x32,VU16x32)

#endif
