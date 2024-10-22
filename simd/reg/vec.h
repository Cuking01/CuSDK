struct Vec_Reg_Base;

template<typename T>
concept Vec_Reg_T=std::derived_from<T,Vec_Reg_Base>;

#include "vec/mm.h"
#include "vec/xmm.h"
#include "vec/ymm.h"
#include "vec/zmm.h"
