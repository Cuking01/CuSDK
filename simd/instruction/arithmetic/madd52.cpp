#pragma once

make_i_3(madd52lo,_mm512_madd52lo_epu64,VU64x8,avx512ifma52,1,VU64x8,VU64x8,VU64x8)

make_i_3(madd52hi,_mm512_madd52hi_epu64,VU64x8,avx512ifma52,1,VU64x8,VU64x8,VU64x8)
