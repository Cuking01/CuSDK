#pragma once

struct XMM_I;

template<typename T>
concept XMM_I_T=std::derived_from<T,XMM_I>;

#include "i/vi8x16.h"
#include "i/vi16x8.h"
#include "i/vi32x4.h"
#include "i/vi64x2.h"
#include "i/vi128x1.h"

#include "i/vu8x16.h"
#include "i/vu16x8.h"
#include "i/vu32x4.h"
#include "i/vu64x2.h"
#include "i/vu128x1.h"
