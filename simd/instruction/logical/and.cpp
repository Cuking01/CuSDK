#pragma once

make_i_2(operator&,_mm256_and_si256,get_reg<A>,avx2,(reg_same<A,B>),YMM_I,YMM_I)
