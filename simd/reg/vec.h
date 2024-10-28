#pragma once

struct Vec_Reg_Base;
struct Vec_Reg_Format_Base;

template<typename Ele_T,u2 Ele_N,typename MM_Base,typename FMT_Base> requires(sizeof(Ele_T)*Ele_N==sizeof(MM_Base))
struct Vec_Reg;

template<typename T>
concept Vec_Reg_T=std::derived_from<T,Vec_Reg_Base>&&Non_CV_T<T>;

template<typename T>
concept Vec_Reg_Format_T=std::derived_from<T,Vec_Reg_Format_Base>&&Non_CV_T<T>;

#include "vec/mm.h"
#include "vec/xmm.h"

#include "vec/ymm.h"

#include "vec/zmm.h"
