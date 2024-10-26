#pragma once

template<Scale_T T,u2 n>
struct Scale_Pack_Ref;

template<typename T>
static constexpr bool is_scale_pack_ref=false;

template<Scale_T T,u2 n>
static constexpr bool is_scale_pack_ref<Scale_Pack_Ref<T,n>> =true;

template<typename T>
concept Scale_Pack_Ref_T=is_scale_pack_ref<T>;

