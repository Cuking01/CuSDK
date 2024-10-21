#pragma once

struct YMM_F;

template<typename T>
concept YMM_F_T=std::derived_from<T,YMM_F>;

#include "f/vf32x8.h"
