#pragma once

template<Addr_T T,u2 n>
struct Addr_Pack_Ref;

template<typename T>
static constexpr bool is_addr_pack_ref=false;

template<Addr_T T,u2 n>
static constexpr bool is_addr_pack_ref<Addr_Pack_Ref<T,n>> =true;

template<typename T>
concept Addr_Pack_Ref_T=is_addr_pack_ref<T>;

