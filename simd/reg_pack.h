#pragma once

template<Reg_T Reg,u2 n> requires (n>0)
struct Pack;

template<typename T>
constexpr bool is_reg_pack_v=false;

template<Reg_T Reg_T,u2 n>
constexpr bool is_reg_pack_v<Pack<Reg_T,n>> =true;

template<typename T>
concept Reg_Pack_T=is_reg_pack_v<T>;

