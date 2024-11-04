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

struct YMM_H;

template<typename T>
concept YMM_H_T=std::derived_from<T,YMM_H>;

struct V8x32;
struct V16x16;
struct V32x8;
struct V64x4;
struct V128x2;

