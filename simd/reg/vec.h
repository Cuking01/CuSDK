#pragma once

struct Vec_Reg_Base;

template<typename Ele_T,u2 Ele_N,typename MM_Base> requires(sizeof(Ele_T)*Ele_N==sizeof(MM_Base))
struct Vec_Reg;

template<typename T>
concept Vec_Reg_T=std::derived_from<T,Vec_Reg_Base>&&Non_CV_T<T>;

#include "vec/mm.h"
#include "vec/xmm.h"

#ifdef __AVX__
#include "vec/ymm.h"
#endif

#ifdef __AVX512F__
#include "vec/zmm.h"
#endif
