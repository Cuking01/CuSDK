#pragma once

make_i_2(operator-,_mm256_sub_epi32,VI32x8,avx2,1,VI32x8,VI32x8)
make_i_2(operator-,_mm256_sub_epi32,VU32x8,avx2,1,VU32x8,VU32x8)

make_i_2(operator-,_mm512_sub_epi64,VI64x8,avx512f,1,VI64x8,VI64x8)
make_i_2(operator-,_mm512_sub_epi64,VU64x8,avx512f,1,VU64x8,VU64x8)

