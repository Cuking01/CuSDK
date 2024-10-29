#pragma once

make_i_2(operator*,_mm256_mul_epi32,VI64x4,avx2,1,VI32x8,VI32x8)
make_i_2(operator*,_mm256_mul_epu32,VU64x4,avx2,1,VU32x8,VU32x8)

