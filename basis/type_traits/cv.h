#pragma once

template<typename T>
struct is_non_cv:std::true_type{};

template<typename T>
struct is_non_cv<const T>:std::false_type{};

template<typename T>
struct is_non_cv<volatile T>:std::false_type{};

template<typename T>
struct is_non_cv<const volatile T>:std::false_type{};

template<typename T>
constexpr bool is_non_cv_v=is_non_cv<T>::value;


template<typename A,typename B>
struct const_with
{
	using type=std::remove_const_t<A>;
};

template<typename A,typename B> requires (std::is_const_v<B>)
struct const_with<A,B>
{
	using type=const std::remove_const_t<A>;
};

// if B is const then const A else A.
template<typename A,typename B>
using const_with_t=const_with<A,B>::type;

