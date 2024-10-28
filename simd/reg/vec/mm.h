#pragma once

struct MM;

template<typename T>
concept MM_T=std::derived_from<T,MM>&&Non_CV_T<T>;

struct MM_I;

template<typename T>
concept MM_I_T=std::derived_from<T,MM_I>;

struct MM_F;

template<typename T>
concept MM_F_T=std::derived_from<T,MM_F>;

struct MM_D;

template<typename T>
concept MM_D_T=std::derived_from<T,MM_D>;

struct V8x8;
struct V16x4;
struct V32x2;
struct V64x1;

