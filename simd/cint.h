#pragma once


template<std::integral auto cint>
struct CInt;

template<typename T>
constexpr bool is_cint_v=false;

template<std::integral auto cint>
constexpr bool is_cint_v<CInt<cint>> =true;

template<typename T>
concept CInt_T=is_cint_v<T>;

template<std::integral auto... cints>
struct CInt_Pack;

template<typename T>
constexpr bool is_cint_pack_v=false;

template<std::integral auto... cints>
constexpr bool is_cint_pack_v<CInt_Pack<cints...>> =true;

template<typename T>
concept CInt_Pack_T=is_cint_pack_v<T>;
