#pragma once

#include<xmmintrin.h>
#include<emmintrin.h>
#include<immintrin.h>

#define SIMD_OPT ALWAYS_INLINE
#define IMPL_ALTERNATIVE(...) 

#include "simd/flag.h"

#include "simd/reg.h"
#include "simd/reg_pack.h"
#include "simd/pack_ref.h"
#include "simd/cint.h"
#include "simd/scale.h"
#include "simd/scale_pack_ref.h"
#include "simd/address.h"
#include "simd/addr_pack_ref.h"
#include "simd/instruction.h"


#include "simd/reg.hpp"
#include "simd/reg_pack.hpp"
#include "simd/pack_ref.hpp"
#include "simd/cint.hpp"
#include "simd/scale.hpp"
#include "simd/scale_pack_ref.hpp"
#include "simd/address.hpp"
#include "simd/addr_pack_ref.hpp"
#include "simd/instruction.hpp"

#include "simd/instruction.cpp"

#undef IMPL_ALTERNATIVE
#undef SIMD_OPT
