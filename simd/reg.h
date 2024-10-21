#pragma once

struct Vec_Reg_Base;

template<typename T>
concept Vec_Reg_T=std::derived_from<T,Vec_Reg_Base>;

#include "reg/mm.h"
#include "reg/xmm.h"
#include "reg/ymm.h"
#include "reg/zmm.h"

