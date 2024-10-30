#pragma once

make_i_3(permute2x,_mm256_permute2f128_si256,get_reg<A>,avx,(reg_same<A,B>),YMM,YMM,FMT_Imm)

