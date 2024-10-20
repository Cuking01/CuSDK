#pragma once

template<> struct Vec_Reg<512>
{
	__m512i reg;
};

using ZMM=Vec_Reg<512>;

template<typename T>
concept ZMM_T=std::derived_from<T,ZMM>;


