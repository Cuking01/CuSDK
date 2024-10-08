#pragma once

template<typename T>
concept Sample_Integer_Type=std::signed_integral<T>&&is(sizeof(T)).one_of(1,2,4);

template<typename T>
concept Sample_Float_Type=std::floating_point<T>&&is(sizeof(T)).one_of(4,8);

template<typename T>
concept Sample_Type=Sample_Integer_Type<T>||Sample_Float_Type<T>;

template<Sample_Float_Type T>
f3 sample_to_f3(T v)
{
	return v;
}

template<Sample_Integer_Type T>
f3 sample_to_f3(T v)
{
	static constexpr T max=std::numeric_limits<T>::max();
	static constexpr T min=std::numeric_limits<T>::min();

	if(v==min)v++;
	return v*(1.0/max);
}

template<Sample_Float_Type T>
T f3_to_sample(f3 v)
{
	return v;
}

template<Sample_Integer_Type T>
T f3_to_sample(f3 v)
{
	static constexpr T max=std::numeric_limits<T>::max();

	if(v>1)v=1;
	if(v<-1)v=-1;

	return v*max;
}

template<typename S,typename T>
T sample_trans(S v)
{
	return f3_to_sample<T>(sample_to_f3<S>(v));
}

template<typename S,typename T>
void sample_trans_n(T*to,const S*from,u3 n)
{
	for(u3 i=0;i<n;i++)
		to[i]=sample_trans<S,T>(from[i]);
}
