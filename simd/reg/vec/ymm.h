#pragma once

struct YMM;

template<typename T>
concept YMM_T=std::derived_from<T,YMM>&&Non_CV_T<T>;

struct YMM_I;

template<typename T>
concept YMM_I_T=std::derived_from<T,YMM_I>;

struct YMM_F;

template<typename T>
concept YMM_F_T=std::derived_from<T,YMM_F>;

struct YMM_D;

template<typename T>
concept YMM_D_T=std::derived_from<T,YMM_D>;


#ifdef __AVX512F__

struct YMM_H;

template<typename T>
concept YMM_H_T=std::derived_from<T,YMM_H>;

#endif
