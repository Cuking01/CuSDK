#pragma once

template<typename T>
struct Predicate
{
	const T*p_value;
	Predicate(T&&v):p_value(&v){}
	Predicate(const T&v):p_value(&v){}

	operator T() const {return *p_value;}
	const T& value() const {return *p_value;}

	void print_type() const
	{
		printf("%s\n",typeid(T).name());
	}
};


template<typename T>
struct is:Predicate<T>
{
	bool one_of(auto&&... args)
	{
		return ((Predicate<T>::value()==args)||...);
	}

	bool none_of(auto&&... args)
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
