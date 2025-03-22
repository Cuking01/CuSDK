#pragma once

make_i_2(min,_mm256_min_epu32,VU32x8,avx2,1,VU32x8,VU32x8)
make_i_2(min,_mm512_min_epu64,VU64x8,avx512f,1,VU64x8,VU64x8)
