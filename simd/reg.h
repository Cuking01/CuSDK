#pragma once

struct Reg_Base;

#include "reg/k.h"
#include "reg/vec.h"



template<typename T>
concept Reg_T=std::derived_from<T,Reg_Base>&&Non_CV_T<T>;

