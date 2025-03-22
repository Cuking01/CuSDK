#pragma once

make_i_1(set1,_mm256_set1_epi32,VI32x8,avx,1,s2)
make_i_1(set1,_mm256_set1_epi32,VU32x8,avx,1,u2)
make_i_1(set1,_mm512_set1_epi64,VI64x8,avx,1,s3)
make_i_1(set1,_mm512_set1_epi64,VU64x8,avx,1,u3)
