#pragma once

struct XMM;

template<typename T>
concept XMM_T=std::derived_from<T,XMM>;

#include "xmm/i.h"
#include "xmm/f.h"
#include "xmm/d.h"
#include "xmm/h.h"

