#pragma once

template<> struct Vec_Reg<64>
{
	__m64 reg;
};

using MM=Vec_Reg<64>;

template<typename T>
concept MM_T=std::derived_from<T,MM>;


