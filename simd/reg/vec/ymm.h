#pragma once

struct YMM;

template<typename T>
concept YMM_T=std::derived_from<T,YMM>;

#include "ymm/i.h"
#include "ymm/f.h"
#include "ymm/d.h"
#include "ymm/h.h"
