#pragma once

template<template<typename...> typename Template,typename Ins>
struct is_instance_of:std::false_type{};

template<template<typename...> typename Template,typename... Para>
struct is_instance_of<Template,Template<Para...>>:std::true_type{};

template<template<typename...> typename Template,typename Ins>
constexpr bool is_instance_of_v=is_instance_of<Template,Ins>::value;

