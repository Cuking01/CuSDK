#pragma once

template<typename T>
struct Predicate
{
	const T*p_value;
	constexpr Predicate(T&&v) noexcept:p_value(&v){}
	constexpr Predicate(const T&v) noexcept:p_value(&v){}

	constexpr operator T() const noexcept {return *p_value;}
	constexpr const T& value() const noexcept {return *p_value;}
};


template<typename T>
struct is:Predicate<T>
{
	constexpr bool one_of(auto&&... args) const noexcept(noexcept(((Predicate<T>::value()==args)||...)))
	{
		return ((Predicate<T>::value()==args)||...);
	}

	constexpr bool none_of(auto&&... args) const noexcept(noexcept(!((Predicate<T>::value()==args)||...)))
	{
		return !((Predicate<T>::value()==args)||...);
	}

	constexpr bool in(auto&&l,auto&&r) const noexcept(noexcept(l<=Predicate<T>::value()&&Predicate<T>::value()<=r))
	{
		return l<=Predicate<T>::value()&&Predicate<T>::value()<=r;
	}
};

template<typename T>
is(T&&)->is<T>;
template<typename T>
is(const T&)->is<T>;
template<typename T>
is(T&)->is<T>;

