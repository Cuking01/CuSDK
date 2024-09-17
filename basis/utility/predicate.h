#pragma once

template<typename T>
struct Predicate
{
	const T*p_value;
	constexpr Predicate(T&&v):p_value(&v){}
	constexpr Predicate(const T&v):p_value(&v){}

	constexpr operator T() const {return *p_value;}
	constexpr const T& value() const {return *p_value;}

	// void print_type() const
	// {
	// 	printf("%s\n",typeid(T).name());
	// }
};


template<typename T>
struct is:Predicate<T>
{
	constexpr bool one_of(auto&&... args) const
	{
		return ((Predicate<T>::value()==args)||...);
	}

	constexpr bool none_of(auto&&... args) const
	{
		return ((Predicate<T>::value()==args)||...);
	}
};

template<typename T>
is(T&&)->is<T>;
template<typename T>
is(const T&)->is<T>;
template<typename T>
is(T&)->is<T>;

