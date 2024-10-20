#pragma once

template<> struct Vec_Reg<256>
{
	__m256i reg;
};

using YMM=Vec_Reg<256>;

template<typename T>
concept YMM_T=std::derived_from<T,YMM>;


