#pragma once

struct YMM_H;

template<typename T>
concept YMM_H_T=std::derived_from<T,YMM_H>;

#include "h/vf16x16.h"

