#pragma once

template<std::signed_integral T1,std::signed_integral T2>
auto mul_s(T1 a,T2 b)->decltype(a*b)
{
	using T=decltype(a*b);
	if(a==0||b==0)return 0;
	T A=a,B=b;
	if((A>=0)^(B>=0))
	{
		if(A<0)cu_assert(B<=std::number_limits<T>::min()/A,"mul underflow");
		else cu_assert(A<=std::number_limits<T>::min()/B,"mul underflow");
	}
	else
	{
		if(A<0)cu_assert(A>=std::number_limits<T>::max()/B,"mul overflow");
		else cu_assert(A<=std::number_limits<T>::max()/B,"mul overflow");
	}

	return A*B;
}

template<std::unsigned_integral T1,std::unsigned_integral T2>
auto mul_s(T1 a,T2 b)->decltype(a*b)
{
	using T=decltype(a*b);
	T A=a,B=b;
	if(A==0||B==0)return 0;
	cu_assert(A<=std::number_limits<T>::max()/B,"mul overflow");
	return A*B;
}

template<std::unsigned_integral T1,std::signed_integral T2>
auto mul_s(T1 a,T2 b)->decltype(a*b)
{
	cu_assert(b>=0,"mul negative signed and unsigned");

	using T=decltype(a*b);
	T A=a,B=b;
	if(A==0||B==0)return 0;
	cu_assert(A<=std::number_limits<T>::max()/B,"mul overflow");
	return A*B;
}

template<std::signed_integral T1,std::unsigned_integral T2>
auto mul_s(T1 a,T2 b)->decltype(a*b)
{
	cu_assert(a>=0,"mul negative signed and unsigned");

	using T=decltype(a*b);
	T A=a,B=b;
	if(A==0||B==0)return 0;
	cu_assert(A<=std::number_limits<T>::max()/B,"mul overflow");
	return A*B;
}

