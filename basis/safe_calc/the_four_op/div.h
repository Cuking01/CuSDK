#pragma once

template<std::integral T1,std::integral T2>
auto div_s(T1 a,T2 b)->decltype(a/b)
{
	cu_assert(b!=0,"div by 0");
	return a/b;
}

template<std::integral T1,std::integral T2>
auto mod_s(T1 a,T2 b)->decltype(a%b)
{
	cu_assert(b!=0,"div by 0");
	return a%b;
}
