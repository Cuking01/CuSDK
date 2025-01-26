#pragma once

make_i_2(operator==,_mm256_cmpeq_epi32,YMM_I,avx2,1,VI32x8,VI32x8)
make_i_2(operator==,_mm256_cmpeq_epi32,YMM_I,avx2,1,VU32x8,VU32x8)
