#pragma once

make_i_2(operator&,_mm256_add_epi32,get_reg<A>,avx2,(std::same_as<A,B>),YMM_I,YMM_I)
