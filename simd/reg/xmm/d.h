#pragma once

struct XMM_D;

template<typename T>
concept XMM_D_T=std::derived_from<T,XMM_D>;

#include "d/vf64x2.h"
