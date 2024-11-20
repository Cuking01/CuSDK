#pragma once

struct Reg_Base;

#ifdef __AVX512F__
#include "reg/k.h"
#endif

#include "reg/vec.h"



template<typename T>
concept Reg_T=std::derived_from<T,Reg_Base>&&Non_CV_T<T>;

template<typename T>
concept Reg_Lvalue_Ref_T=std::is_lvalue_reference_v<T>&&Reg_T<std::remove_reference_t<T>>;

template<typename T>
concept Reg_CLvalue_Ref_T=std::is_lvalue_reference_v<T>&&Reg_T<std::remove_cvref_t<T>>;


