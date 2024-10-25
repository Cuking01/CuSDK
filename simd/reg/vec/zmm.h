#pragma once

struct ZMM;

template<typename T>
concept ZMM_T=std::derived_from<T,ZMM>&&Non_CV_T<T>;

struct ZMM_I;

template<typename T>
concept ZMM_I_T=std::derived_from<T,ZMM_I>;

struct ZMM_F;

template<typename T>
concept ZMM_F_T=std::derived_from<T,ZMM_F>;

struct ZMM_D;

template<typename T>
concept ZMM_D_T=std::derived_from<T,ZMM_D>;

struct ZMM_H;

template<typename T>
concept ZMM_H_T=std::derived_from<T,ZMM_H>;


