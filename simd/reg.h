#pragma once

struct Reg_Base;

#ifdef __AVX512F__
#include "reg/k.h"
#endif

#include "reg/vec.h"



template<typename T>
concept Reg_T=std::derived_from<T,Reg_Base>&&Non_CV_T<T>;

