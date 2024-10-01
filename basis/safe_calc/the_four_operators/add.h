#pragma once

template<std::signed_integral T1,std::signed_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	using T=decltype(a+b);
	T A=a,B=b;
	if((A>=0)^(B>=0))return A+B;
	if(A>=0)cu_assert(A<=std::numeric_limits<T>::max()-B,"add overflow");
	else cu_assert(A>=std::numeric_limits<T>::min()-B,"add underflow");
	return A+B;
}

template<std::unsigned_integral T1,std::unsigned_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	using T=decltype(a+b);
	T A=a,B=b;
	cu_assert(A<=std::numeric_limits<T>::max()-B,"add overflow");
	return A+B;
}

template<std::unsigned_integral T1,std::signed_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	using T=decltype(a+b);
	T A=a,B=b;
	if(b>=0)cu_assert(A<=std::numeric_limits<T>::max()-B,"add overflow");
	else cu_assert(A>std::numeric_limits<T>::max()-B,"add underflow");
	return A+B;
}

template<std::signed_integral T1,std::unsigned_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	return add_s(b,a);
}

template<std::integral T1,std::integral T2,std::integral... Ts>
auto add_s(T1 a,T2 b,Ts... v) requires Not_Empty_Pack<Ts...>;
{
	return add_s(add_s(a,b),v...);
}
