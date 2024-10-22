#pragma once

struct YMM_I;

template<typename T>
concept YMM_I_T=std::derived_from<T,YMM_I>;

#include "i/vi8x32.h"
#include "i/vi16x16.h"
#include "i/vi32x8.h"
#include "i/vi64x4.h"
#include "i/vi128x2.h"

#include "i/vu8x32.h"
#include "i/vu16x16.h"
#include "i/vu32x8.h"
#include "i/vu64x4.h"
#include "i/vu128x2.h"
