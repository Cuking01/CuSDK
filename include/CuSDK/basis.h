#pragma once

#if !(__cplusplus>=202302L)
	#error "c++ standard must be C++23 or later"
#endif

#include "../../basis/std_head.h"

namespace cusdk
{

#include "../../basis/macro.h"
#include "../../basis/type_traits.h"
#include "../../basis/type.h"
#include "../../basis/concepts.h"
#include "../../basis/utility.h"
#include "../../basis/exception.h"
#include "../../basis/safe_int_calc.h"
#include "../../basis/file.h"
#include "../../basis/memory.h"

};
