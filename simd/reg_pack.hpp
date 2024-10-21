#pragma once

template<Vec_Reg_T Reg,u2 n>
struct Pack
{
	Reg reg[n];

};

template<typename T>
constexpr bool is_vec_reg_pack_v=false;

template<Vec_Reg_T Reg_T,u2 n>
constexpr bool is_vec_reg_pack_v<Pack<Reg_T,n>> =true;

template<typename T>
concept Vec_Reg_Pack_T=is_vec_reg_pack_v<T>;


