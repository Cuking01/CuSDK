#pragma once

template<typename T>
concept Addr_T=std::is_pointer_v<T>;

template<Addr_T T,u2 n>
struct Addr_Pack;

template<typename T>
constexpr bool is_addr_pack_v=false;

template<Addr_T T,u2 n>
constexpr bool is_addr_pack_v<Addr_Pack<T,n>> =true;

template<typename T>
concept Addr_Pack_T=is_addr_pack_v<T>;

