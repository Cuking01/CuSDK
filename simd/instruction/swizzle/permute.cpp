#pragma once

make_i_3(permute2x,_mm256_permute2f128_si256,get_reg<A>,avx,(reg_same<A,B>),YMM,YMM,FMT_Imm)

make_i_2(permute8x32,_mm256_permutevar8x32_epi32,get_reg<A>,avx2,1,V32x8,VI32x8)
make_i_2(permute8x32,_mm256_permutevar8x32_epi32,get_reg<A>,avx2,1,V32x8,VU32x8)
