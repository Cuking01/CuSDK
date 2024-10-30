#pragma once

make_i_2(operator<<,_mm256_slli_epi32,VI32x8,avx2,1,VI32x8,FMT_Imm)
make_i_2(operator<<,_mm256_slli_epi32,VU32x8,avx2,1,VU32x8,FMT_Imm)

make_i_2(operator<<,_mm256_slli_epi64,VI64x4,avx2,1,VI64x4,FMT_Imm)
make_i_2(operator<<,_mm256_slli_epi64,VU64x4,avx2,1,VU64x4,FMT_Imm)

