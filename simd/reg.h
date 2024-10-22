#pragma once

#include "reg/k.h"
#include "reg/vec.h"



template<typename T>
concept Reg_T=Vec_Reg_T<T>||K_Reg_T<T>;

