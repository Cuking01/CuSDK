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

