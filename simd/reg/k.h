#pragma once

struct K_Reg_Base;

template<typename T>
concept K_Reg_T=std::derived_from<T,K_Reg_Base>;
