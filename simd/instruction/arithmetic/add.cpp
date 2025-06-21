#pragma once

make_i_2(operator+,_mm256_add_epi32,VI32x8,avx2,1,VI32x8,VI32x8)
make_i_2(operator+,_mm256_add_epi32,VU32x8,avx2,1,VU32x8,VU32x8)

make_i_2(operator+,_mm512_add_epi64,VI64x8,avx512f,1,VI64x8,VI64x8)
make_i_2(operator+,_mm512_add_epi64,VU64x8,avx512f,1,VU64x8,VU64x8)



make_i_4(add,_mm512_mask_add_epi16,VI16x32,avx512bw,1,VI16x32,K32,VI16x32,VI16x32)
make_i_4(add,_mm512_mask_add_epi16,VU16x32,avx512bw,1,VU16x32,K32,VU16x32,VU16x32)

make_i_3(add,_mm512_maskz_add_epi16,VI16x32,avx512bw,1,K32,VI16x32,VI16x32)
make_i_3(add,_mm512_maskz_add_epi16,VU16x32,avx512bw,1,K32,VU16x32,VU16x32)

make_i_4(add,_mm512_mask_add_epi64,VI64x8,avx512bw,1,VI64x8,K8,VI64x8,VI64x8)
make_i_4(add,_mm512_mask_add_epi64,VU64x8,avx512bw,1,VU64x8,K8,VU64x8,VU64x8)

make_i_3(add,_mm512_maskz_add_epi64,VI64x8,avx512bw,1,K8,VI64x8,VI64x8)
make_i_3(add,_mm512_maskz_add_epi64,VU64x8,avx512bw,1,K8,VU64x8,VU64x8)
