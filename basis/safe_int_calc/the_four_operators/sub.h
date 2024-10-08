#pragma once

#pragma once

template<std::signed_integral T1,std::signed_integral T2>
auto sub_s(T1 a,T2 b)->decltype(a-b)
{
	using T=decltype(a-b);
	T A=a,B=b;
	if((A>=0)^(B>=0))return A+B;
	if(A>=0)cu_assert(B>=A-std::numeric_limits<T>::max(),"sub overflow");
	else cu_assert(B<=A-std::numeric_limits<T>::min(),"sub underflow");
	return A-B;
}

template<std::unsigned_integral T1,std::unsigned_integral T2>
auto sub_s(T1 a,T2 b)->decltype(a-b)
{
	using T=decltype(a-b);
	T A=a,B=b;
	cu_assert(A>=B,"sub underflow");
	return A-B;
}

template<std::unsigned_integral T1,std::signed_integral T2>
auto sub_s(T1 a,T2 b)->decltype(a-b)
{
	using T=decltype(a-b);
	T A=a,B=b;
	if(b>=0)cu_assert(A>=B,"sub underflow");
	else cu_assert(A<=std::numeric_limits<T>::max()+B,"sub overflow");
	return A-B;
}

template<std::signed_integral T1,std::unsigned_integral T2>
auto sub_s(T1 a,T2 b)->decltype(a-b)
{
	using T=decltype(a-b);
	T A=a,B=b;
	cu_assert(a>=0,"sub negative signed and unsigned");
	cu_assert(A>=B,"sub underflow");
	
	return A-B;
}

