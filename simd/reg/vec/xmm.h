#pragma once

struct XMM;

template<typename T>
concept XMM_T=std::derived_from<T,XMM>&&Non_CV_T<T>;

#include "xmm/i.h"
#include "xmm/f.h"
#include "xmm/d.h"
#include "xmm/h.h"

