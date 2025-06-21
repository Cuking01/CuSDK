#pragma once

struct K_Reg_Base;

template<u2 w> requires (w==8||w==16||w==32||w==64)
struct K_Reg;

template<typename T>
concept K_Reg_T=std::derived_from<T,K_Reg_Base>&&Non_CV_T<T>;
