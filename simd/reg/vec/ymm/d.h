#pragma once

struct YMM_D;

template<typename T>
concept YMM_D_T=std::derived_from<T,YMM_D>;

#include "d/vf64x4.h"
