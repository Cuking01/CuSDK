#pragma once

template<std::signed_integral T1,std::signed_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	using T=decltype(a+b);
	T A=a,B=b;
	if((A>=0)^(B>=0))return A+B;
	if(A>=0)cu_assert(A<=std::number_limits<T>::max()-B,"add overflow");
	else cu_assert(A>=std::number_limits<T>::min()-B,"add underflow");
	return A+B;
}

template<std::unsigned_integral T1,std::unsigned_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	using T=decltype(a+b);
	T A=a,B=b;
	cu_assert(A<=std::number_limits<T>::max()-B,"add overflow");
	return A+B;
}

template<std::unsigned_integral T1,std::signed_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	using T=decltype(a+b);
	T A=a,B=b;
	if(b>=0)cu_assert(A<=std::number_limits<T>::max()-B,"add overflow");
	else cu_assert(A>std::number_limits<T>::max()-B,"add underflow");
	return A+B;
}

template<std::signed_integral T1,std::unsigned_integral T2>
auto add_s(T1 a,T2 b)->decltype(a+b)
{
	return add_s(b,a);
}
