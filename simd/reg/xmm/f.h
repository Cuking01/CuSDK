#pragma once

struct XMM_F;

template<typename T>
concept XMM_F_T=std::derived_from<T,XMM_F>;

#include "f/vf32x4.h"
