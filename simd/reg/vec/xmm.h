#pragma once

struct XMM;

template<typename T>
concept XMM_T=std::derived_from<T,XMM>&&Non_CV_T<T>;

struct XMM_I;

template<typename T>
concept XMM_I_T=std::derived_from<T,XMM_I>;

struct XMM_F;

template<typename T>
concept XMM_F_T=std::derived_from<T,XMM_F>;

struct XMM_D;

template<typename T>
concept XMM_D_T=std::derived_from<T,XMM_D>;

struct XMM_H;

template<typename T>
concept XMM_H_T=std::derived_from<T,XMM_H>;


struct V8x16;
struct V16x8;
struct V32x4;
struct V64x2;
struct V128x1;
