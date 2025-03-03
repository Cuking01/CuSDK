#pragma once

template<Reg_T T,u2 n> requires (n>0)
struct Pack_Ref;

template<typename T>
constexpr bool is_reg_pack_ref_v=false;

template<Reg_T Reg,u2 n>
constexpr bool is_reg_pack_ref_v<Pack_Ref<Reg,n>> =true;

template<typename T>
concept Pack_Ref_T=is_reg_pack_ref_v<T>;



template<Reg_T T,u2 n> requires (n>0)
struct Pack_CRef;

template<typename T>
constexpr bool is_reg_pack_cref_v=false;

template<Reg_T Reg,u2 n>
constexpr bool is_reg_pack_cref_v<Pack_CRef<Reg,n>> =true;

template<typename T>
concept Pack_CRef_T=is_reg_pack_cref_v<T>||Pack_Ref_T<T>;

template<typename T>
concept Reg_Lvalue_Like_T=Reg_Lvalue_Ref_T<T>||Reg_Pack_Lvalue_Ref_T<T>||Pack_Ref_T<std::remove_cvref_t<T>>;

template<typename T>
concept Reg_CLvalue_Like_T=Reg_CLvalue_Ref_T<T>||Reg_Pack_CLvalue_Ref_T<T>||Pack_CRef_T<std::remove_cvref_t<T>>;

