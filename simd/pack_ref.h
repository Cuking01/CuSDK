#pragma once

template<Reg_T T,u2 n>
struct Pack_Ref;

template<typename T>
constexpr bool is_reg_pack_ref_v=false;

template<Reg_T Reg,u2 n>
constexpr bool is_reg_pack_ref_v<Pack<Reg,n>> =true;

template<typename T>
concept Pack_Ref_T=is_reg_pack_ref_v<T>;



