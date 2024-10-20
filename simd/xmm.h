#pragma once

template<> struct Vec_Reg<128>
{
	__m128i reg;
};

using XMM=Vec_Reg<128>;

template<typename T>
concept XMM_T=std::derived_from<T,XMM>;


