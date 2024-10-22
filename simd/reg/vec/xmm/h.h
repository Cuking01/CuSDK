#pragma once

struct XMM_H;

template<typename T>
concept XMM_H_T=std::derived_from<T,XMM_H>;

#include "h/vf16x8.h"

