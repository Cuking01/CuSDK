#pragma once

struct YMM;

template<typename T>
concept YMM_T=std::derived_from<T,YMM>&&Non_CV_T<T>;

#include "ymm/i.h"
#include "ymm/f.h"
#include "ymm/d.h"
#include "ymm/h.h"
