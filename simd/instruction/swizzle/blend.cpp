#pragma once

make_i_3(blend,_mm256_blend_epi32,get_reg<A>,avx,(reg_same<A,B>),V32x8,V32x8,FMT_Imm)

