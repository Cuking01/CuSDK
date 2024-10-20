#pragma once

template<u2 bitw>
struct Vec_Reg;


template<typename T>
constexpr bool is_vec_reg_impl=false;

template<u2 bitw>
constexpr bool is_vec_reg_impl<Vec_Reg<bitw>> =true;

template<typename T>
concept Vec_Reg_T=is_vec_reg_impl<T>;

#include "mm.h"
#include "xmm.h"
#include "ymm.h"
#include "zmm.h"

#include "mm.cpp"
#include "xmm.cpp"
#include "ymm.cpp"
#include "zmm.cpp"
