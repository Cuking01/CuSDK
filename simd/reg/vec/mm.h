#pragma once

struct MM;

template<typename T>
concept MM_T=std::derived_from<T,MM>&&Non_CV_T<T>;
