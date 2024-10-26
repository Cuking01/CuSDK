#pragma once

template<typename T>
concept Scale_T=std::is_arithmetic_v<T>||std::is_same_v<T,u4>||std::is_same_v<T,s4>;

template<Scale_T T,u2 n>
struct Scale_Pack;

template<typename T>
constexpr bool is_scale_pack_v=false;

template<Scale_T T,u2 n>
constexpr bool is_scale_pack_v<Scale_Pack<T,n>> =true;

template<typename T>
concept Scale_Pack_T=is_scale_pack_v<T>;

