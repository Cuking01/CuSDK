#pragma once

struct ZMM;

template<typename T>
concept ZMM_T=std::derived_from<T,ZMM>&&Non_CV_T<T>;
