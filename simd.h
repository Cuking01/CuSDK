#pragma once

#include<xmmintrin.h>
#include<emmintrin.h>
#include<immintrin.h>

#define SIMD_OPT ALWAYS_INLINE
#define IMPL_ALTERNATIVE(...) 

#include "simd/reg.h"
#include "simd/reg_pack.h"
#include "simd/pack_ref.h"
#include "simd/cint.h"
#include "simd/instruction.h"


#include "simd/reg.hpp"
#include "simd/reg_pack.hpp"
#include "simd/pack_ref.hpp"
#include "simd/cint.hpp"
#include "simd/instruction.hpp"

#include "simd/instruction.cpp"

#undef IMPL_ALTERNATIVE
#undef SIMD_OPT
