#pragma once

make_i_2(operator|,_mm256_or_si256,get_reg<A>,avx2,(reg_same<A,B>),YMM_I,YMM_I)
make_i_2(operator|,_mm512_or_si512,get_reg<A>,avx512f,(reg_same<A,B>),ZMM_I,ZMM_I)

